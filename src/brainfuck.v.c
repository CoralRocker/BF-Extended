#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include "Vector.h"

typedef enum boolean {false, true} bool;

int main(int argc, char **argv)
{

	char fname[LINE_MAX];
	if(argc < 2){
		printf("No filename given. Please enter name of file to interpret: ");
		fgets(fname, LINE_MAX, stdin);
		fname[strlen(fname)-1] = 0x00;
	}


	/* Pointer */
	vector *bfArray = initVector();
	pushBackVector(bfArray, 0);
	uint64_t bfArrSize = 1, bfArrPos = 0;
	vector *tempBFArray;
	uint64_t tBFArrSize, tBFArrPos;

	vector *bfLoop = initVector();
	uint64_t bfLpPos = 0;
	vector *tempBFLoop;
	uint64_t tBFLPos;

	/* Files */
	FILE *f = fopen(((argc>1)?argv[1]:fname), "r");
	
	bool debug = false;
	if(argc >= 3)
		if(argv[2][0] == 'd')
		{
			printf("Debugging program.\nPrints will be with integers\n-----------------\n");
			debug = true;
		}

	/* Compile Loop */
	char c;
	bool comment = false;
	while((c = fgetc(f)) != EOF)
	{
		switch(c)
		{
			case '/':
			{
				uint32_t temp = ftell(f);
				c = fgetc(f);
				if(c == '*')
					comment = true;
				else
					fseek(f, temp, SEEK_SET);
				break;
			}
			case '*':
			{
				uint32_t temp = ftell(f);
				c = fgetc(f);
				if(c == '/')
					comment = false;
				else
					fseek(f, temp, SEEK_SET);
				break;
			}
		}
		if(!comment){
			switch(c)
			{
				case '>':
					if(bfArrPos + 1 < bfArrSize)
					{
						bfArrPos++;
					}else{
						pushBackVector(bfArray, 0);
						bfArrSize++;
						bfArrPos++;
					}
					break;

				case '<':
					if(bfArrPos != 0)
					{
						bfArrPos--;
					}
					break;

				case '+':
					assignVector(bfArray, bfArrPos, atVector(bfArray, bfArrPos) + 1);
					break;

				case '-':
					if(atVector(bfArray, bfArrPos) <= 0)
						assignVector(bfArray, bfArrPos, 0);
					else
						assignVector(bfArray, bfArrPos, atVector(bfArray, bfArrPos) - 1);
					break;

				case '.':
					if(!debug)
						printf("%c", atVector(bfArray, bfArrPos));
					else
						printf("%d\n", atVector(bfArray, bfArrPos));
					break;

				case ',':
					assignVector(bfArray, bfArrPos, getchar());
					break;

				case '[':
					pushBackVector(bfLoop, ftell(f));
					bfLpPos++;
					break;

				case ']':
					if(atVector(bfLoop, bfArrPos) == 0)
					{	
						popBackVector(bfLoop);
					}else{
						fseek(f, backVector(bfLoop), SEEK_SET);
					}
					break;

				case '{':
					tempBFArray = bfArray;
					bfArray = initVector();
					tBFArrPos = bfArrPos;
					tBFArrSize = bfArrSize;
					bfArrPos=0;
					bfArrSize=1;
					pushBackVector(bfArray, atVector(tempBFArray, tBFArrPos));
					
					tempBFLoop = bfLoop;
					bfLoop = initVector();
					tBFLPos = bfLpPos;
					bfLpPos = 0;
					break;

				case '}':
					assignVector(tempBFArray, tBFArrPos, atVector(bfArray, bfArrPos));
					freeVector(bfArray);
					bfArray = tempBFArray;
					bfArrPos = tBFArrPos;
					bfArrSize = tBFArrSize;
					
					free(bfLoop);
					bfLoop = tempBFLoop;
					bfLpPos = tBFLPos;
					break;
			}
		}
	}
	printf("\n");
	/* Close Files */
	fclose(f);
}	
