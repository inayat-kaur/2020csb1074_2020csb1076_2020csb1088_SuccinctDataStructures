# pragma once

extern int number_of_nodes;

struct Tree{
    int data;
    int number_of_children;
    struct Tree** children; 
}typedef tree;

struct Node{
    int posn;
    char pr;
}typedef node;