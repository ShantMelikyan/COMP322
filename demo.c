#include<stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv){
	int result = 0;
	char binary[100];
	char str2[8];

	printf("you have entered: %d values\n", argc); 
	
	printf("Values entered: ");

	for (int i = 0; i < argc; ++i) 
        printf("%s " , argv[i]); 
    
//===================== determine if reading from cmd or file ============================
    result = strcmp(argv[1], "-");
  		if (result == 0)
   			printf("Reading from commandline! \n");
   		else
   			printf("Reading from file!\n");
	
	
//====================== open file =====================================
   FILE *fptr;
   if ((fptr = fopen("zero_and_one.txt","r")) == NULL){
       printf("Error! opening file");
       // Program exits if the file pointer returns NULL
       exit(1);
   }
//====================== read from file =================================

   while (fgets(binary, sizeof(binary), fptr) != NULL) 
   {
   	
   		int num = 0;
   		int sum = 0;
   		char* ptr;
   		int decimal = 0;
        fprintf(stderr, "got line: %s", binary);
        for(int i = 0; i < 8; i++)
   		{	
   			str2[i] = binary[i+1];
   			sum +=(int)binary[i];
   		}
      	char ascii = strtol(str2, &ptr, 2);
      	decimal = (int)ascii;
        //for(int i = 0; i < 8; i++)
			//num += (binary[i] - '0') << (7-i);
		
		printf("Original ASCII    Decimal  Parity\n");
		printf("%s      %c       %d  \n", binary, ascii, decimal);


   }
        
   fclose(fptr); 



	return 0;

}
