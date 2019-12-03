#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include "Vector.h"
#include "brainfuck.h"

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
				case '~':
					bfArrPos = bfArrSize - 1;
					break;
				case '|':
					int option = atVector(bfArray, bfArrPos);
					if(option == 0){
						int lastPos;
						for(int i = 0; i < bfArrSize; i++)
							if(atVector(bfArray, bfArrPos) != 0)
								lastPos = i;
						for(int i = 0; i < (bfArrSize - lastPos - 1); i++)
							popBackVector(bfArray);
					}else{
						int pos = 0;
						while(pos < bfArrSize){
							if(atVector(bfArray, pos)==option)
								eraseVector(bfArray, pos);
							else
								pos++;
							bfArrSize = bfArray->size;
						}
					}
					bfArrSize = bfArray->size;
					break;

			}
		}
	}

	freeVector(bfArray);
	freeVector(bfLoop);
	freeVector(ScratchArr);
	freeVector(fileArray);
	printf("\n");
	/* Close Files */
	fclose(f);
}
