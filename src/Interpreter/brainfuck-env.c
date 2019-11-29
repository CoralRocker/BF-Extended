#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <stdint.h>
#include "Vector.h"
#include "brainfuck.h"

const float BFE_ENV_VERSION = 1.0;

static void catch_sigint(int signo){
//	printf("\n%s%s CAUGHT EITHER SIGTERM OR SIGINT --BRAINFUCK-ENV %3f =>%s ", KRED, BYLW, BFE_ENV_VERSION, KNRM);	
}


int main(int argc, char **argv)
{
	signal(SIGINT, catch_sigint);
	signal(SIGTERM, catch_sigint);
	/* Pointer */
	bfArray = initVector();
	pushBackVector(bfArray, 0);
	bfLoop = initVector();
	ScratchArr = initVector();

	/* Files */
	FILE *f = fopen(".BFE-ENV", "w+");
	vector* fileArray = initVector();
	pushBackVector(fileArray, f);

	bool debug = false;
	
	/* Compile Loop */
	char c;
	char *line = NULL;
	size_t len = 0;
	off_t pos;
	bool breakout = false;
	char* nLine;

	printf("%s%sBRAINFUCK-ENV %.2f =>%s ", KRED, BYLW, BFE_ENV_VERSION, KNRM);
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
							size_t tempLen;
							FILE* tempStream;
							tempStream = open_memstream(&tempBuf, &tempLen);
							while((c = fgetc(f))!= '@' && c != EOF){
								fputc(c, tempStream);
							}
							fclose(tempStream);
							//puts(tempBuf);
							pushBackVector(fileArray, fopen(tempBuf, "r"));
							f = backVector(fileArray);
							if(f==NULL)
								puts("!!! FILE NAME INVALID !!!");
							openInclude();
							//openScratchPad();
							free(tempBuf);
						break;
						}
					case '!':
						{
							closeInclude();
							fclose(popBackVector(fileArray));
							f = backVector(fileArray);
						break;
						}
				}
			}
		}
		free(line);
		len = 0;
		if(breakout)
			break;
		printf("%s%s%sBRAINFUCK-ENV %.2f =>%s ", nLine, KRED, BYLW, BFE_ENV_VERSION, KNRM);
	}
	freeVector(bfArray);
	freeVector(bfLoop);
	freeVector(ScratchArr);
	freeVector(fileArray);
	printf("\n");
	/* Close Files */
	fclose(f);
	remove(".BFE-ENV");
}	
