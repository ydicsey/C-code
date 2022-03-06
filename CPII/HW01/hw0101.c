#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void Hex2Bin(char* input, char* inputBinary, int32_t size)
{
	// input = malloc(sizeof(char)*size);
	inputBinary = malloc(sizeof(char)*size*4);

	int32_t index = 0;
    printf("\ncheck point01\n");
	while (input[index])
	{
		switch (input[index++]) {
        case '0':
            printf("\n0000\n");
            strncat(inputBinary, "0000", 5);
            break;
        case '1':
			strncat(inputBinary, "0001", 5);
            break;
        case '2':
			strncat(inputBinary, "0010", 5);
            break;
        case '3':
			strncat(inputBinary, "0011", 5);
            break;
        case '4':
            printf("\n0100\n");
            strncat(inputBinary, "0100", 5);
            break;
        case '5':
            strncat(inputBinary, "0101", 4);
            break;
        case '6':
            strncat(inputBinary, "0110", 4);
            break;
        case '7':
            strncat(inputBinary, "0111", 4);
            break;
        case '8':
            strncat(inputBinary, "1000", 4);
            break;
        case '9':
            strncat(inputBinary, "1001", 4);
            break;
        case 'A':
        case 'a':
            strncat(inputBinary, "1010", 4);
            break;
        case 'B':
        case 'b':
            strncat(inputBinary, "1011", 4);
            break;
        case 'C':
        case 'c':
            strncat(inputBinary, "1100", 4);
            break;
        case 'D':
        case 'd':
            strncat(inputBinary, "1101", 4);
            break;
        case 'E':
        case 'e':
            strncat(inputBinary, "1110", 4);
            break;
        case 'F':
        case 'f':
            strncat(inputBinary, "1111", 4);
            break;
		}
	}
}

int main(){
	uint8_t input[130];
    // uint8_t inputBinary[600] = {0};
	// char *input, *inputBinary;
    char *inputBinary;
	int16_t length = 0, i;

	// do
	// {
	// 	printf("Please enter the hex string: ");
	// 	fflush(stdin);
	// 	fgets(input, 130, stdin);
		
    //     length = strlen(input);
	// 	if(length > 129)
	// 	{
	// 		printf("\nThe number of words exceeds the limit(128)\n");
	// 		continue;
	// 	}
	// }while(1);
	
	printf("Please enter the hex string: ");
	fflush(stdin);
	fgets(input, 130, stdin);
	length = strlen(input) - 1;
	Hex2Bin(input, inputBinary, length);
    printf("%d", length);
	// puts(inputBinary);
	return 0;
}