# include <stdio.h>
# include <stdlib.h>
# include "definitions.h"
# include "balanced_parentheses.h"
# include "depth_first_unary_degree_sequence.h"
# include "LOUDS.h"

void addNode(tree ** k);

int number_of_nodes;

int main(){
    number_of_nodes=0;
    tree * root=NULL;
    addNode(&root);
    Balanced_Parentheses(&root, number_of_nodes);
    DFUDS(&root, number_of_nodes);
    LOUDS_print(root,number_of_nodes);
    return 0;
}

void addNode(tree ** k){
    *k=(tree *)malloc(sizeof(tree));
    int d,t;
    printf("Enter data of node: ");
    scanf("%d",&d);
    (*k)->data=d;
    number_of_nodes++;
    printf("Enter number of children: ");
    scanf("%d",&t);
    if(t>0) (*k)->children =(tree**)malloc(t*(sizeof(tree*)));
    (*k)->number_of_children=t;
    for(int i=0;i<t;i++){
        printf("\nAdd child %d of node %d:\n",i+1,(*k)->data);
        addNode(&((*k)->children[i]));
    }  
}

