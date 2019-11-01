#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include "Vector.h"

const float BFE_ENV_VERSION = 1.0;

const char* KRED = "\033[31m";
const char* KBLK = "\033[30m";
const char* KGRN = "\033[32m";
const char* KYLW = "\033[33m";
const char* KBLU = "\033[34m";
const char* KMGA = "\033[35m";
const char* KCYN = "\033[36m";
const char* KWHT = "\033[37m";

const char* BRED = "\033[41m";
const char* BBLK = "\033[40m";
const char* BGRN = "\033[42m";
const char* BYLW = "\033[43m";
const char* BBLU = "\033[44m";
const char* BMGA = "\033[45m";
const char* BCYN = "\033[46m";
const char* BWHT = "\033[47m";

const char* KNRM = "\033[0m";

typedef enum boolean {false, true} bool;

typedef struct scratchpad {
	vector *arrPtr, *loopPtr;
	vector *prevArr, *prevLoop;
	uint64_t prevArrSize, prevArrPos, prevLoopPos;
} scratchpad;

int main(int argc, char **argv)
{
	/* Pointer */
	vector *bfArray = initVector();
	pushBackVector(bfArray, 0);
	uint64_t bfArrSize = 1, bfArrPos = 0;

	vector *bfLoop = initVector();
	uint64_t bfLpPos = 0;

	vector *ScratchArr = initVector();

	/* Files */
	FILE *f = fopen(".BFE-ENV", "w+");
	
	bool debug = false;
	
	/* Compile Loop */
	char c;
	char *line = NULL;
	size_t len = 0;
	off_t pos;
	bool breakout = false;
	char* nLine;

	printf("%s%sBRAINFUCK-ENV %3f =>%s ", KRED, BYLW, BFE_ENV_VERSION, KNRM);
	while(getline(&line, &len, stdin) != -1)
	{
		nLine = "";
		pos = ftell(f);
		fputs(line, f);
		fseek(f, pos, SEEK_SET);
		while((c = fgetc(f)) != EOF)
		{
			switch(c)
			{
				case 'q':
				case 'Q':
					breakout = true;
					break;
			}
			if(!breakout){
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
						nLine = "\n";
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
		free(line);
		len = 0;
		if(breakout)
			break;
		printf("%s%s%sBRAINFUCK-ENV %3f =>%s ", nLine, KRED, BYLW, BFE_ENV_VERSION, KNRM);
	}
	freeVector(bfArray);
	freeVector(bfLoop);
	freeVector(ScratchArr);
	printf("\n");
	/* Close Files */
	fclose(f);
	remove(".BFE-ENV");
}	
