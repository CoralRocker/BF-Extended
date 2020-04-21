#include <stdio.h>
#include "Vector.h"
#include "VoidVector.h"
void trimMemory(vector* v){int option = curVector(v);if(option==0){int pos = v->size-1;while(pos != 0){int val = atVector(v, pos);if(val == 0)popBackVector(v);else if(val != 0) break; pos--;}}else{int pos = 0; while(pos < v->size){if(atVector(v,pos)==option)eraseVector(v,pos);else pos++;}}if(v->curpos >= v->size)v->curpos=v->size-1; else if(v->size <= 0){pushBackVector(v, 0);v->curpos=0;}}
int main(){
voidVector* parentVectors = initVoidVector(); pushBackVoidVector(parentVectors, initVector()); vector *tmp, *v = backVoidVector(parentVectors);
pushBackVector(v, 0);
int args_to_pass;
while(curVector(v)){
decVector(v);
}
pushBackVoidVector(parentVectors, initVector()); tmp = backVoidVector(parentVectors); args_to_pass = curVector(v); if(args_to_pass == 0) pushBackVector(tmp, 0); for(int i=1; i<=args_to_pass; i++){pushBackVector(tmp, atVector(v, v->curpos+i));} v = backVoidVector(parentVectors);
addVector(v, 3);addVector(v, 3);printf("%d", curVector(v));
while(curVector(v)){
shiftRight(v);
addVector(v, 4);addVector(v, 4);shiftLeft(v);
decVector(v);
}
shiftRight(v);
putchar(curVector(v));
while(curVector(v)){
shiftLeft(v);
incVector(v);
shiftRight(v);
decVector(v);
}
shiftLeft(v);
putchar(curVector(v));
while(curVector(v)){
decVector(v);
}
incVector(v);
shiftRight(v);
addVector(v, 4);addVector(v, 4);shiftLeft(v);
tmp = popBackVoidVector(parentVectors); v = backVoidVector(parentVectors); args_to_pass = curVector(tmp); for(int i=1; i<=args_to_pass;i++){assignOrPushVector(v, v->curpos+i, atVector(tmp, tmp->curpos+i));} freeVector(tmp);
while(curVector(v)){
shiftRight(v);
addVector(v, 3);addVector(v, 3);shiftLeft(v);
decVector(v);
}
putchar(curVector(v));

freeVector(v);
}
