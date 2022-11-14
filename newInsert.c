#include <stdio.h>
#include <stdlib.h>
#define MAX_LINKED_LIST_SIZE 65534

static int initialized=0;
static int rootNode=0;

enum id
{
    PROCESS , HOLE
};

struct Node
{
    int in_use;
    int previous;
    int next;

    size_t size;

    enum id type;

    void* arena;

};

const char * enum_type[] = {
    "PROCESS",
    "HOLE",
    
};

static struct Node LinkedList[MAX_LINKED_LIST_SIZE];


void printNode(int index)
{
    printf("\n");
    printf("LinkedList[%d] is a %s of size %zu\n" , index , enum_type[LinkedList[index].type] , LinkedList[index].size);
    printf("LinkedList[%d] ------- LinkedList[%d] -------- LinkedList[%d]\n" , LinkedList[index].previous , index , LinkedList[index].next);
    printf("LinkedList[%d] is located at %p\n" , index , LinkedList[index].arena );
    printf("\n");

}

void printList()
{
    int index=rootNode;
    printf("\n\n");

    while( (index != -1) & (LinkedList[index].in_use))
    {
        printNode(index);
        index=LinkedList[index].next;
    }

}

int mavalloc_init(size_t size)
{
    void* arena = malloc(65535);
    LinkedList[0].arena= arena;
    LinkedList[0].previous=-1;
    LinkedList[0].next=-1;
    LinkedList[0].in_use=1;
    LinkedList[0].size = 65535;
    LinkedList[0].type = HOLE;
    initialized = 1;
    
    printf("-----------------------------------------------------\n");
    printf("Initialized head\n");
    printNode(0);
    printf("-----------------------------------------------------\n");
   
    

    return 0;



}


//find freeNodeInternal which is bigger than size_t
int findfreeNodeInternal(size_t size)
{
    for(int i=0; i<MAX_LINKED_LIST_SIZE;i++)
    {
        if (LinkedList[i].in_use==0 )
        {
            
            printf("\n I found a free node at %d to insert process of size%zu\n" , i , size);
            printNode(i);
            
            return i;

        }

        
    }

    return-1;
}

void printState()
{

    int i = rootNode;

    printf("\t\tVISUALIZATION\t\t");
	
    /** Iterate over the linked list in node order and print the nodes. */
	for (int i=0; i<2;i++)
    {
        printNode(i);
    }
}
int insertNodeInternal(int previous , int current , int size )
{
    //Insert node after previous
    //A--B--C--D--E--F--Hole
    //Previous=E , Current=H
    //A--B--C--D--E--H--F--HOLE

    // Insert the process after previous .
    // The node after previous is always a hole.
    // Insert process , add hole.
    // Insert at current.


    LinkedList[current].next=-1;
    LinkedList[current].previous=-1;

    

    if (LinkedList[rootNode].previous==-1 && LinkedList[rootNode].next==-1)
    {
        printf("I am adding when everything is empty. Need to initialize with a hole\n");
        LinkedList[current].next=rootNode;
        LinkedList[rootNode].previous=current;
        LinkedList[current].previous=-1;

        //make linkedlist[rootnode] a hole.//Only come here when the hole size is bigger then requested size
        LinkedList[rootNode].size=LinkedList[rootNode].size-size;
        LinkedList[rootNode].type=HOLE;
        LinkedList[rootNode].next=-1;
        rootNode=current;
       
        // printf("The next free is at %d\n" , next_free);
        

    }
    else if (previous>=0)
    {
        
        printf("I am here when previous >= 0  . The value of previous is %d. \n\n" , previous);
        
        // A-Hole , Insert B
        
        // B-A-Hole
        //prev=A
        //INSERT C such that B--A--C--HOLE

        //  B--A--(500) C is also 500.
        
        int  index_of_hole = LinkedList[previous].next;
        if (LinkedList[index_of_hole].size==size)
        {
            printf("I found the perfect hole\n\n");
            current=index_of_hole;
            LinkedList[current].type=PROCESS;
            LinkedList[current].previous=previous;
            LinkedList[previous].next= current;
            
            

        }
        else
        {
            
            printf("The index of the hole is %d\n" , index_of_hole);
            
            

            LinkedList[current].previous=previous;
            printf("Set LinkedList[%d].previous to %d\n" , current , previous);

            LinkedList[previous].next=current;
            printf("Set LinkedList[%d].next to %d\n" , previous , current);

            LinkedList[current].next=index_of_hole;
        
            
            
            
            // LinkedList[current].previous=LinkedList[previous].previous;
            // printf("Added Linkedlist[%d].previous is Linkedlist[%d]\n" , current , LinkedList[previous].previous);
            // LinkedList[current].next=previous;
            // LinkedList[previous].next=index_of_hole;
            // LinkedList[previous].previous=current;
            //Now change the values of the hole.
            
            LinkedList[index_of_hole].type=HOLE;
            // LinkedList[index_of_hole].next=;
            LinkedList[index_of_hole].previous=current;
            //set arena
            LinkedList[index_of_hole].size=LinkedList[index_of_hole].size-size;

        }

        
        

    }
    else 
    {
         //if you are adding to an hole at the front 
        // HOLE  and adding node B
        // B----HOLE
        // if (LinkedList[previous].type==HOLE)
        // {

        // }
        printf("I am adding to the front of the head\n");
        printf("The current index is %d , the previous index is %d \n" , current , previous);
        
       
        //Create a new node to enter the value
        LinkedList[current].next=rootNode;
        LinkedList[rootNode].previous=current;
        LinkedList[current].previous=-1;

        //make linkedlist[rootnode] a hole.//Only come here when the hole size is bigger then requested size
        LinkedList[rootNode].size=LinkedList[rootNode].size-size;
        LinkedList[rootNode].type=HOLE;
        rootNode=current;

        

    }

    return 0;
}

