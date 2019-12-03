#pragma once
#include "Vector.h"
#include <stdint.h>

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
		assignVector(bfArray, temp->prevArrPos+i, atVector(temp->arrPtr, bfArrPos+i+1));
	freeVector(temp->arrPtr);
	freeVector(temp->loopPtr);
	bfArrSize = temp->prevArrSize;
	bfArrPos = temp->prevArrPos;
	bfLpPos = temp->prevLoopPos;
	free(temp);
}
