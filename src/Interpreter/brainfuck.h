#pragma once
#include "Vector.h"
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


vector *bfArray, *bfLoop, *ScratchArr;
uint64_t bfArrSize = 1, bfArrPos = 0, bfLpPos = 0;

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

void openScratchPad(){
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
}

void closeScratchPad(){	
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
}

void openInclude(){
	scratchpad *temp = malloc(sizeof(scratchpad));
	temp->arrPtr = initVector();
	temp->loopPtr = initVector();
	int numItems = atVector(bfArray, bfArrPos);
	temp->prevArr = bfArray;
	temp->prevLoop = bfLoop;
	temp->prevArrSize = bfArrSize;
	temp->prevArrPos = bfArrPos;
	temp->prevLoopPos = bfLpPos;
	
	bfArray = temp->arrPtr;
	bfLoop = temp->loopPtr;
	bfArrPos = 0;
	bfLpPos = 0;
	for(int i = 1; i <= numItems; i++)
		pushBackVector(bfArray, atVector(temp->prevArr, temp->prevArrPos+i));
	if(numItems == 0){
		pushBackVector(bfArray, 0);
	}
	bfArrSize = bfArray->size;
	pushBackVector(ScratchArr, temp);
}

void closeInclude(){	
	scratchpad *temp = popBackVector(ScratchArr);
	int numItems = atVector(bfArray, bfArrPos);
	bfArray = temp->prevArr;
	bfLoop = temp->prevLoop;
	for(int i = 0; i < numItems; i++)
		assignVector(bfArray, temp->prevArrPos+i, atVector(temp->arrPtr, bfArrPos+i));
	freeVector(temp->arrPtr);
	freeVector(temp->loopPtr);
	bfArrSize = temp->prevArrSize;
	bfArrPos = temp->prevArrPos;
	bfLpPos = temp->prevLoopPos;
	free(temp);
}
char* rootDir(FILE* f, char* strname){
	int file_descriptor = fileno(f);
	char* dirname = malloc(1024);
	char fdpath[1024];
	ssize_t n;
	sprintf(fdpath, "/proc/self/fd/%d", file_descriptor);
	n = readlink(fdpath, dirname, 1024);
	if(n < 0)
		return NULL;
	dirname[n] = 0x0;
	
	int strLen = strlen(strname);
	for(int i = n - 1; i >= n - strLen; i--){
		if(dirname[i] == '/')
			break;
		dirname[i]=0x0;
	}
//	printf("N: %d, STRLEN: %d\n", n, strlen(dirname));

	return dirname;
}

FILE* relativeFilePointer(FILE* f, char* strname, char* relativePath){
	char* rootdir = rootDir(f, strname);
	int rlen = strlen(rootdir);
	int alen = strlen(relativePath);
	//printf("RootDir: %s\n", rootdir);
	for(int i = rlen; i < rlen+alen; i++)
		rootdir[i] = relativePath[i-rlen];

	rootdir[rlen+alen] = 0x00;
	//printf("New dir: %s\n", rootdir);

	FILE* newFile = fopen(rootdir, "r");
	
	if(!newFile)
		perror("ERROR");
	free(rootdir);

	return newFile;
}
void trimMemory(){
	int option = atVector(bfArray, bfArrPos);
	if(option == 0){
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

}
