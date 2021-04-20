#ifndef __AVL_H
#define __AVL_H

typedef struct Record {
  char *key;
  char *value;
} Record;

typedef struct avl_node {
  Record data;
  struct avl_node *left;
  struct avl_node *right;
  struct avl_node *parent;
  int height;
} avl_node;

typedef struct avl_tree {
  avl_node *root;
} avl_tree;

avl_node *new_avl_node(Record data);
avl_tree *new_avl_tree();
int max(int a, int b);
int height(avl_node *n);
avl_node *minimum(avl_tree *t, avl_node *x);
void left_rotate(avl_tree *t, avl_node *x);
void right_rotate(avl_tree *t, avl_node *x);
int balance_factor(avl_node *n);
void insert(avl_tree *t, avl_node *n);
void transplant(avl_tree *t, avl_node *u, avl_node *v);
void avl_delete_fixup(avl_tree *t, avl_node *n);
void avl_delete(avl_tree *t, avl_node *z);
void inorder(avl_tree *t, avl_node *n);
avl_node *search(avl_node *x, avl_node *z);

#endif
