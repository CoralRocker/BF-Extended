#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include "Vector.h"

typedef enum boolean {false, true} bool;

typedef struct scratchpad {
	vector *arrPtr, *loopPtr;
	vector *prevArr, *prevLoop;
	uint64_t prevArrSize, prevArrPos, prevLoopPos;
} scratchpad;

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

	vector *bfLoop = initVector();
	uint64_t bfLpPos = 0;

	vector *ScratchArr = initVector();

	/* Files */
	FILE *f = fopen(((argc>1)?argv[1]:fname), "r");
	
	bool debug = false;
	
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
						printf("%c", (int) atVector(bfArray, bfArrPos));
					else
						printf("%d\n", (int) atVector(bfArray, bfArrPos));
					break;

				case ',':
					assignVector(bfArray, bfArrPos, (void*) getchar());
					break;

				case '[':
					pushBackVector(bfLoop, (void*) ftell(f));
					bfLpPos++;
					break;

				case ']':
					if(atVector(bfArray, bfArrPos) == 0)
					{	
						popBackVector(bfLoop);
					}else{
						fseek(f, (long int) backVector(bfLoop), SEEK_SET);
					}
					break;

				case '{':
					{
					scratchpad *temp = malloc(sizeof(scratchpad));
					temp->arrPtr = initVector();
					temp->loopPtr = initVector();
					temp->prevArr = bfArray;
					temp->prevLoop = bfLoop;
					temp->prevArrSize = bfArrSize;
					temp->prevArrPos = bfArrPos;
					temp->prevLoopPos = bfLpPos;
					
					bfArray = temp->arrPtr;
					bfLoop = temp->loopPtr;
					bfArrSize = 1;
					bfArrPos = 0;
					bfLpPos = 0;
					pushBackVector(bfArray, atVector(temp->prevArr, temp->prevArrPos));
					pushBackVector(ScratchArr, temp);
					break;
					}
				case '}':
					{
					scratchpad *temp = popBackVector(ScratchArr);
					bfArray = temp->prevArr;
					bfLoop = temp->prevLoop;
					assignVector(bfArray, temp->prevArrPos, atVector(temp->arrPtr, bfArrPos));
					freeVector(temp->arrPtr);
					freeVector(temp->loopPtr);
					bfArrSize = temp->prevArrSize;
					bfArrPos = temp->prevArrPos;
					bfLpPos = temp->prevLoopPos;
					free(temp);
					break;
					}
			}
		}
	}

	freeVector(bfArray);
	freeVector(bfLoop);
	freeVector(ScratchArr);
	printf("\n");
	/* Close Files */
	fclose(f);
}	
