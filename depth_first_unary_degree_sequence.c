# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "depth_first_unary_degree_sequence.h"
# include "definitions.h"

static int count=0;

int number_of_nodes=0;

node* dfuds=NULL;

void DFUDS(tree ** k,int n){
    number_of_nodes=n;
    dfuds=(node*)malloc(2*sizeof(node)*number_of_nodes);
    dfuds[count].val=(*k)->data;
    dfuds[count].pr='(';
    count++;
    depth_first(k);
    display_dfuds();

    int res;
    for( int i = 0;i < 2*number_of_nodes; i++){
        if(dfuds[i].pr == '('){
            printf("FOR %d\n",dfuds[i].val);
            printf("Parent of %d : ",dfuds[i].val);
            if((res = parent_dfuds(i))!=-1){ 
                printf("%d\n",res);
            }
            printf("Subtree size of %d : %d\n",dfuds[i].val,subtreesize_dfuds(i));
            printf("degree of %d : %d\n",dfuds[i].val,degree_dfuds(i));
            printf("Preorder rank of %d : %d\n",dfuds[i].val,preorder_rank_dfuds(i));
            printf("Preorder select of %d : %d\n",dfuds[i].val,preorder_select_dfuds(i));
            printf("Leaf-rank of %d : %d\n",dfuds[i].val,leaf_rank_dfuds(i));
            printf("Leaf-select of %d : %d\n",dfuds[i].val,leaf_select_dfuds(i));
            printf("Inorder rank of %d : %d\n",dfuds[i].val,inorder_rank_dfuds(i));
            printf("Inorder select of %d : %d\n",dfuds[i].val,inorder_select_dfuds(i));
            printf("Leftmost leaf of %d : %d\n",dfuds[i].val,leftmost_leaf_dfuds(i));
            printf("Rightmost leaf of %d : %d\n",dfuds[i].val,rightmost_leaf_dfuds(i));
        }
    }
//int child_dfuds(int v, int i);
//lac function left
//functions to be checked
}

void depth_first(tree ** r){
    for(int i=0;i<(*r)->number_of_children;i++){
         dfuds[count].val=(*r)->children[i]->data;
         dfuds[count].pr='(';
         count++;
    }
        dfuds[count].val=(*r)->data;
        dfuds[count].pr=')';
        count++;
    for(int i=0;i<(*r)->number_of_children;i++){
        depth_first(&((*r)->children[i]));
    }
}

void display_dfuds(void){
     for(int i=0;i<2*number_of_nodes;i++){
        printf("%c ",dfuds[i].pr);
    }
    printf("\n");
    for(int i=0;i<2*number_of_nodes;i++){
        printf("%d ",dfuds[i].val);
    }
    printf("\n");
}

int find_close_dfuds(int i)
{
    int temp = dfuds[i].val;
    for(int j=i+1; j<2*number_of_nodes; j++)
    {
        if(dfuds[j].val == temp)
        {
            return j;
        }      
    }
}

int find_open_dfuds(int i){
    int temp = dfuds[i].val;
    for(int j=i-1; j>-1; j--)
    {
        if(dfuds[j].val == temp)
        {
            return j;
        }
    }
}

int enclose_dfuds(int i){
    int count = 0;
    for(int j = i - 1; j > -1 ; j--){
        if(dfuds[j].pr == '('){
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

int rank_dfuds(char* pattern,int size,int i){
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
        new_string[p]=dfuds[p-(size+1)].pr;
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

int select_dfuds(char* pattern,int size,int i){
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
        new_string[p]=dfuds[p-(size+1)].pr;
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

int parent_dfuds(int v){
    return select_dfuds(")",1,rank_dfuds(")",1,find_open_dfuds(v-1))) + 1;
}

int child_dfuds(int v, int i){
    return find_close_dfuds(select_dfuds(")",1,rank_dfuds(")",1,v)+1)- i) + 1;
}

int subtreesize_dfuds(int v){
    return find_close_dfuds(enclose_dfuds(v)-v)/2 +1;
}

int degree_dfuds(int v){
    return select_dfuds(")",1,v) - select_dfuds("(",1,v) - 1;
}

int preorder_rank_dfuds(int v){
    return rank_dfuds(")",1,v-1)+1;
}

int preorder_select_dfuds(int i){
    return select_dfuds(")",1,i-1)+1;
}

int leaf_rank_dfuds(int v){
    return rank_dfuds("))",2,v);
}

int leaf_select_dfuds(int i){
     return select_dfuds("))",2,i);
}

int inorder_rank_dfuds(int v){
    return leaf_rank_dfuds(child_dfuds(v,2)-1);
}

int inorder_select_dfuds(int i){
    return parent_dfuds(leaf_select_dfuds(i)+1);
}

int leftmost_leaf_dfuds(int v){
    return leaf_select_dfuds(leaf_rank_dfuds(v-1)+1);
}

int rightmost_leaf_dfuds(int v){
    return find_close_dfuds(enclose_dfuds(v));
}
