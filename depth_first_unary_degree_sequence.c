# include <stdio.h>
# include <stdlib.h>
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
         dfuds[count].posn=(*r)->data;
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

int find_close(int i)
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

int find_open(int i){
    int temp = dfuds[i].posn;
    for(int j=i-1; j>-1; j--)
    {
        if(dfuds[j].posn == temp)
        {
            return j;
        }
    }
}

int enclose(int i){
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

int rank(char type,int i){
    int count =1;
    for(int j = i-1; j >-1 ; j--){
        if(dfuds[j].pr == type){
            count++;
        }
    }
    return count;
}

int select(char type, int i){
    int j;
    for(j = 0; j < 2*number_of_nodes && i>0 ; j++){
        if(dfuds[j].pr == type){
            i--;
        }
    }
    return j;
}