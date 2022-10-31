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

int count = 0;
struct Node linkedlist[MAX_SIZE];

void allocate(int size)
{
    //allocate that much memory from my malloc function.
    int  *ptr = (int *) malloc(10*sizeof(struct Node));
    //that pointer will be stored in the first arraylist alongside lenght. 
    //i need to have the starting and ending position for the values.
    linkedlist[0].value = -1;
    
    linkedlist[0].start = ptr;
    linkedlist[0].end = ptr+40;
    

}

void insert(int num)
{
    //insert num into the array
    //which position of the array do i insert it to.
    //do i get specified which node it must go to.

    //Add int to the next empty space in the file
    //see until you find empty space.
    int i=0;

    if (linkedlist[0].value == -1)
    {
        linkedlist[i].value = num;
        linkedlist[i].end =  linkedlist[0].start + 4;
        linkedlist[i+1].start = linkedlist[i].end;
        return;

    }
    
    while(i<MAX_SIZE)
    {
        //this value in the linkedl ist must be empty.
        if( linkedlist[i+1].value== -1 )
        {
            linkedlist[i+1].value = num;
            printf("Added %d in position %d of the linked node\n" , num , i);
            linkedlist[i+1].start = linkedlist[i].end;
            linkedlist[i+2].start = linkedlist[i+1].start+4;
            break;
        }
        i=i+1;
        
       
        

    }

    


}

int main()
{

    //store the pointer of the node in a static array. 

    

   

    //initialize everything with NULL
    for (int i=0 ; i<MAX_SIZE ; i++)
    {
        
        linkedlist[i].value=-1;
        
    }

    allocate(4096);

    //pointer set up

    

    insert(3);
    insert(4);
    insert(5);







}