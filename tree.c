# include <stdio.h>
# include <stdlib.h>
# include "balanced_paranthesis.h"

void addNode(tree ** k);
void display(tree** r);

int main(){
    tree * root=NULL;
    addNode(&root);
    display(&root);
    bp=(node*)malloc(2*sizeof(node)*number_of_nodes);
    balanced_paranthesis(&root);
    display_bp();

    int res;
    for( int i = 0;i < 2*number_of_nodes; i++){
        if(bp[i].pr == '('){
            printf("FOR %d\n",bp[i].posn);
            printf("Parent of %d : ",bp[i].posn);
            if((res = parent(i))!=-1){ 
                printf("%d\n",res);
            }
            printf("first child of %d : ", bp[i].posn);
            if ((res = firstchild(i)) != -1) {
                printf("%d\n",res);
            }
            printf("last child of %d : ", bp[i].posn);
            if ((res = lastchild(i)) != -1) {
                printf("%d\n", res);
            }
            printf("sibling of %d : ",bp[i].posn);
            if((res = sibling(i))!=-1){
                printf("%d\n",res);
            }
            printf("depth %d : %d\n",bp[i].posn,depth(i));

            printf("subtree size of %d : %d\n",bp[i].posn,subtreesize(i));
        }
    }
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

