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

void insert_h(int size)
{
    struct Node *temp2;
    struct Node *temp = head;

    while (temp!=NULL)
    {
        if (size<temp->size & temp->type == HOLE)
        {
            printf("I am in inside the if condition. The current node is a hole. %p\n" , temp);
            //create a new linked list here and insert it
            //trying to add data to temp2;
            
            printf("I am here");
            temp2->size = size;

            printf("I am here");
            
            
            //chenge the size of the list
            temp->size = temp->size - size;
            //change prev.
            temp2->prev = temp->prev;

        }

        temp=temp->next;
    }
}

void insert_check(int size)
{

    struct Node *temp2;
    struct Node *temp = head;

    printf("I am here\n");

    temp2->size=size;
    temp2->type=PROCESS;
    

    printf("I am here after assigning values\n");
    
    //iterste until you find a hole.

    while(temp!=NULL & temp->next != NULL )
    {
        temp=temp->next;
    }


    printf("%d\n" , temp->type);
    printf("%p\n" , temp->prev);
    printf("%d\n" , temp->size);
    printf("%p\n" , temp->next );
    // printf(" %p --------- %d --------- %p" , temp->prev , temp->size , temp->next);

    printf("The current size of temp2 is %d\n" , temp2->size);
    printf("The current size of temp is %d\n" , temp->size);
    printf("%p\n" , temp);
    temp2->next = temp;
    printf("temp2->next is %p\n" , temp2->next);
    temp->size = temp->size - temp2->size;
    printf("The current size of temp is %d\n" , temp->size);
    temp2->prev = temp->prev;


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

void insert(int size)
{

    //go until you reach a hole.
    // go until you find a hole. 
    
    struct Node *temp2;

    struct Node *temp = head;
    //initialized a temp to be head.

    while (temp!=NULL & temp->next!=NULL )

    {
        temp = temp->next;

    }

    //at this point you have reached a point where the temp->next is null.

    // temp->next will have your process.

    if (size < temp->size & temp->type == HOLE)

    {
        
        temp->next = head; 
        //temp will point to head.
        
        //you can have your process at the beginning and the next one is whole.
        temp->size = size;
        
        temp->type = PROCESS;
        
        temp->prev = head->prev;
        printf("The previous of temp is %p\n" , temp->prev);

        //decrease  the size of the next thing to be smaller.
        temp->next->size = head->size - size;
        printf("The value of the next bit is changed to %d\n" , temp->next->size);

        printf("The current value of the head is %p\n" , head);
        
        // change the head to temp.
        head = temp;
        printf("The current value of the head is %p\n" , head);
        printf("Added a new node\n");
        printf("Current head : %p , %d\n" , &head , head->size);
        printf("The node after head is %p\n" , head->next);
        printf("The value in the node after the head is %d\n" , head->next->size);
        printf("----%p-----------  %d  ----------%p\n" , head->next->prev , head->next->size , head->next->next);



    }
    

    
}

void print_ll()
{

    // struct Node *temp = head;
    // // print

    // while(temp!=NULL & temp->next!=NULL)
    // {
    //     printf(" %p -------- %d -----------%p\n" , temp->prev , temp->size , temp->next);
    //     temp = temp->next;

    // }

    printf("%d\n" , head->size);
    printf("%d\n" , head->next->size);
}

int main()
{
    allocate(10*sizeof(struct Node));
    
    //insert 24 bytes.
    insert_h(24);
    // print_ll();


    

    
}