#pragma once
# include "definitions.h"

void depth_first(tree ** k);
void DFUDS(tree ** k,int n);
void display_dfuds(void);

int find_close_dfuds(int i);
int find_open_dfuds(int i);
int enclose_dfuds(int i);
int rank_dfuds(char* pattern,int size,int i);
int select_dfuds(char* pattern,int size,int i);

int parent_dfuds(int v);
int last_child_dfuds(int v);
int first_child_dfuds(int v);
int degree_dfuds(int v);
int leaf_rank_dfuds(int v);
int leaf_select_dfuds(int i);

