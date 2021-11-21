#include<stdio.h>
#include <stdlib.h>
#include "definitions.h"
#include "LOUDS.h"

struct qnode{
    tree* ptr; struct qnode *next;
}typedef qnode;
qnode* front; // front of the queue
qnode* rear;  // end of the queue


tree* root;
int number_of_nodes;
int ldscount;
struct ldsnode* lds;
char one = '1';
char zero = '0';


// declaration of all the function used
void enq(tree* p ); //enque function for queue
void create_q( tree* p); // function to create queue
tree* deq(); // deque function for queue
int is_qempty(); // function to check whether queue is empty or not
void display_q(); // function to display queue
int ldsrank(char* pattern, int i);  // LOUDDS rank
int ldsselect(char* pattern, int i);  // LOUDDS select
int ldsparent(int x);   
int ldsfirstchild(int x);
int ldslastchild(int x); 
int ldsdegree(int x);   
int ldsrightsibling(int x);
void LOUDS(tree* r); // LOUDS traversal
void ldstraversal(tree* r);  // auxiliary function for LOUDS traversal
void display_lds(void); // function to display LOUDS
void LOUDS_print(tree* r,int n);

//------------------------------------------------//

void LOUDS_print(tree* r,int n)
{
    number_of_nodes=n;
    lds = (struct ldsnode*)malloc(( 2*number_of_nodes +1 )*sizeof(struct ldsnode));
    LOUDS(r);
    display_lds();
    for(int i=0;i<2*n +1;i++)
    {
        if(lds[i].bn=='1')
        {
            printf("Value of current node: %d\n",lds[i].posn);
            if(ldsparent(i)==-1)
            printf("Root itself\n");
            else
            printf("parent = %d\n",lds[ldsparent(i)].posn);

            if(ldsfirstchild(i)==-1)
            printf("NULL first child!\n");
            else 
            printf("first child = %d\n",lds[ldsfirstchild(i)].posn);

            if(ldslastchild(i)==-1)
            printf("NULL last child!\n");
            else printf("last child = %d\n",lds[ldslastchild(i)].posn);

            if(ldsrightsibling(i)==-1)
            printf("NULL right sibling\n");
            else printf("right sibling = %d\n",lds[ldsrightsibling(i)].posn);

            printf("degree is %d\n",ldsdegree(i));
        }
    }

}

void create_q(tree *p)
{
    front=(qnode*)malloc(sizeof(qnode));
    front->ptr= p;
    rear = front;
    front->next = NULL;
}
// enqueue function of the queue
void enq(tree *p)
{
    if (front==NULL)
    {
        create_q(p);
        rear=front;
        return;
    }
    qnode* temp = (qnode*)malloc(sizeof(qnode));

    temp->ptr = p;
    temp->next = NULL;

    rear->next = temp;
    rear = temp;

}
//dequeue function of the queue
tree* deq()
{
    if (front==NULL)
        return NULL;
    qnode* temp = front;
    tree* x = front->ptr;
    front= front->next;
    free(temp);

    return x;
}
// checks if queue is empty
int is_qempty()
{
    if(front==NULL)
    return 1;
    else return 0;
}
// auxiliary function to display queue used in breadth first search
void display_q()
{
    qnode *temp;
    temp = front;
    while(temp!=NULL)
    {
        printf("%d ",temp->ptr->data);
        temp = temp->next;

    }
}

void LOUDS(tree* r)// main function of LOUDS TRAVERSAL
{
    lds[0].bn = '1'; lds[0].posn= r->data;
    lds[1].bn = '0';
    ldscount = 2;
    ldstraversal(r);

}
void ldstraversal(tree* r) // auxiliary function of LOUDS TRAVERSAL
{
    int x = r->number_of_children;
    int i;
    for(i=0;i<x;i++)
    {
        lds[ldscount].posn = (*(r->children +i))->data;
       lds[ldscount].bn = '1'; 
       enq(*(r->children +i));
       ldscount++;
    }
    lds[ldscount++].bn = '0';
    if(is_qempty())
    return;
    else 
    ldstraversal(deq());
}

// function to display the representation and values stored 
void display_lds(void){
    printf("LEVEL ORDERED UNARY DEGREE SEQUENCE (LOUDS) REPRESENTATION\n");
    for(int i=0;i<2*number_of_nodes+1;i++){
        if(lds[i].bn=='1')
        {
             printf("%c",lds[i].bn);printf("(%d) ",lds[i].posn);
        }
        else printf("%c ",lds[i].bn);
    }
    printf("\n");
}

int ldsrank(char* pattern,int i){
    int size = 1;
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
        new_string[p]=lds[p-(size+1)].bn;
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

int ldsselect(char* pattern,int i){
    int size = 1;
    int c=0;
    int p=0;
    int a, b, k;
    int l=size+1+(2*number_of_nodes + 1);
    int * Z_array=(int *)malloc(l*sizeof(int));
    char * new_string=(char*)malloc((l+1)*sizeof(char));
    while(p<size){
        new_string[p]=pattern[p];
        p++;
    }
    new_string[p]='$';
    p++;
    while(p<l){
        new_string[p]=lds[p-(size+1)].bn;
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

int ldsfirstchild(int x)
{
    x=x+1;
    x = ldsselect(&zero,ldsrank(&one,x));
    if(lds[x].bn=='0')
    return -1;
    else return x;
}

int ldslastchild(int x)
{
    x=x+1;
    x = ldsselect(&zero,ldsrank(&one,x)+1)-2;
    if(lds[x].bn=='0')
    return -1;
    else return x;
}

int ldsdegree(int x)
{
    if(ldslastchild(x)==-1 && ldsfirstchild(x) ==-1)
    return 0;
    return ldslastchild(x)-ldsfirstchild(x)+1;
}

int ldsrightsibling(int x)
{

    if(lds[x+1].bn=='0')
    return -1;
    else return x+1;
}

int ldsparent(int x)
{
    x=x+1;
   x = ldsselect(&one,ldsrank(&zero,x))-1;
   if(x<0)
   return -1;
   else if(lds[x].bn=='0')
    return -1;
    else return x;
}


