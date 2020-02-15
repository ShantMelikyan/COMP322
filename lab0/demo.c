#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include <ctype.h>

void calculations(char* val);

const char *VALUES[] = { "NUL", "SOH", "STX", "ETX", "EOT", "ENQ", "ACK", "BEL",
						"BS", "HT", "LF", "VT", "FF", "CR", "SO", "SI", "DLE",
						"DC1", "DC2", "DC3", "DC4", "NAK", "SYN", "ETB", "CAN",
						"EM", "SUB", "ESC", "FS", "GS", "RS", "US", "SPACE" };
const char*DEL = "DEL";

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		printf("No Input!");	
		return 0;
	}
	char c; // one bit will be stored
	int pos = 0; // start reading from file at 
	char line[9];
	int start_pos = 1; // start reading from stdin at 

	
  	//if(argc >= 2 && (open(argv[1], O_RDONLY)) == -1){ // reading from stdin
		
	if(argv[1][0] == '-' || argv[1][0] == '0' || argv[1][0] == '1'){

		if(argc == 2 && argv[1][0] == '-'){  // check if there is any input
			printf("Wrong input!\n");
			return 0;
		}
		if(argv[1][0] == '-')
			start_pos = 2;
		
		for(int i = start_pos; i < argc; i++){ // stdin input check 
		 	for(unsigned int j =0; j < strlen(argv[i]); j++){
		 		if(argv[i][j] != '0' && argv[i][j] != '1'){
		 			printf("Wrong input!\n");
		 			return 0;
		 		}
		 	}
		 }
		printf("\nOriginal ASCII    Decimal  Parity\n");
		printf(  "-------- -------- -------- -------- \n");


		for(int i = start_pos ; i < argc; i++){
			calculations(argv[i]);
		}

	}
	//else if(argc == 2 && argv[1][0] != '-' && (open(argv[1], O_RDONLY) != -1)){ // reading from file
	else if(argc == 2 && isascii(argv[1][0]) && (argv[1][0] >= 97 && argv[1][0] <= 122)) {

		if(open(argv[1], O_RDONLY) == -1)
			printf("cant open file!");

		int filedesc = open(argv[1], O_RDONLY);
		
		while(read(filedesc, &c, 1) != 0 ){	// iterating through the file 
			
			if (c != '0' && c != '1' && c != ' '){ // check for correct data in the file
				printf("Your file had a wrong data!\n");
				return 0;
			}
		}

		printf("\nOriginal   ASCII    Decimal  Parity\n");
		printf("-------- -------- -------- -------- \n");

		filedesc = open(argv[1], O_RDONLY); // reset the file descriptor

		while(read(filedesc, &c, 1) != 0 ){	// iterating through the file 
			
			if(c == ' ' ){		// if newline or space detected 
			
				line[pos] = '\0'; 			// end the binary(ascii) number 
				calculations(line);		// pass the line for further calculations
				pos = 0;
			}
			else{							// continue adding chars to the binary(ascii)
			
				line[pos] = c;
				pos++;
			}

		}
		
			line[pos] = '\0'; 			// end the binary(ascii) number 
			calculations(line);		// pass the line for further calculations
		
	}
	else 
		printf("Wrong input");
			   
	return 0;

}

void calculations(char* val)
{ 

	char binary[9];
	int decimal = 0;
	strcpy(binary, val);		

   	int sum = 0;
   	int size = strlen(binary);

	if(size < 9){      // adding 0 at the end if there is less than 8 bits
	
		for(int j = size; j < 9; j++){
         	binary[j] = '0';
        }

        binary[8] = '\0';
   	}

	for(int i = 0; i < 8; i++){ // calculating the sum
	
		sum +=(int)binary[i];
	}

	for(int i = 1; i < 8; i++)           // calculating decimal 
		decimal += (binary[i]-'0') << (7-i);

	char ascii = (char)decimal;          // converting decimal to ascii value 
  		
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