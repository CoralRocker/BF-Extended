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

void openScratchPad();

void closeScratchPad();

/* Pointer */
vector *bfArray;// = initVector();
uint64_t bfArrSize = 1, bfArrPos = 0;

vector *bfLoop;// = initVector();
uint64_t bfLpPos = 0;

vector *ScratchArr;// = initVector();

int main(int argc, char **argv)
{

	char fname[LINE_MAX];
	if(argc < 2){
		printf("No filename given. Please enter name of file to interpret: ");
		fgets(fname, LINE_MAX, stdin);
		fname[strlen(fname)-1] = 0x00;
	}


	bfArray = initVector();
	pushBackVector(bfArray, 0);

	bfLoop = initVector();
	
	ScratchArr = initVector();

	/* Files */
	vector *fileArray = initVector();
	pushBackVector(fileArray, fopen(((argc>1)?argv[1]:fname), "r"));
	
	FILE *f = backVector(fileArray);

	bool debug = (argc > 2) ? (argv[2][0] == 'd') : false;
	
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
					openScratchPad();
					break;
					}
				case '}':
					{
					closeScratchPad();
					break;
					}
				case '^':
					bfArrPos = 0;
					break;
				case '#':
					printf("%d", atVector(bfArray, bfArrPos));
					break;
				case '@':
					{	
						char* tempBuf;
						size_t* tempLen;
						FILE* tempStream;
						tempStream = open_memstream(&tempBuf, &tempLen);
						while((c = fgetc(f))!= '@' && c != EOF){
							fputc(c, tempStream);
						}
						fclose(tempStream);
						//puts(tempBuf);
						pushBackVector(fileArray, fopen(tempBuf, "r"));
						f = backVector(fileArray);
						openScratchPad();
					break;
					}
				case '!':
					{
						closeScratchPad();
						popBackVector(fileArray);
						f = backVector(fileArray);
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

void openScratchPad(){
	scratchpad *temp = malloc(sizeof(scratchpad));
	int numItems = atVector(bfArray, bfArrPos);
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
	for(int i = 1; i <= numItems; i++)
		pushBackVector(bfArray, atVector(temp->prevArr, temp->prevArrPos+i));
	pushBackVector(ScratchArr, temp);
}

void closeScratchPad(){	
	scratchpad *temp = popBackVector(ScratchArr);
	int numItems = atVector(bfArray, bfArrPos);
	bfArray = temp->prevArr;
	bfLoop = temp->prevLoop;
	for(int i = 0; i < numItems; i++)
		assignVector(bfArray, temp->prevArrPos+i+1, atVector(temp->arrPtr, bfArrPos+i));
	freeVector(temp->arrPtr);
	freeVector(temp->loopPtr);
	bfArrSize = temp->prevArrSize;
	bfArrPos = temp->prevArrPos;
	bfLpPos = temp->prevLoopPos;
	free(temp);
}
