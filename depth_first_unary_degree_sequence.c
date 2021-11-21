# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "depth_first_unary_degree_sequence.h"
# include "definitions.h"

static int count=0;

int number_of_nodes=0;

node* dfuds=NULL;       // pointer to the array of structures storing the parentheses and node data

void DFUDS(tree ** k,int n){
    number_of_nodes=n;
    dfuds=(node*)malloc(2*sizeof(node)*number_of_nodes);    //allocating memory for the parentheses sequence
    dfuds[count].val=(*k)->data;
    dfuds[count].pr='(';
    count++;
    depth_first(k);             //performing depth first traversal and storing the nodes of the tree
    display_dfuds();            //Displaying the stored tree
    int res;
    for( int i = 0;i < 2*number_of_nodes; i++){
        if(dfuds[i].pr == '('){
            printf("FOR %d\n",dfuds[i].val);
            printf("Parent of %d : ",dfuds[i].val);
            res = parent_dfuds(i);
            if(res!=-1){ 
                printf("%d\n",dfuds[res-1].val);
            }
            else if(res==-1) printf("ROOT ITSELF\n");
            if(first_child_dfuds(i)!=-1) printf("First child of %d : %d\n",dfuds[i].val,dfuds[first_child_dfuds(i)-1].val);
            else printf("First child of %d : NULL\n",dfuds[i].val);
            if(first_child_dfuds(i)!=-1) printf("Last child of %d : %d\n",dfuds[i].val,dfuds[last_child_dfuds(i)-1].val);
            else printf("Last child of %d : NULL\n",dfuds[i].val);
            printf("Degree of %d : %d\n",dfuds[i].val,degree_dfuds(dfuds[i].val));
            printf("Leaf-rank of %d : %d\n",dfuds[i].val,leaf_rank_dfuds(i));
        }
        //printf("Leaf no. %d : %d\n",x,leaf_select_dfuds(x));
    }
}

void depth_first(tree ** r){                //performing depth first search on the tree and storing values and parentheses for the nodes
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
    printf("DEPTH FIRST UNARY DEGREE SEQUENCE (DFUDS) REPRESENTATION\n");
     for(int i=0;i<2*number_of_nodes;i++){
        printf("%c ",dfuds[i].pr);      //displaying the parantheses sequence
    }
    printf("\n");
    for(int i=0;i<2*number_of_nodes;i++){
        printf("%d ",dfuds[i].val);         //displaying the values of the nodes in the parantheses sequence
    }
    printf("\n");
}

int find_close_dfuds(int i)     //function to find closing bracket corresponding to the opening bracket at index i
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

int find_open_dfuds(int i){         //function to find opening bracket corresponding to the closing bracket at index i
    int temp = dfuds[i].val;
    for(int j=i-1; j>-1; j--)
    {
        if(dfuds[j].val == temp)
        {
            return j;
        }
    }
}

int enclose_dfuds(int i){           //function to find the opening bracket which encloses the opening bracket at index i
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

int rank_dfuds(char* pattern,int size,int i){       //function to find the rank of a given pattern till index i using Z-array method
    int c =0;
    int p=0;
    int a, b, k;
    int l=size+1+i;
    int * Z_array=(int *)malloc(l*sizeof(int));         //allocating memory for the Z-array
    char * new_string=(char*)malloc((l+1)*sizeof(char));        //allocating memory for the concatinated string of pattern and parantheses
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
    for (int j=1;j<l;j++){                                      //finding rank using Z-algorithm
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
        if(Z_array[p]==size)c++;        //calculating the number of occurrences of the pattern
    }
    free(Z_array);          //freeing the allocated memory
    free(new_string);
    return c;
}

int select_dfuds(char* pattern,int size,int i){           //function to find the index of the ith occurrence of the patten using Z-array method
    int c=0;
    int p=0;
    int a, b, k;
    int l=size+1+(2*number_of_nodes);
    int * Z_array=(int *)malloc(l*sizeof(int));          //allocating memory for the Z-array
    char * new_string=(char*)malloc((l+1)*sizeof(char));        //allocating memory for the concatinated string of pattern and parantheses
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
        if(j>b){                                                //Calculating select using Z-array algorithm
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
        if(Z_array[p]==size)c++;                //finding the index of ith occurrence of the pattern
        if(c==i){
            free(Z_array);
            free(new_string);
            return p-size;
        } 
    }
    free(Z_array);                   //freeing the allocated memory
    free(new_string);
    return -1;          //returning -1 if pattern didn't occur ith time
}

int parent_dfuds(int v){            //function to find the parent of the node at index i
    if(dfuds[v].val==1) return -1;
    int closed = rank_dfuds(")",1,v+1);
    return select_dfuds(")",1,1+closed);
}

int last_child_dfuds(int i){            //function to find the last child of the node at index i
    int v=select_dfuds(")",1,dfuds[i].val); 
    int h=rank_dfuds("(",1,v);
    return select_dfuds("(",1,h);                           
}

int first_child_dfuds(int i){           //function to find the first child of the node at index i
    if(i==0){
        if(dfuds[1].pr=='(') return 2;
        else return -1;
    }
    int v=select_dfuds(")",1,dfuds[i].val-1); 
    if(dfuds[v].pr=='(') return v+1; 
    else return -1;                                             
}

int degree_dfuds(int v){                //function to find the degree of the node at index i
    if(v==1) return select_dfuds(")",1,v)-2;
    return select_dfuds(")",1,v) - select_dfuds(")",1,v-1) - 1;                         
}

int leaf_rank_dfuds(int v){              //function to find the rank of the node at index i
    int g=dfuds[v].val;
    int h=select_dfuds(")",1,g);
    int r=rank_dfuds("))",2,h);
    if(r==0) return 0;
    return r;
}

int leaf_select_dfuds(int i){            //function to find the leaf select 
    return 1+select_dfuds("))",2,i);
}

