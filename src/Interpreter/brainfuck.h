#pragma once
#include "Vector.h"
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* Vectors and Variables Needed */
vector *bfArray, *bfLoop, *ScratchArr, *inputFileArr;
uint64_t bfArrSize = 1, bfArrPos = 0, bfLpPos = 0;

/* Text Color Constants */
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

/* Boolean Definition */
typedef enum boolean {false, true} bool;

/* Scratchpad save structure.
 * This allows us to save all the memory from the program
 * state to a single structure, which facilitates the opening
 * and closing of scratchpads. 
 */
typedef struct scratchpad {
	vector *arrPtr, *loopPtr;
	vector *prevArr, *prevLoop;
	uint64_t prevArrSize, prevArrPos, prevLoopPos;
} scratchpad;

/* Opens up a classic style scratchpad */
void openScratchPad(){
	/* Save program state to a scratchpad */
	scratchpad *temp = (scratchpad*)malloc(sizeof(scratchpad));
	temp->arrPtr = initVector();
	temp->loopPtr = initVector();
	temp->prevArr = bfArray;
	temp->prevLoop = bfLoop;
	temp->prevArrSize = bfArrSize;
	temp->prevArrPos = bfArrPos;
	temp->prevLoopPos = bfLpPos;
	
	/* Get New Program State */
	bfArray = temp->arrPtr;
	bfLoop = temp->loopPtr;
	bfArrSize = 1;
	bfArrPos = 0;
	bfLpPos = 0;
	pushBackVector(bfArray, atVector(temp->prevArr, temp->prevArrPos));
	
	/* Save scratchpad */
	pushBackVector(ScratchArr, temp);
}

/* Close classic Scratchpad
 * The order in which memory is freed and old program state
 * is replaced is important because of the interaction between
 * the old and new program state.
 */
void closeScratchPad(){	
	/* Load old program state from previously save scratchpad */
	scratchpad *temp = popBackVector(ScratchArr);
	bfArray = temp->prevArr;
	bfLoop = temp->prevLoop;

	/* Assign return variable to the old program state */
	assignVector(bfArray, temp->prevArrPos, atVector(temp->arrPtr, bfArrPos));
	
	/* Free memory */
	freeVector(temp->arrPtr);
	freeVector(temp->loopPtr);

	/* Save Old Program State */
	bfArrSize = temp->prevArrSize;
	bfArrPos = temp->prevArrPos;
	bfLpPos = temp->prevLoopPos;

	/* Free Memory */
	free(temp);
}

/* Open new include file */
void openInclude(){
	/* Save old program state */
	scratchpad *temp = malloc(sizeof(scratchpad));
	temp->arrPtr = initVector();
	temp->loopPtr = initVector();
	temp->prevArr = bfArray;
	temp->prevLoop = bfLoop;
	temp->prevArrSize = bfArrSize;
	temp->prevArrPos = bfArrPos;
	temp->prevLoopPos = bfLpPos;
	
	/* Set new program state */
	int numItems = atVector(bfArray, bfArrPos);
	bfArray = temp->arrPtr;
	bfLoop = temp->loopPtr;
	bfArrPos = 0;
	bfLpPos = 0;
	for(int i = 1; i <= numItems; i++) //Put params into program
		pushBackVector(bfArray, atVector(temp->prevArr, temp->prevArrPos+i));
	if(numItems == 0){ //If no params, put 0 as starting variable
		pushBackVector(bfArray, 0);
	}
	bfArrSize = bfArray->size; //Set arrsize

	/* Saave Scratch array */
	pushBackVector(ScratchArr, temp);
}

/* Close classic Scratchpad
 * The order in which memory is freed and old program state
 * is replaced is important because of the interaction between
 * the old and new program state.
 */
void closeInclude(){	
	/* Load old program state */
	scratchpad *temp = popBackVector(ScratchArr);
	int numItems = atVector(bfArray, bfArrPos);
	bfArray = temp->prevArr;
	bfLoop = temp->prevLoop;
	for(int i = 0; i < numItems; i++) // Load return variables in program
		assignVector(bfArray, temp->prevArrPos+i, atVector(temp->arrPtr, bfArrPos+i));
	
	/* Free Memory */
	freeVector(temp->arrPtr);
	freeVector(temp->loopPtr);

	/* Set more values */
	bfArrSize = temp->prevArrSize;
	bfArrPos = temp->prevArrPos;
	bfLpPos = temp->prevLoopPos;
	
	/* Free Memory */
	free(temp);
}

/* Given a file pointer and a file names,
 * this method gives the absolute path of
 * the root directory.
 */
char* rootDir(FILE* f, char* strname){
	/* Get full file path */
	int file_descriptor = fileno(f);
	char* dirname = malloc(1024);
	char fdpath[1024];
	ssize_t n;
	sprintf(fdpath, "/proc/self/fd/%d", file_descriptor);
	n = readlink(fdpath, dirname, 1024);
	if(n < 0)
		return NULL;
	dirname[n] = 0x0;
	
	/* Remove original file name from root directory, up to the first '/' */
	int strLen = strlen(strname);
	for(int i = n - 1; i >= n - strLen; i--){
		if(dirname[i] == '/')
			break;
		dirname[i]=0x0;
	}

	return dirname;
}

/* Get a file pointer for a file relative to another file's location,
 * given a file name.
 */
FILE* relativeFilePointer(FILE* f, char* strname, char* relativePath){
	/* Get Root Directory of file and string lengths */
	char* rootdir = rootDir(f, strname);
	int rlen = strlen(rootdir);
	int alen = strlen(relativePath);

	/* Add file name to absolute path */
	for(int i = rlen; i < rlen+alen; i++)
		rootdir[i] = relativePath[i-rlen];

	rootdir[rlen+alen] = 0x00;
	
	/* Open new file */
	FILE* newFile = fopen(rootdir, "r");
	
	/* Check if file is good */
	if(!newFile)
		perror("ERROR");

	/* Free memory */
	free(rootdir);

	return newFile;
}
/* Remove specifc cells and free their memory.
 * If this method is used improperly, it is
 * possible to remove all the cells in memory,
 * which would be an issue.
 */
void trimMemory(){
	int option = atVector(bfArray, bfArrPos);//Get what cells to remove
	if(option == 0){ // If cells to remove is 0, remove all cells after the last populated one
		int pos = bfArrSize - 1;
		while(pos != 0){
			int val = atVector(bfArray, pos);
			if(val == 0)
				popBackVector(bfArray);
			else if(val != 0)
				break;
			pos--;
		}
		bfArrSize = bfArray->size;
	}else{ // Otherwise, remove all cells holding the given value.
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
	if(bfArrPos >= bfArrSize)
		bfArrPos = bfArrSize - 1;
	else if(bfArrSize <= 0){
		pushBackVector(bfArray, 0);
		bfArrSize = bfArray->size;
		bfArrPos = 0;
	}

}
