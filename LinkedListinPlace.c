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

//Insert the node located at current roght after the node indexed by previous. 
//i.e LinkedList[previous].next and LinkedLiST[LinkedList[previous].next].previous values are updated.

//  A ------ B ------- F ------- D Insert C between B and F . previous = 1 , current = could be anything.
int insertNodeInternal(int previous , int current)
{
    LinkedList[current].previous = -1;
    LinkedList[current].next = -1;

    //Start from the previous node

    if (previous >=0)
    {
        int temp;

        /* Connect the previous node with the current node. 
        If it exists and store off previous->next somewhere else so that we use it later. 
        */
       LinkedList[current].previous = previous;
       temp = LinkedList[previous].next;
       LinkedList[previous].next = current;
       LinkedList[current].next = temp;

       

       
    }
    
    else if (LinkedList[rootNode].previous == -1 && LinkedList[rootNode].next == -1)
    {
        // make current == rootnode?

    }

    else
    {
        //if previous less than 0 
        // A ----- B ----- F ----- D . Insert C at the position of  A -> C---A ---B ---F ---F
        //if previous value = -1 , replace the root node.

        LinkedList[rootNode].previous = current;
        LinkedList[current].previous = -1;
        LinkedList[current].next = rootNode;
        rootNode = current;

    }

    return 0;
}


// removeNode Internal , remove a node from the list
 
//  A -- B -- C --D , REMOVE c . B->NEXT SHOULD POINT TO D , D->PREV should point to B , Don't remove C
int removeNodeInternal(int node)
{

    //node is the value?

    if (node < 0 || node >= MAX_LINKED_LIST_SIZE)
    {
        printf("ERROR: Can not remove node %d because it is out of our array bounds"
			   " of 0 ... %d\n", node, MAX_LINKED_LIST_SIZE);
		return -1;
    }

    if (LinkedList[node].in_use==0)
    {
        printf("Eroor : Cannot remove node %d. It is not in use. \n" , node);
        return -1;
    }

    //Make the index not in use , so it can be overwritten later.

    LinkedList[node].in_use=0;

    //get it's prev and next.
    if (node==0)
    {
        rootNode = LinkedList[rootNode].next;
    }

    LinkedList[LinkedList[node].previous].next = LinkedList[node].next;
    //change the LinkedList[node].next prev to 
    //Don't need to currently because we are only going one way.

    //change it's next and prev.
    LinkedList[node].next=-1;
    LinkedList[node].previous=-1;

    return 0;
    

}


//removeNode is finding the value and getting the index.
//on removeInternalNode it is about replacing the node->next and prev values. 
int removeNode(int value)
{
    //given the value , we need to find it's node's index and then use removeNodeInternal

    int index= rootNode;

    while(index!=-1)
    {
        if (LinkedList[index].value==value)
        {
            return removeNodeInternal(index);
        }

        index = LinkedList[index].next;
    }

    return -1;

}


int insertNode(int value)
{

    //find free node
    //start from headnode and traverse until you find an empty one. 
    // get previous and current index. 
    // on insert Internal Node , insert the node in between the previous and the current one and shift everything to the right. 

    // find a free internal node. 
    int index = findFreeNodeInternal();

    //Start from the rootnode 
    int current = rootNode;
    // At the beginning because you start from the rootnode , your prev = -1
    int previous = -1;
    

    //return value 
    int ret = -1;

    //If it is the firstnode that has been initialized , make sure that it is the rootnode. 

    if (initialized ==0)
    {
        LinkedList[0].previous=-1;
        LinkedList[0].next=-1;
        LinkedList[0].value = value;
        initialized = 1;
    }

    //but if the index has already been intialized. 
    //i,.e the rootnode is already there and there is space


    if (index >= 0)
    {
        while (current >=0 && LinkedList[current].in_use==1 && LinkedList[current].value < value)
        {
            previous = current;
            current = LinkedList[current].next;
        }

        //you reach a point where current is not in use .
        // if previous >=-1 ile we found an empty node . aka  A --- B ----
        if (previous >=-1)
        {
            ret = insertNodeInternal(previous ,  index);
        }

        else if (current == -1)
        //we ran off the end of the list
        {
            ret = insertNodeInternal(LinkedList[previous].previous , index);


        }

        //after our new node is marked , we need it to set it as being used.
        LinkedList[index].value = value;
        LinkedList[index].in_use=1;
    }

    return ret;
    
}

void printList()
{
    int i = rootNode;

    while (initialized && i !=-1 && LinkedList[i].in_use)
    {
        printf("LinkedList[%d] : %d\n" , i , LinkedList[i].value);
        i = LinkedList[i].next;
    }

}

int main()
{
    
    insertNode(100); 
	insertNode(120);
	insertNode(90);
	insertNode(110);
	insertNode(85);
	insertNode(87);
	insertNode(84);
	insertNode(10);
	insertNode(500);

    printList();
}