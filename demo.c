#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

void calculations(char fptr[]);

const char *VALUES[] = { "NUL", "SOH", "STX", "ETX", "EOT", "ENQ", "ACK", "BEL",
						"BS", "HT", "LF", "VT", "FF", "CR", "SO", "SI", "DLE",
						"DC1", "DC2", "DC3", "DC4", "NAK", "SYN", "ETB", "CAN",
						"EM", "SUB", "ESC", "FS", "GS", "RS", "US", "SPACE" };
const char*DEL = "DEL";

int main(int argc, char** argv)
{

	char c;
	int pos = 0;
	char line[9];
	int start_pos = 1;
	char binary[9];

  	if(argc >= 2 && (open(argv[1], O_RDONLY)) == -1) // reading from stdin
	{
		printf("\ncmd\n");
		if(argv[1][0] == '-')
			start_pos = 2;
		printf("\nOriginal ASCII    Decimal  Parity\n");
		printf(  "-------- -------- -------- -------- \n");
		for(int i = start_pos ; i < argc; i++)
		{
			strcpy(binary, argv[i]);
			calculations( binary);
			
		}

	}
   	else if(argc == 2 && argv[1][0] != '-' && (open(argv[1], O_RDONLY) != -1)) // reading from file
   	{
		
		int filedesc = open(argv[1], O_RDONLY);
		

		printf("\nOriginal   ASCII    Decimal  Parity\n");
		printf("-------- -------- -------- -------- \n");

		while(read(filedesc, &c, 1) != 0 )	// iterating through the file 
		{
			if(c == '\n' || c == ' ')		// if newline or space detected 
			{

				line[pos] = '\0'; 			// end the binary(ascii) number 
				calculations( line);		// pass the line for further calculations
				pos = 0;
			}
			else  							// continue adding chars to the binary(ascii)
			{
				line[pos] = c;
				pos++;
			}

		}

	}
	else 
		printf("Wrong input");
			   
	return 0;

}

void calculations(char* fptr)
{ 
	char str2[8];
	char binary[9];

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
		
	if((ascii >= 0 && ascii <= 32))
		printf("%s\t%s\t%i\t",binary, VALUES[decimal], decimal);
	else if(ascii == 127)
		printf("%s\t%s\t%i\t",binary, DEL, decimal);
	else
		printf("%s\t%c\t%i\t",binary, ascii, decimal);

	if(sum % 2 == 0)
		printf("EVEN\n");
	else 
		printf("ODD\n");
		     
}