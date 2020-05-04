//In this lab, you will develop a single program that calculates the 
//page number and the offset within the page for a given virtual memory address.  

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) 
{
    if(argc != 2){
        printf("\tNeed one argument.\n\tTry ./paging [address]\n");
        return 0;
    }
    
    const int PAGE_SIZE = 4096;
    unsigned int address, page_num, offset;
    
    /* calculations */
    address = atoi(argv[1]);
    page_num = address / PAGE_SIZE;
    offset = address % PAGE_SIZE;
    
    /* output calculations */
    printf("\tThe address %s contains:\n", argv[1]); 
    printf("\tpage number = %d\n", page_num);
    printf("\toffset = %d\n", offset);
    
    return 0;
}