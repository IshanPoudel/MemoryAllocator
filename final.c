#include <stdio.h>
#include <stdlib.h>

#define MAX_LINKED_LIST_SIZE 10


static int initialized = 0;
static int rootNode=0;

enum id
{
    PROCESS , HOLE
};

const char * enum_type[] = {
    "PROCESS",
    "HOLE",
    
};

struct Node
{
    int in_use;
    //1 for in_use , 0 for not in use

    size_t size;
    // the size of the node

    void* arena;
    // the pointer to the struct

    int next;
    //the next value it points to

    int previous;
    // the previous value it points too

    enum id type;
};

static struct Node LinkedList[MAX_LINKED_LIST_SIZE];

void printNode(int i)
{
    printf("For the current node: \n");
    printf("Previous : %d  Next: %d \n" , LinkedList[i].previous , LinkedList[i].next);
    printf("LinkedList[%d] : %zu\n " , 0 , LinkedList[i].size);
    printf("Curernt pointer : %p \n" , LinkedList[i].arena);
    printf("The node is a %s\n" , enum_type[ LinkedList[i].type]);
    printf("\n");
}

int mavalloc_init(size_t size)
{
    void* arena = malloc(65535);
    LinkedList[0].arena= arena;
    LinkedList[0].previous=-1;
    LinkedList[0].next=-1;
    initialized = 1;
    LinkedList[0].in_use=1;
    LinkedList[0].size = 65535;
    LinkedList[0].type = HOLE;
    

    printf("Initialized head.\n");
   
    

    return 0;



}



int findFreeNodeInternal()

{
    int i=0;

    for(i=0; i<MAX_LINKED_LIST_SIZE;i++)
    {
        //find a hole or if no hole , find a unused spot.
        if (LinkedList[i].in_use==0 || LinkedList[i].type==HOLE)
        {
            return i;
        }
    }
    
    return -1;
}

int insertNodeInternal(int previous , int current)
{
    // insert a new node after previous .
    // A--B--C--D--E--F--hoLE
    // PREVIOUS=E , CURRENT = H 
    // A--B--C--D--E--H--F--hOLE

    LinkedList[current].previous=-1;
    LinkedList[current].next=-1;

    if (previous>=0)
    {
        printf("I am here when previous >=0 \n");
        int temp;
        LinkedList[current].previous=previous;
        temp = LinkedList[previous].next;
        LinkedList[previous].next=current;
        LinkedList[current].next=temp;
        //implementing a heap , so next process is behind the process.
        LinkedList[current].arena=LinkedList[previous].arena+LinkedList[current].size;
        

    }
    else if (LinkedList[rootNode].previous==-1 && LinkedList[rootNode].next==-1)
    {
        printf("I am adding to the head\n");
        
        //Adding to the head 
        //HOLE
        //Should be: A-Hole
        // LinkedList[rootNode].arena=
        LinkedList[current].arena=LinkedList[rootNode].arena;
    }
    else
    //previouis = -1 but LinkedList[rootnode].next !=-1
    // so , A-B--C--D 
    //Insert E at A.
    //E--A--B--C--D
    {
        printf("I am adding to the head on the last one\n");
        LinkedList[rootNode].previous=current;
        LinkedList[current].next=rootNode;
        LinkedList[current].previous=-1;
        rootNode=current;
        // LinkedList[current].arena

    }
    return 0;

}

void printList()
{
    /** Start at the root of the linked list */
	int i = rootNode;
	
    /** Iterate over the linked list in node order and print the nodes. */
	while (initialized && i != -1 && LinkedList[i].in_use)
	{
		printf("LinkedList[%d]: %zu\n", i, LinkedList[i].size);
        // printNode(i);
		i = LinkedList[i].next;
	}
}


int insertNode(int size)
{

    int index = findFreeNodeInternal();
    printf("I  am trying to add a node id size %d , A free node is at %d\n" , size , index);

    int current = rootNode;
    int previous =-1;
    int ret=-1;

    if (index>=0)
    {
        while (current>=0 && LinkedList[current].in_use && LinkedList[current].type!=HOLE && 
        LinkedList[current].size>size)
        {
            previous=current;
            current=LinkedList[current].next;
        }

        // at this point we have the previous and the current
       
        if(previous>=-1)
        {
            ret = insertNodeInternal(previous , index);
        }
        else if (current==-1)
        {
            ret=insertNodeInternal(LinkedList[previous].previous , index);
        }

        LinkedList[index].size=size;
        LinkedList[index].in_use=1;
        LinkedList[index].type=PROCESS;
        
        
    }

    //first you need to initialize.

    return ret;

}

int removeNodeInternal(int node)
{

    if(node<0 || node>=MAX_LINKED_LIST_SIZE)
    {
        printf("ERROR: Can not remove because it is out of bounds\n");
        return -1;
    }

    if(LinkedList[node].in_use==0)
    {
        printf("ERROR: Can not remove node . It is not in use \n");
    }

    LinkedList[node].in_use=0;
    LinkedList[node].type=HOLE;

    if (node==rootNode)
    {
        rootNode=LinkedList[rootNode].next;
    }

    //if node is in the middle of something.
    if (LinkedList[node].previous>=0)
    {
        // A--B--C--D--E remove c 
        LinkedList[LinkedList[node].previous].next=LinkedList[node].next;
    }

    LinkedList[node].next = -1;
    LinkedList[node].previous=-1;
    //Need to change the arena

    return 0;
}

int removeNode(int size)
{
    int index = rootNode;

    while(index!=-1)
    {
        if(LinkedList[index].size==size)
        {
            return removeNodeInternal(index);
        }
        index=LinkedList[index].next;
    }
    return -1;
}

int main()
{
    mavalloc_init(65534);
    
    insertNode(450);
    insertNode(400);
    insertNode(600);
    insertNode(800);
    insertNode(1000);

    // printList();

    removeNode(450);

    printList();

    insertNode(500);
    
    printf("\n\n");
    printList();
    return 0;
}


