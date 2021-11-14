# include <stdio.h>
# include <stdlib.h>
# include "balanced_paranthesis.h"

void addNode(tree ** k);
void display(tree** r);
static int number_of_nodes=0;

int main(){
    tree * root=NULL;
    addNode(&root);
    display(&root);
    Balanced_Paranthesis(&root,number_of_nodes);
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

void display(tree** r){
    printf("%d ",(*r)->data); 
    for(int i=0;i<(*r)->number_of_children;i++){
        display(&((*r)->children[i]));
    }
    printf("\n");  
}

