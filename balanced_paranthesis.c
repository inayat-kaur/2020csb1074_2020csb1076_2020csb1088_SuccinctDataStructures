# include <stdio.h>
# include <stdlib.h>
# include "balanced_paranthesis.h"

int count=0;
static int number_of_nodes=0;
node* bp=NULL;

void Balanced_Paranthesis(tree ** k,int n){
    number_of_nodes=n;
    bp=(node*)malloc(2*sizeof(node)*number_of_nodes);
    balanced_paranthesis(k);
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
}

void display_bp(void){
    for(int i=0;i<2*number_of_nodes;i++){
        printf("%c ",bp[i].pr);
    }
    printf("\n");
    for(int i=0;i<2*number_of_nodes;i++){
        printf("%d ",bp[i].posn);
    }
    while (1)
    {
        printf("b");
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
}

int sibling(int v){
    if(v==0){
        printf("NULL\n");
        return -1;
    }
    if(bp[v].pr == '('){
        if(bp[v-1].pr == '('){
            int temp = find_close(v) +1;
            if(bp[temp].pr == ')'){
                printf("NULL\n");
                return -1;
            }
            else{
                return bp[temp].posn;
            }
        }
        else{
            return bp[v-1].posn;
        }
    }
}

int lastchild(int v){
    if (bp[v].pr == ')') {
        if (find_open(v) == v - 1) {
            printf("NULL\n");
            return -1;
        }
        else {
            return bp[v - 1].posn;
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