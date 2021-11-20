#include<stdio.h>
#include <stdlib.h>


struct Tree{
    int data;
    int number_of_children;
    struct Tree** children; 
}typedef tree;

struct ldsnode{
    int posn;
    char bn;
};


struct qnode{
    tree* ptr; struct qnode *next;
}typedef qnode;
qnode* front; // front of the queue
qnode* rear;  // end of the queue


tree* root;
int number_of_nodes;
int ldscount;
struct ldsnode* lds;



// declaration of all the function used
void enq(tree* p ); //enque function for queue
void create_q( tree* p); // function to create queue
tree* deq(); // deque function for queue
int is_qempty(); // function to check whether queue is empty or not
void display_q(); // function to display queue
int ldsrank(char typ, int i);  // LOUDDS rank
int ldsselect(char type, int i);  // LOUDDS select
int ldsparent(int x);   
int ldsfirstchild(int x);
int ldslastchild(int x); 
int ldsdegree(int x);   
int ldsrightsibling(int x);
void LOUDS(tree* r); // LOUDS traversal
void ldstraversal(tree* r);  // auxiliary function for LOUDS traversal
void display_lds(void); // function to display LOUDS


//------------------------------------------------//

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
    // for(i=0; i<x;i++)
    // {
    //     enq(*(r->children +i));
    // }
    if(is_qempty())
    return;
    else 
    ldstraversal(deq());
}

// function to display the representation and values stored 
void display_lds(void){
    for(int i=0;i<2*number_of_nodes+1;i++){
        printf("%c ",lds[i].bn);
    }
    printf("\n");
    for(int i=0;i<2*number_of_nodes;i++){
       if(lds[i].bn=='1')
        printf("%d ",lds[i].posn);
       else
        printf(" ");
    }
    printf("\n");
}


int ldsrank(char typ, int i)
{
    int count =0;
    for(int j=0;j<i;j++)
    {
        if(lds[j].bn == typ)
        count++;
    }
    return count;
}

int ldsselect(char type, int i){
    int j;
    for(j = 0; j < 2*number_of_nodes+1 && i>0 ; j++){
        if(lds[j].bn == type){
            i--;
        }
    }
    return j;
}
int ldsfirstchild(int x)
{
    x=x+1;
    x = ldsselect('0',ldsrank('1',x));
    if(lds[x].bn=='0')
    return -1;
    else return lds[x].posn;
}
int ldslastchild(int x)
{
    x=x+1;
    x = ldsselect('0',ldsrank('1',x)+1)-2;
    if(lds[x].bn=='0')
    return -1;
    else return lds[x].posn;
}

int ldsdegree(int x)
{
    return ldslastchild(x)-ldsfirstchild(x)+1;
}
int ldsrightsibling(int x)
{

    if(lds[x+1].bn=='0')
    return -1;
    else return lds[x+1].posn;
}
int ldsparent(int x)
{
    x=x+1;
   x = ldsselect('1',ldsrank('0',x))-1;
   if(lds[x].bn=='0')
    return -1;
    else return lds[x].posn;
}



int main()
{
    scanf("%d",&number_of_nodes);
    lds = (struct ldsnode*)malloc(( 2*number_of_nodes +1 )*sizeof(struct ldsnode));
    LOUDS(root);  // root of the tree is passed as an argument

}