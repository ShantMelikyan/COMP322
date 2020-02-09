#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

void readFromfile(FILE *fptr);
void readFromCMD(int argc, char **argv);

int main(int argc, char** argv)
{
	int result = 0;
	int fp_to_read = 0;
	printf("you have entered: %d values\n", argc); 
	printf("Values entered: ");

	for (int i = 0; i < argc; ++i) 
        printf("%s " , argv[i]); 
    
//===================== determine if reading from cmd or file ============================
    result = strcmp(argv[1], "-");
	printf("Original ASCII    Decimal  Parity\n");
	printf("-------- -------- -------- -------- \n");
  		if(argc > 2) // reading from cmd
		  {
   			printf("Reading from commandline! \n");
			readFromCMD(argc, argv);
		  }
   		else if(argc == 2) // reading from file
   		{
			printf("Reading from file!\n");
			FILE *fptr;
   				if ((fptr = fopen("zero_and_one.txt","r")) == NULL)
				   {
   						printf("Error! opening file");
						exit(1);
   					}
			
			readFromfile(fptr);
		}
		else
			printf("cant open file");
			   
   
return 0;

}

void readFromfile(FILE *fptr)
{ 
	char str2[8];
	char binary[100];
	while (fgets(binary, sizeof(binary), fptr) != NULL) 
	{
   	
   		int num = 0;
   		int sum = 0;
   		char* ptr;
   		int size = strlen(binary);
		if(size < 9)
		{
			for(int j = size; j < 9; j++)
            {
            	binary[j] = '0';
            }
            binary[8] = '\0';
   		}
        for(int i = 0; i < 8; i++)
   		{	
   			str2[i] = binary[i+1];
   			sum +=(int)binary[i];
   		}
      	char ascii = strtol(str2, &ptr, 2);
      	int	decimal = (int)ascii;
		
		for (int i = 0; i < 8; i++)
			printf("%c", binary[i]);

		printf("\t%c\t%d\t", ascii, decimal );
			if(sum % 2 == 0)
				printf("EVEN\n");
			else 
				printf("ODD\n");

   }
   fclose(fptr); 
}
void readFromCMD(int argc, char **argv)
{
	char binary[9];
    char str2[8];

    for(int i = 2; i < argc; i++)
    {
		int sum = 0;
		char *ptr;

        strcpy(binary, argv[i]);
        int size = strlen(argv[i]);

        if(size < 9)
        {
            for(int j = size; j < 9; j++)
            {
            	binary[j] = '0';
            }
            binary[8] = '\0';
        }
        for(int j = 0; j < 8; j++)
        {
            str2[j] = binary[j + 1];
            sum += (int)binary[j];
		}
                        
        
        char ascii = strtol(str2, &ptr, 2);
        int decimal = (int)ascii; 

		printf("%s\t%c\t%i\t", binary, ascii, decimal);
		if(sum % 2 == 0)
			printf("EVEN\n");
		else 
			printf("ODD\n");
                    
    }
}