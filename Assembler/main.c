#include "avl.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

  FILE *file;
  char mne[16], bin[16];

  avl_node *n;
  Record r;

  //////////////////////////////////////////////////////////////////////////
  ////////////////////          numeros             ////////////////////////
  //////////////////////////////////////////////////////////////////////////
  avl_tree *n_tree = new_avl_tree();
  char n_vet[8][8] = {"0", "1", "2", "3", "4", "5", "6", "7"};
  char b_vet[8][8] = {"000", "001", "010", "011", "100", "101", "110", "111"};

  for (int i = 0; i < 8; i++) {
    r.key = n_vet[i];
    r.value = b_vet[i];
    n = new_avl_node(r);
    insert(n_tree, n);
  }

  //////////////////////////////////////////////////////////////////////////
  ////////////////////          mnemônicos          ////////////////////////
  //////////////////////////////////////////////////////////////////////////

  file = fopen("mne.txt", "r");

  avl_tree *m_tree = new_avl_tree();

  if (file == NULL) {
    printf("[ERROR]: Fail to open file!\n");
    return -1;
  }

  while ((fscanf(file, "%s\t%s\n", bin, mne)) != EOF) {
    r.key = strdup(mne);
    r.value = strdup(bin);
    n = new_avl_node(r);
    insert(m_tree, n);
  }

  fclose(file);

  //////////////////////////////////////////////////////////////////////////
  ////////////////////          assembly            ////////////////////////
  //////////////////////////////////////////////////////////////////////////

  file = fopen("assembly.txt", "r");
  FILE *b_file = fopen("hex.hex", "w");
  char opm[16], s1[2], s2[2], s3[2];
  char *opc, *d1, *d2, *d3;

  if (file == NULL) {
    printf("[ERROR]: Fail to open file!\n");
    return -1;
  }
  if (b_file == NULL) {
    printf("[ERROR]: Fail to open file!\n");
    return -1;
  }

  TipoLista b_lista, h_lista;
  TipoItem b_item, h_item;
  FLVazia(&b_lista);
  FLVazia(&h_lista);
  int cont = 0;

  fprintf(b_file, "v2.0 raw\n");

  while ((fscanf(file, "%s\t%s\t%s\t%s\n", opm, s1, s2, s3)) != EOF) {
    r.key = opm;
    n = new_avl_node(r);
    opc = search(m_tree->root, n)->data.value;

    r.key = s1;
    n = new_avl_node(r);
    d1 = search(n_tree->root, n)->data.value;

    r.key = s2;
    n = new_avl_node(r);
    d2 = search(n_tree->root, n)->data.value;

    r.key = s3;
    n = new_avl_node(r);
    d3 = search(n_tree->root, n)->data.value;

    char binaryString[20];

    snprintf(binaryString, 20, "%s%s%s%s\n", opc, d1, d2, d3);

    b_item.Chave = cont;
    b_item.Valor = strdup(binaryString);
    Insere(b_item, &b_lista);

    int value = (int)strtol(binaryString, NULL, 2);
    char hexString[12]; // long enough for any 32-bit value, 4-byte aligned
    sprintf(hexString, "%04x\n", value);

    h_item.Chave = cont;
    h_item.Valor = strdup(hexString);
    Insere(h_item, &h_lista);

    fprintf(b_file, hexString, opc, d1, d2, d3);
    cont++;
  }

  fclose(file);
  fclose(b_file);

  Imprime(h_lista);
  Imprime(b_lista);

  return 0;
}
