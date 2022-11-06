#include <stdio.h>
#define MAX_LINKED_LIST_SIZE 65534

static int initialized = 0; //to see if the list is initialized
static int rootNode = 0;  // to keep track of the index of the rootnode.



enum id
{
    PROCESS ,
    HOLE 

};


struct Node
{
    // to see if the value has been initialized
    int in_use ;
    //the actual value aka main thing we care about
    int value;
    
    // the previous node it points too. References the index.
    int previous;
    
    //references the next node it points too
    int next;

    // To know if it is a process or a hole.
    // enum id type;

    //Need to keep track of if the heap block is free or in use. We could just use the enum.
};
//Initilaize a  array of structs of size  MAX_LINKED_LIST_SIZE
static struct Node LinkedList[MAX_LINKED_LIST_SIZE];


//Need to find an internal node for iuse.


int findFreeNodeInternal()
{
    //Iterate through the linked list to find a node (actually an array index ) which has not been used.

    for (int i=0; i<MAX_LINKED_LIST_SIZE;i++)
    {
        if (LinkedList[i].in_use==0)
        {
            return i;
        }

    }

    return -1;
}

//insertnode in the internal. 

void insertNode(int value)
{

    //First need to find the head of the linked node.
    
    if (initialized==0)
    {

        printf("I am in the head\n");
        LinkedList[rootNode].value = value;
        printf("I am here");
        LinkedList[rootNode].previous =-1;
        LinkedList[rootNode].in_use =1;
        initialized =1;
        printf("I am done=");
        

    }
    else
    {
        // I am adding
        // the rootnode is in use 
        // find the next freenode. 
        int index = findFreeNodeInternal();
        //you need to connect it to the previous. 
        LinkedList[index].value =value;
        LinkedList[index].in_use = 1;
        //need to link the previous. 
        int temp = rootNode;
        int next_index = LinkedList[temp].next;

        while (LinkedList[next_index].in_use!= -1) 
        {
           
           temp = LinkedList[temp].next;
           next_index = LinkedList[temp].next;
            
            
        }

        //at this point next_index is empty. But we need to know the one previous to it. 
        // temp is full , next_index is empty.
        printf("I found temp %d\n" , temp);

        //We join our value with temp.
        LinkedList[index].previous = temp;
        

    }

}

int main()
{
    
    insertNode(100);
    insertNode(200);
}