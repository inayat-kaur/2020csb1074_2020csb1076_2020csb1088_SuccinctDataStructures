# include <stdio.h>
# include <stdlib.h>
# include "balanced_parentheses.h"
# include "definitions.h"

static int count=0;

int number_of_nodes;

node* bp=NULL;

void Balanced_Parentheses(tree ** k,int n){
    printf("BALANCED PARENTHESES REPRESENTATION:\n");
    number_of_nodes=n;
    bp=(node*)malloc(2*sizeof(node)*number_of_nodes);
    balanced_parentheses(k);
    display_bp();

    int res;
    for( int i = 0;i < 2*number_of_nodes; i++){
        if(bp[i].pr == '('){
            printf("FOR %d\n",bp[i].val);
            printf("Parent of %d : ",bp[i].val);
            if((res = parent_bp(i))!=-1){ 
                printf("%d\n",bp[res].val);
            }
            printf("first child of %d : ", bp[i].val);
            if ((res = firstchild_bp(i)) != -1) {
                printf("%d\n",bp[res].val);
            }
            printf("last child of %d : ", bp[i].val);
            if ((res = lastchild_bp(i)) != -1) {
                printf("%d\n", bp[res].val);
            }
            printf("sibling of %d : ",bp[i].val);
            if((res = sibling_bp(i))!=-1){
                printf("%d\n",bp[res].val);
            }
            printf("depth %d : %d\n",bp[i].val,depth_bp(i));

            printf("subtree size of %d : %d\n",bp[i].val,subtreesize_bp(i));

            printf("Degree of %d is %d\n",bp[i].val,degree_bp(i));
        }
    }
}

// for displaying the encoded balanced parentheses representation of tree
void display_bp(void){
    for(int i=0;i<2*number_of_nodes;i++){
        printf("%c ",bp[i].pr);
    }
    printf("\n");
    for(int i=0;i<2*number_of_nodes;i++){
        printf("%d ",bp[i].val);
    }
    printf("\n");
}

// for encoding given tree as balanced parentheses
void balanced_parentheses(tree ** r){
    bp[count].val=(*r)->data;
    bp[count].pr='(';
    count++;
    for(int i=0;i<(*r)->number_of_children;i++){
        balanced_parentheses(&((*r)->children[i]));
    }
    bp[count].val=(*r)->data;
    bp[count].pr=')';
    count++;
}


// finds the closing parentheses corresponding to the opening pareentheses at i
int find_close_bp(int i)
{
    int temp = bp[i].val;
    for(int j=i+1; j<2*number_of_nodes; j++)
    {
        if(bp[j].val == temp)
        {
            return j;
        }
        
    }
}

// finds the opening parentheses corresponding to the closing pareentheses at i
int find_open_bp(int i){
    int temp = bp[i].val;
    for(int j=i-1; j>-1; j--)
    {
        if(bp[j].val == temp)
        {
            return j;
        }
    }
}

// finds the parentheses that just encloses 
int enclose_bp(int i){
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

// uses z-algorithm to find the rank of given parentheses
int rank_bp(char* pattern,int i){
    int size=1;
    int c =0;
    int p=0;
    int a, b, k;
    int l=size+1+i;
    int * Z_array=(int *)malloc(l*sizeof(int));
    char * new_string=(char*)malloc((l+1)*sizeof(char));
    while(p<size){
        new_string[p]=pattern[p];
        p++;
    }
    new_string[p]='$';
    p++;
    while(p<l){
        new_string[p]=bp[p-(size+1)].pr;
        p++;
    }
    new_string[p]='\0';
    a=0;
    b=0;
    for (int j=1;j<l;j++){
        if(j>b){
            a=j;
            b=j;
            while ((new_string[b-a]==new_string[b])&&(b<l))b++;
            Z_array[j]=b-a;
            b--;
        }
        else{
            k = j-a;
            if(Z_array[k]<b-i+1){
                Z_array[j] = Z_array[k];
            }
            else{
                a = j;
                while ((new_string[b-a] == new_string[b])&&(b<l)) b++;
                Z_array[j] = b-a;
                b--;
            }
        }
    }
    for(p=1;p<l;p++){
        if(Z_array[p]==size)c++;
    }
    free(Z_array);
    free(new_string);
    return c;
}

int select_bp(char* pattern,int i){
    int size = 1;
    int c=0;
    int p=0;
    int a, b, k;
    int l=size+1+(2*number_of_nodes);
    int * Z_array=(int *)malloc(l*sizeof(int));
    char * new_string=(char*)malloc((l+1)*sizeof(char));
    while(p<size){
        new_string[p]=pattern[p];
        p++;
    }
    new_string[p]='$';
    p++;
    while(p<l){
        new_string[p]=bp[p-(size+1)].pr;
        p++;
    }
    new_string[p]='\0';
    a=0;
    b=0;
    for (int j=1;j<l;j++){
        if(j>b){
            a=j;
            b=j;
            while ((new_string[b-a]==new_string[b])&&(b<l))b++;
            Z_array[j]=b-a;
            b--;
        }
        else{
            k = j-a;
            if(Z_array[k]<b-i+1){
                Z_array[j] = Z_array[k];
            }
            else{
                a = j;
                while ((new_string[b-a] == new_string[b])&&(b<l)) b++;
                Z_array[j] = b-a;
                b--;
            }
        }
    }
    for(p=1;p<l;p++){
        if(Z_array[p]==size)c++;
        if(c==i){
            free(Z_array);
            free(new_string);
            return p-size;
        } 
    }
    free(Z_array);
    free(new_string);
    return -1;
}

// finds the parent of given node
int parent_bp(int v){
    if(v==0){
        printf("ROOT ITSELF\n");
        return -1;
    }
    return enclose_bp(v);
}

// for finding the first child
int firstchild_bp(int v){
    if (bp[v].pr == '(') {
        if (find_close_bp(v) == v+1) {
            printf("NULL\n");
            return -1;
        }
        else {
            return (v + 1);
        }
    }
}

// for finding the sibling of the given vertex whose parentheses is at v
int sibling_bp(int v){
    if(v==0){
        printf("NULL\n");
        return -1;
    }
    if(bp[v].pr == '('){
        if(bp[v-1].pr == '('){
            int temp = find_close_bp(v) +1;
            if(bp[temp].pr == ')'){
                printf("NULL\n");
                return -1;
            }
            else{
                return temp;
            }
        }
        else{
            return (v-1);
        }
    }
}

int lastchild_bp(int v){
    if (bp[v].pr == ')') {
        if (find_open_bp(v) == v - 1) {
            printf("NULL\n");
            return -1;
        }
        else {
            return (v - 1);
        }
    }
    else {
        lastchild_bp(find_close_bp(v));
    }
}

int depth_bp(int v){
    return rank_bp("(", v) - rank_bp(")", v);
}

// return the number of nodes in the subtree rooted at the node corresopnding to vertex at v
int subtreesize_bp(int v){
    if(bp[v].pr == '('){
        return (find_close_bp(v) - v + 1) / 2;
    }
    else{
        return ( v - find_open_bp(v) + 1)/2 ;
    }
}

// return the degree: number of children of given node
int degree_bp(int v){
    int deg=0;
    int count =0;
    for(int i = v+1 ; i < find_close_bp(v); i++){
        if(bp[i].pr=='('){
            count++;
            if(count==1){
            deg++;
            }
        }
        else{
            count--;
        }
    }
    return deg;
}