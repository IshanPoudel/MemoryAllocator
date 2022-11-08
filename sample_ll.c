//have one node allocated at first. 
// once you have a process or a hole , you change the pointer to the first node and add it to the arraylisy.
//by adding to the arraylist it means changing -1 to positive.

// ypu create a new node and insert it. 

//when you allocate/initialize you have the fist one as the starting list. 



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 10

enum id
{
    PROCESS ,
    HOLE 

};


//need to have a size

// when you allocate , you allocate the linked list with a hole of size max

//when you insert stuff on it , you see if it a hole and ahead and then add stuff to it.

struct Node
{

    

   
    //stores the pointers actual value. aka the number.

    int size;

    

    struct Node* prev;

    struct Node* next;

    enum id type;


    
    
};

 struct Node *head;

void allocate(size_t size)
{

   

    head = (struct Node *)malloc(size);
    head->size = size;
    head->prev=NULL;
    head->next = NULL;
    head->type = HOLE;

    printf("Added a head %p\n" , &head );
    



    return;



}



void insert_check(int size)
{

    struct Node *temp2;
    struct Node *temp = head;

    

    temp2->size=size;
    temp2->type=PROCESS;
    

    
    
    //if head is NULL.

    //iterste until you find a hole.

    //if there is a hole in the head and is bigger than the requested size
    if (head->type== HOLE & head->size > size)
    {
        printf("The head has no process\n");
        //have temp2 be the head.
        temp2->prev = NULL;
        head = temp2;

        printf("I am here\n");

        

        //create a node to store the remaining hole.
        temp->size = temp->size-size;
        temp->prev = head;
        temp->next = NULL;
        temp->type= HOLE;

        head->next = temp;

        printf("%p ----------- %p with size %d --------- %p\n" , head->prev ,head , head->size , head->next);
        printf("%p ----------- %p with size %d  --------- %p\n" , temp->prev , temp  , temp->size , temp->next);

       

        
        return;

        


    }

    while (temp!=NULL)
    {
       if (temp->type == HOLE)
       {

        printf("\n\n");

        printf("The current temp has free memory \n");

        printf(" Previous %p\n" , temp->prev);
        printf(" It's value %p\n" , temp);
        printf(" Next %p\n" , temp->next);
        printf("Free size %d\n" , temp->size);
        printf("\n");

        //add stuff. 

        struct Node *newNode;
        newNode->prev = temp;
        newNode->size = temp->size - size;
        newNode->type = HOLE;
        newNode->next = NULL;

        //the new struct should be in front of the hole.
        temp->size = size;
        temp->type = PROCESS;
        temp->next = newNode;

        
        


        //insert a new node with remaining memory.

       


        // //the newly inserted struct should point to the hole
        // temp2->next = temp;
        // //the struct shou
        // temp2->prev = temp->prev;


        // //decrease the size of the hole and have it point back to the newly added struct.
        // temp->size = temp->size - size;
        // temp->prev = temp2;
        
        
        
        printf("Added  a new struct at\n");
        printf(" %p -------------- %p with size %d ------------- %p" , temp->prev , temp , temp->size , temp->next);

        
        
       

        
        

       }
       temp = temp->next;
    }

    


    // printf("%d\n" , temp->type);
    // printf("%p\n" , temp->prev);
    // printf("%d\n" , temp->size);
    // printf("%p\n" , temp->next );
    // // printf(" %p --------- %d --------- %p" , temp->prev , temp->size , temp->next);

    // printf("The current size of temp2 is %d\n" , temp2->size);
    // printf("The current size of temp is %d\n" , temp->size);
    // printf("%p\n" , temp);
    // temp2->next = temp;
    // printf("temp2->next is %p\n" , temp2->next);
    // temp->size = temp->size - temp2->size;
    // printf("The current size of temp is %d\n" , temp->size);
    // temp2->prev = temp->prev;


    // if (temp->type==HOLE)
    // {
    //     printf("I am here\n");
    //     // //insert temp2 in temps position and move temp furthwr down.
    //     // temp2->next = temp;
    //     // printf("I assing ed temp2->next");
    //     // temp->size = temp->size - temp2->size;
    //     // temp2->prev = temp->prev;


    //     //insert it there


    // }


    
    

}





int main()
{
    allocate(10*sizeof(struct Node));
    
    //insert 24 bytes.
    insert_check(24);
    insert_check(30);
    
    // print_ll();


    

    
}