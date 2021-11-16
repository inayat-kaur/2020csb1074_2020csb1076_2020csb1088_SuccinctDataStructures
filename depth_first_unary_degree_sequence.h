#pragma once
# include "definitions.h"

void depth_first(tree ** k);
void DFUDS(tree ** k,int n);
void display_dfuds(void);
int find_close(int i);
int find_open(int i);
int enclose(int i);


int rank(char type,int i);
int select(char type, int i);
/*int parent(int v);
int firstchild(int v);
int sibling(int v);
int lastchild(int v);
int depth(int v);
int subtreesize(int v);
int degree(int v);*/
