#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

void readFromfile(char fptr[]);
void readFromCMD(int argc, char **argv);
int valid_output(int ascii);

const char *values[] = { "NUL", "SOH", "STX", "ETX", "EOT", "ENQ", "ACK", "BEL",
						"BS", "HT", "LF", "VT", "FF", "CR", "SO", "SI", "DLE",
						"DC1", "DC2", "DC3", "DC4", "NAK", "SYN", "ETB", "CAN",
						"EM", "SUB", "ESC", "FS", "GS", "RS", "US", "SPACE" };

int main(int argc, char** argv)
{
	
	char c;

  	if(argc > 2) // reading from cmd
	{
   		printf("Reading from commandline! \n");
		readFromCMD(argc, argv);
	}
   	else if(argc == 2 && argv[1][0] != '-') // reading from file
   	{
		printf("Reading from file!\n");
		
		int filedesc = open(argv[1], O_RDONLY);
		if(filedesc)
			printf("\nfile desc = %d\n", filedesc);
		else
			printf("something wrong");
		
		int pos = 0;
		char line[9];
			printf("\nOriginal ASCII    Decimal  Parity\n");
			printf("-------- -------- -------- -------- \n");
			while(read(filedesc, &c, 1) != 0 )
			{
				if(c == '\n'){

					line[pos] = '\0';
					//printf("%s\n", line);
					readFromfile(line);
					pos = 0;
				}
				else{
					line[pos] = c;
					//printf("%c", c);
					pos++;
				}
			}

	
		

	}
	else 
		printf("Wrong input");
			   
   
	return 0;

}

void readFromfile(char* fptr)
{ 
	char str2[8];
	char binary[100];
	

		strcpy(binary, fptr);		

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
		
			//for (int i = 0; i < 8; i++)
			//	printf("%c", binary[i]);

			if((ascii >= 0 && ascii <= 32) || ascii == 127)
				printf("%s\t%s\t%i\t",binary, values[decimal], decimal);
			else
				printf("%s\t%c\t%i\t",binary, ascii, decimal);

			if(sum % 2 == 0)
				printf("EVEN\n");
			else 
				printf("ODD\n");
		     


}

void readFromCMD(int argc, char **argv)
{
	char binary[9];
    char str2[8];
		printf("\nOriginal ASCII    Decimal  Parity\n");
		printf("-------- -------- -------- -------- \n");
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

			if((ascii >= 0 && ascii <= 32) || ascii == 127)
				printf("%s\t%s\t%i\t", binary, values[decimal], decimal);
			else
				printf("%s\t%c\t%i\t", binary, ascii, decimal);
			if(sum % 2 == 0)
				printf("EVEN\n");
			else 
				printf("ODD\n");
	
                    
    }

}