int insertNode(int size)
{
    int index=findfreeNodeInternal(size);

    int current = rootNode;
    printf("The current root is at index %d\n" , current);
    int previous = -1;
    int ret=-1;
    
    //we need to insert at index.
    //need to iterate until we find index?
    //need to find where to insert it to end of

    //need to iterate until you find a hole which is bigger than what you need and add it there.

    while( current>=0 && LinkedList[current].in_use )
    {
        printf("Current node at index %d is a %s and has size %zu\n" , current , enum_type[LinkedList[current].type] , LinkedList[current].size);
        // if(LinkedList[current].size>size && LinkedList[current].type==HOLE)
        if(LinkedList[LinkedList[current].next].size>=size && LinkedList[LinkedList[current].next].type==HOLE)
        {
            
            printf("MATCH: Current node at index %d is a %s and has size %zu\n" , current ,enum_type[LinkedList[current].type] , LinkedList[current].size);
            printf("MATCH: Next index is a hole\n");
            previous=current;
            break;
        

        }
        current=LinkedList[current].next;
        
        
    }

    //at this point the previous is in_use. 
    printf("The previous value %d  is currently filled with a process and the next one is either not in use or a hole . \n" , previous );
    if (previous>=0)
    {
         printNode(previous);

    }

    if (previous>=-1)
    {
        ret = insertNodeInternal(previous , index , size );
        //we insert a not between previoud and index which is always a process.
    }
    else if (current==-1)
    {
        // We ran of the end of the list. 
        // If max of five then current = E.next which is -1 , previous = E
        //aka A-B-C-D-E. Insert between E.prev aka D and the index
        ret = insertNodeInternal(LinkedList[previous].previous , index , size );


    }

    //After our node is linked , we need to change some node parameters. 
    LinkedList[index].size=size;
    LinkedList[index].in_use=1;
    LinkedList[index].type=PROCESS;

    
    //Updating arena
    //index contains our current inserted node. 
    //index starts from the nex node's pointer.
    //the previous pointer 
    int next = LinkedList[index].next;
    LinkedList[index].arena = LinkedList[next].arena;
    LinkedList[next].arena = LinkedList[index].arena+ LinkedList[index].size;


    // printf("\nTWO NEW NODES THAT WERE CREATED ARE:\n");
    
    // printNode(index);
    // printNode(LinkedList[index].next);

    


   
    
    return 0;


}

int removeNodeInternal(int node)
{
    if (node<0 || node>= MAX_LINKED_LIST_SIZE)
    {
        printf("Error:\n");
    }

    if (LinkedList[node].in_use==0)
    {
        printf("Cannot remove node. Not in use \n");
    }

    printf("I am trying to remove a node at index %d\n" , node);
    

    LinkedList[node].in_use=1;
    LinkedList[node].type=HOLE;
    
    

    

    //do i change the arena when i remove a node.

    return 0;
    

}

int removeNode(int size )
{
    int index = rootNode;

    while(index!=-1)
    {
    
        if (LinkedList[index].size==size)
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
    insertNode(100);
    insertNode(200);
    insertNode(800);
    insertNode(600);
    insertNode(1000);
    
    
   
    
    insertNode(10);
    removeNode(800);
    insertNode(800);
    
    removeNode(600);
    insertNode(50);
    insertNode(550);
    printList();
    return 0;

}