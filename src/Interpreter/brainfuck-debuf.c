#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include "Vector.h"
#include "brainfuck.h"

int main(int argc, char **argv)
{

	/*Find file name to open*/
	char fname[LINE_MAX];
	if(argc < 2){
		printf("No filename given. Please enter name of file to interpret: ");
		fgets(fname, LINE_MAX, stdin);
		fname[strlen(fname)-1] = 0x00;
	}

	/* Initialize vectors and arrays */
	bfArray = initVector();		//Main BF cell array
	pushBackVector(bfArray, 0);	//Initialize first cell to 0
	bfLoop = initVector();		//Loop array
	ScratchArr = initVector();	//Scratch Memory Array

	/* File and FileName Arrays */
	vector *fileArray = initVector();
	pushBackVector(fileArray, fopen(((argc>1)?argv[1]:fname), "r"));
	vector *fileNameArray = initVector();
	pushBackVector(fileNameArray, ((argc>1)?argv[1]:fname));
	FILE *rf = backVector(fileArray);
	inputFileArr = initVector();
	vector *tempFileArray = initVector();
	FILE *f = tmpfile();
	pushBackVector(tempFileArray, f);

	char c; // Character
	bool comment = false; //Check if code is commented out or not
	char* buf;
	size_t buflen;
	int line = 0, character = 0;
	while(getline(&buf, &buflen, rf)!=-1)
	{
		line++;
		int curPlace = ftell(f);
		fputs(buf, f);
		fseek(f, curPlace, SEEK_SET);
		/* Compile Loop */	
		while((c = fgetc(f)) != EOF)
		{
			switch(c) // Check for Comments...
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
			if(!comment){ //Interpret code if not commented out
				switch(c)
				{
					case '>': //Move cell forward
						if(bfArrPos + 1 < bfArrSize)
						{
							bfArrPos++;
						}else{
							pushBackVector(bfArray, 0);
							bfArrSize++;
							bfArrPos++;
						}
						break;
	
					case '<': //Move cell backward
						if(bfArrPos != 0)
						{
							bfArrPos--;
						}
						break;
	
					case '+': //Increment cell
						assignVector(bfArray, bfArrPos, atVector(bfArray, bfArrPos) + 1);
						break;
	
					case '-': //Decrement cell
						if(atVector(bfArray, bfArrPos) <= 0)
							assignVector(bfArray, bfArrPos, 0);
						else
							assignVector(bfArray, bfArrPos, atVector(bfArray, bfArrPos) - 1);
						break;
	
					case '.': //Print cell
						printf("%c", (int) atVector(bfArray, bfArrPos));
						break;
	
					case ',': //Get input from keyboard
						assignVector(bfArray, bfArrPos, (void*) fgetc((inputFileArr->size == 0)?stdin : backVector(inputFileArr)));
						break;
	
					case '[': //Start loop
						if(atVector(bfArray, bfArrPos)!=0){
							pushBackVector(bfLoop, (void*) ftell(f));
							bfLpPos++;
						}else{
							while((c = fgetc(f))!=']'){
								character++;

							};
						}
						break;
	
					case ']': //End loop
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
					case '#':
						printf("%d", atVector(bfArray, bfArrPos));
						break;
					case '@': //Open include file
						{	
							/* Get File Name */
							char* tempBuf;
							size_t tempLen;
							FILE* tempStream;
							tempStream = open_memstream(&tempBuf, &tempLen);
							while((c = fgetc(rf))!= '@' && c != EOF){
								fputc(c, tempStream);
							}
							fclose(tempStream);
							
							/* Get relative file pointer of new file and save it */
							pushBackVector(fileArray, relativeFilePointer(f, backVector(fileNameArray), tempBuf));
							rf = backVector(fileArray);
							pushBackVector(fileNameArray, tempBuf);
							pushBackVector(tempFileArray, tmpfile());
							f = backVector(tempFileArray);
							/* Check for error */
							if(rf==NULL)
								printf("ERROR: %s: Invalid File Name\n");
							/* Open Include System */
							openInclude();
							/* Free Memory */
							free(tempBuf); 
						break;
						}
					case '!': //Close include file
						{
							/* Close includes and files */
							closeInclude();
							fclose(popBackVector(fileArray));
							fclose(popBackVector(tempFileArray));
							popBackVector(fileNameArray);
							rf = backVector(fileArray);
							f = backVector(tempFileArray);
						break;
						}
					case '~': //Go-To-End operator
						bfArrPos = bfArrSize - 1;
						break;
					case '|': //Trim Memory
						{
							trimMemory();
						break;
						}
					case '^': //Return-to-zero operator
						bfArrPos = 0;
						break;
					case '%': //Open separate file
						{
							int numChars = atVector(bfArray, bfArrPos);
							if(numChars != 0){
								char* filename = malloc(numChars+1);
								for(int i = 0; i < numChars; i++){
									filename[i] = atVector(bfArray, bfArrPos+1+i);
								}
								filename[numChars]=0x00;
								puts(filename);
								FILE* newFile = fopen(filename, "r");
								if(!newFile){								
									freeVector(bfArray);
									freeVector(bfLoop);
									freeVector(ScratchArr);
									freeVector(fileArray);
									freeVector(inputFileArr);
									freeVector(tempFileArray);
									printf("ERROR: %s is an invalid filename. Exiting program\n", filename);
									free(filename);
									return 0;
								}
								pushBackVector(inputFileArr, newFile);
								free(filename);
							}else{
								popBackVector(inputFileArr);
							}
						break;
						}
					case 'd': // Debug Information
						printf("\nCurrent Cell: %X\nCurrent Size: %X\nCurrent Value: %X\n", bfArrPos, bfArrSize, atVector(bfArray,bfArrPos));
						break;
				}
			}
	
		}
		free(buf);
		buflen = 0;
		character = 0;
	}

	/* Free Vectors and Arrays */
	freeVector(bfArray);
	freeVector(bfLoop);
	freeVector(ScratchArr);
	freeVector(fileArray);
	freeVector(inputFileArr);
	freeVector(tempFileArray);

	printf("\n");
	
	/* Close Files */
	fclose(f);
}
