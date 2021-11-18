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
    dfuds[count].posn=(*k)->data;
    dfuds[count].pr='(';
    count++;
    depth_first(k);
    display_dfuds();

    /*int res;
    for( int i = 0;i < 2*number_of_nodes; i++){
        if(dfuds[i].pr == '('){
            printf("FOR %d\n",dfuds[i].posn);
            printf("Parent of %d : ",dfuds[i].posn);
            if((res = parent(i))!=-1){ 
                printf("%d\n",res);
            }
            printf("first child of %d : ", dfuds[i].posn);
            if ((res = firstchild(i)) != -1) {
                printf("%d\n",res);
            }
            printf("last child of %d : ", dfuds[i].posn);
            if ((res = lastchild(i)) != -1) {
                printf("%d\n", res);
            }
            printf("sibling of %d : ",dfuds[i].posn);
            if((res = sibling(i))!=-1){
                printf("%d\n",res);
            }
            printf("depth %d : %d\n",dfuds[i].posn,depth(i));

            printf("subtree size of %d : %d\n",dfuds[i].posn,subtreesize(i));
        }
    }*/

}

void depth_first(tree ** r){
    for(int i=0;i<(*r)->number_of_children;i++){
         dfuds[count].posn=(*r)->children[i]->data;
         dfuds[count].pr='(';
         count++;
    }
        dfuds[count].posn=(*r)->data;
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
        printf("%d ",dfuds[i].posn);
    }
    printf("\n");
}

int find_close_dfuds(int i)
{
    int temp = dfuds[i].posn;
    for(int j=i+1; j<2*number_of_nodes; j++)
    {
        if(dfuds[j].posn == temp)
        {
            return j;
        }      
    }
}

int find_open_dfuds(int i){
    int temp = dfuds[i].posn;
    for(int j=i-1; j>-1; j--)
    {
        if(dfuds[j].posn == temp)
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
    int Z_array[l];
    char new_string[l+1];
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
    return c;
}

int select_dfuds(char type, int i){
    int j;
    for(j = 0; j < 2*number_of_nodes && i>0 ; j++){
        if(dfuds[j].pr == type){
            i--;
        }
    }
    return j;
}

int parent_dfuds(int v){
    return select_dfuds(')',rank_dfuds(")",1,find_open_dfuds(v-1))) + 1;
}

int child_dfuds(int v, int i){
    return find_close_dfuds(select_dfuds(')',rank_dfuds(")",1,v)+1)- i) + 1;
}

int subtreesize_dfuds(int v){
    return find_close_dfuds(enclose_dfuds(v)-v)/2 +1;
}

int degree_dfuds(int v){
    return select_dfuds(')',rank_dfuds(")",1,v)+1)-v;
}

int preorder_rank_dfuds(int v){
    return rank_dfuds(")",1,v-1)+1;
}

int preorder_select_dfuds(int i){
    return select_dfuds(')',i-1)+1;
}

