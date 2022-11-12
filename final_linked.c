#include <stdio.h>
#include <stdlib.h>
#define MAX_LINKED_LIST_SIZE 65534

static int initialized = 0;
static int rootNode = 0;


enum id
{
    PROCESS , HOLE
};

struct Node
{
    int in_use;
    int previous;
    int next;

    //have one for size
    size_t size;

    //have one for id
    enum id type;

    //have one for pointer
    void* arena;
};

//initialize an array of structs
static struct Node LinkedList[MAX_LINKED_LIST_SIZE];

int findFreeNodeInternal()
{
    //Needs to not be in use and needs to not be a process. 

    for (int i=0; i<MAX_LINKED_LIST_SIZE;i++)
    {
        if (LinkedList[i].in_use==0 && LinkedList[i].type==HOLE)
        {
            return i;
        }
    }

    return -1;
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
    LinkedList[0].type = PROCESS;

    printf("Initialized head.\n");
    printf("Previous : %d  Next: %d \n" , LinkedList[0].previous , LinkedList[0].next);
    printf("LinkedList[%d] : %zu\n " , 0 , LinkedList[0].size);
    printf("Curernt pointer : %p \n" , LinkedList[0].arena);
    printf("The linkedlist is a %d\n" , LinkedList[0].type);

    return 0;



}

int insertNode(int value)
{
    //need to insertvalue at the beginnig. 

    //initialize mavallloc if not initialized.
    return 0;

    
}


int main()
{
    //First initalize with a node of size 65535 .
    mavalloc_init(65535);

    return 0;
}
