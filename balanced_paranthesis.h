#pragma once

struct Tree{
    int data;
    int number_of_children;
    struct Tree** children; 
}typedef tree;

struct Node{
    int posn;
    char pr;
}typedef node;

extern int count;
extern int number_of_nodes;
extern node* bp;

void balanced_paranthesis(tree ** k);
void display_bp(void);
int find_close(int i);
int find_open(int i);
int enclose(int i);


int rank(char type,int i);
int select(char type, int i);
int parent(int v);
int firstchild(int v);
int sibling(int v);
int lastchild(int v);
int depth(int v);
int subtreesize(int v);
int degree(int v);