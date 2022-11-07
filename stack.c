#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 10

struct Node
{
    int size;
    struct Node* next;
    struct Node* prev;

};

struct Node* head;
struct Node* temp;

void allocate(int size)
{

    //initialize the header file.
    head = malloc( 10* sizeof(struct Node));
    head->next=NULL;
    head->prev=NULL;
    head->size = size;

}


void insert(int size)
{

    

    

    //iterate until you reach the end.
    
    //go until you reach null

    temp = head; 
    while(temp!=NULL & temp->next !=NULL)
    {
        temp = temp->next;
    }

    printf("I am here. The address of temp is %p\n" , temp);
    printf("The address of the head is %p\n" , head);
    printf("The address of the next value is %p\n" , head->next);
    head->next->size = 10;
    //How to enter values without getting segmentation fault. 
    //How to enter values without not getting seg fault.

   

}
int main()
{

    allocate(1000);
    insert(20);

    return 0;
}