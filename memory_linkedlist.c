#include <stdio.h>

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
    int size;
   
    int previous;
    int next;

};

//declare a array of structlost and call it linkedlist.

static struct Node LinkedList[MAX_LINKED_LIST_SIZE];

int findInternalNode()
{

    //iterates through the linked list and see which one has in_use equal to -1

    for (int i=0; i<MAX_LINKED_LIST_SIZE;i++)
    {
        if (LinkedList[i].in_use==0 )
        {
            return i;
        }
        
        
    }

    return -1;

}


//will insert ar current , right after previous.
int insertInternalNode(int previous , int current)

{
    LinkedList[current].previous=-1;
    LinkedList[current].next=-1;

    if (previous>= 0)
    {
        int temp;

        // A -- B -- C --D Insert E between c and d. previous -c 
        LinkedList[current].previous=previous;
        temp = LinkedList[previous].next;
        LinkedList[previous].next=current;
        LinkedList[current].next = temp;
    }
    else if ( LinkedList[rootNode].previous == -1 && LinkedList[rootNode].next == -1)
	{
		/* Do nothing since this is the first node in the linked list. */
	}
    else
    {
        //We are at replacing the root node.
        LinkedList[rootNode].previous = current;
        LinkedList[current].previous =-1;
        LinkedList[current].next = rootNode;
        rootNode = current;
    }

    return 0;



}

int insertNode(int size)
{

    //insert node of size size. 

    //first you need to find a free internal node.

    int index = findInternalNode();
   

    //find a free internal node.
    int current = rootNode;
    int previous = -1;

    int ret = -1;

    if (initialized==0)
    {
        
        LinkedList[0].previous=-1;
        LinkedList[0].next = -1;
        initialized = 1;
    }
    
    if (index >= 0)
    { 
        
        //Since it is always sorted form the beginning. 
        while (current > 0 && LinkedList[current].in_use && LinkedList[current].size< size )
        {
            //if size is smaller it automatically gets added to the top of the list.
            previous=current;
            current = LinkedList[current].next;


        }

        //at this point previous is a node and current points to a free node which has not been in use
        if(previous >= -1)
        {
            ret = insertInternalNode(previous , index);
            //We are inserting at the position index.

        }

        else if (current==-1)
        {
            ret = insertInternalNode(LinkedList[previous].previous , index);
        }

        LinkedList[index].size = size;
        LinkedList[index].in_use = 1;
    }

    return ret;
}


int removeNodeInternal(int node)
{

    //Remove the index from that place and join everything else.

    if (node<0 || node >= MAX_LINKED_LIST_SIZE)
    {
        return -1;
    }

    if (LinkedList[node].in_use==0)
    {
        printf("Erro can not remove node %d. It is not in use \n" , node);
    }

    LinkedList[node].in_use=0;

    if(node==rootNode)
    {
        rootNode=LinkedList[rootNode].next;

    }


    if (LinkedList[node].previous>=0)
    {
        //  A- B - C -D E -F
        // REMOVE C.
        // link b with d and d with b 
        LinkedList[LinkedList[node].previous].next = LinkedList[node].next;
        LinkedList[LinkedList[node].next].previous= LinkedList[node].previous;


    }

    //chaneg the next and prev of the node to -1
    LinkedList[node].next=-1;
    LinkedList[node].previous=-1;

    return 0;

}

int removeNode(int value)
{
    int index = rootNode;

    while (index!= -1)
    {
        if(LinkedList[index].size==value)

        {
            return removeNodeInternal(index);

        }

        index = LinkedList[index].next;

    }

    return -1;

}

void printList()
{
    /** Start at the root of the linked list */
	int i = rootNode;
	
    /** Iterate over the linked list in node order and print the nodes. */
    printf("%d , %d " , initialized , LinkedList[i].in_use);
	while (initialized && i != -1 && LinkedList[i].in_use)
	{
		printf("LinkedList[%d]: %d\n", i, LinkedList[i].size);
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

	printf("\n\nPrint the sorted Linked List\n\n");
	printList();

	removeNode(84);
	
	printf("\n\nTrying to remove an array element that is out of bounds\n");
	printf("This should print two errors.\n");
	removeNodeInternal(-1);
	removeNodeInternal(80000);

	printf("\n\nUpdated Linked List with Node with value 84 deleted\n\n");
	printList();

	removeNode(500);
	insertNode(600);
	printf("\n\nUpdated Linked List with the last Node removed and replaced with a value of 600 \n\n");
	printList();

	removeNode(10);
	printf("\n\nUpdated Linked List with the first Node removed \n\n");
	printList();

	insertNode(2);
	printf("\n\nUpdated Linked List with a new root node added with a value of 2 \n\n");
	printList();

	return 0; 

}