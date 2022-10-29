#include <stdio.h>
#include <stdlib.h>
#include <string.h>


enum TYPE {P , H};
struct Node
{
    size_t size;
    //size of the memory allocated
    void * arena;
    //arena is the pointer to the brginning 
    enum TYPE type;
    //States wether it is a process or a hole

    int next;
    //points to the next bit in the array

    int previous;
    //points to the previous one in the array


};

int main()
{
    
}