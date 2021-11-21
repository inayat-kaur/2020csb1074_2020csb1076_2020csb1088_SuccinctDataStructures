#pragma once
# include "definitions.h"

extern node* bp;

void balanced_parentheses(tree ** k);
void Balanced_Parentheses(tree ** k,int n);
void display_bp(void);
int find_close_bp(int i);
int find_open_bp(int i);
int enclose_bp(int i);


int rank_bp(char *pattern,int i);
int select_bp(char *pattern, int i); 
int parent_bp(int v);
int firstchild_bp(int v);
int sibling_bp(int v);
int lastchild_bp(int v);
int depth_bp(int v);
int subtreesize_bp(int v);
int degree_bp(int v);