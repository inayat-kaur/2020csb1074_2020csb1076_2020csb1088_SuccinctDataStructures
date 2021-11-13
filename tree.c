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

int find_close(int i)
{
    int temp = bp[i].posn;
    for(int j=i+1; j<2*number_of_nodes; j++)
    {
        if(bp[j].posn == temp)
        {
            return j;
        }
        
    }
}

int find_open(int i){
    int temp = bp[i].posn;
    for(int j=i-1; j>-1; j--)
    {
        if(bp[j].posn == temp)
        {
            return j;
        }
    }
}

int enclose(int i){
    int count = 0;
    for(int j = i - 1; j > -1 ; j--){
        if(bp[j].pr == '('){
            count++;
        }
        else{
            count--;
        }
        if(count>0){
            return j;
        }
    }
}

int rank(char type,int i){
    int count =1;
    for(int j = i-1; j >-1 ; j--){
        if(bp[j].pr == type){
            count++;
        }
    }
    return count;
}

int select(char type, int i){
    int j;
    for(j = 0; j < 2*number_of_nodes && i>0 ; j++){
        if(bp[j].pr == type){
            i--;
        }
    }
    return j;
}

int parent(int v){
    if(v==0){
        printf("ROOT ITSELF\n");
        // parent of root ?? 
        return -1;
    }
    return bp[enclose(v)].posn;
}


int firstchild(int v){
    if (bp[v].pr == '(') {
        if (find_close(v) == v+1) {

            printf("NULL\n");
            return -1;
        }
        else {
            return bp[v + 1].posn;
        }
    }
    if (bp[v].pr == ')') {
        firstchild(find_open(v));
    }
}

int sibling(int v){
    if(v==0){
        printf("NULL\n");
        return -1;
    }
    if(bp[v].pr == '('){
        if(bp[v-1].pr == '('){
            if(bp[find_close(v)+1].pr == ')'){
                printf("NULL\n");
                return -1;
            }
            else{
                return bp[find_close(v)+1].posn;
            }
        }
        else{
            return bp[v-1].posn;
        }
    }
    else{
        return sibling(find_open(v));
    }
}

int lastchild(int v){
    if (bp[v].pr == ')') {
        if (find_open(v) == v - 1) {
            printf("NULL\n");
            return -1;
        }
        else {
            return bp[find_open(v - 1)].posn;
        }
    }
    else {
        lastchild(find_close(v));
    }
}

int depth(int v){
    return rank('(', v) - rank(')', v);
}

int subtreesize(int v){
    if(bp[v].pr == '('){
        return (find_close(v) - v + 1) / 2;
    }
    else{
        return ( v - find_open(v) + 1)/2 ;
    }
}
