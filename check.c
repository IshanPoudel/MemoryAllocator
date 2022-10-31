#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 10

struct Node
{

    

    int value;
    //stores the pointers actual value. aka the number.

    

    int *start;

    int *end;


    
    
};

struct Node linkedlist[10];

int main()
{
    // Node *pointer = (Node *)malloc(sizeof(Node));
    // printf("%p\n" , pointer);
    // int *ptr = (int) pointer;
    // printf("%p\n" , pointer);

    //Initialize everything with  -1

    for (int i=0 ; i<MAX_SIZE; i++)
    {
        linkedlist[i].value= -1;
    }

    for (int i=0; i<MAX_SIZE;i++)

    {
        
        if (i ==0)
        {
             linkedlist[i].start = NULL;
             int *ptr = &linkedlist[i];
             linkedlist[i].end = &linkedlist[i+1];

        }
        else if(i==9)
        {
            linkedlist[i].start = &linkedlist[i];
            linkedlist[i].end = NULL;

        }
        else
        {
            linkedlist[i].start = &linkedlist[i];
            linkedlist[i].end = &linkedlist[i+1];

        }   
        
    }


    for (int i=0; i<MAX_SIZE;i++)
    {
        printf("-----%p--------%d------------%p\n" , linkedlist[i].start , linkedlist[i].value , linkedlist[i].end);
    }
}