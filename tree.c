# include <stdio.h>
# include <stdlib.h>


struct Tree{
    int data;
    int number_of_children;
    struct Tree** children; 
}typedef tree;


struct Node{
    int posn;
    char pr;
}typedef node;

int count=0;
int number_of_nodes=0;
node* bp=NULL;

void addNode(tree ** k);
void display(tree** r);
void balanced_paranthesis(tree ** k);
void display_bp(void);

int main(){
    tree * root=NULL;
    addNode(&root);
    display(&root);
    bp=(node*)malloc(2*sizeof(node)*number_of_nodes);
    balanced_paranthesis(&root);
    display_bp();
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

void display_bp(void){
    for(int i=0;i<2*number_of_nodes;i++){
        printf("%c ",bp[i].pr);
    }
    printf("\n");
    for(int i=0;i<2*number_of_nodes;i++){
        printf("%d ",bp[i].posn);
    }
    printf("\n");
}

void balanced_paranthesis(tree ** r){
    bp[count].posn=(*r)->data;
    bp[count].pr='(';
    count++;
    for(int i=0;i<(*r)->number_of_children;i++){
        balanced_paranthesis(&((*r)->children[i]));
    }
    bp[count].posn=(*r)->data;
    bp[count].pr=')';
    count++;
}