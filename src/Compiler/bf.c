#include <stdio.h>
#include "Vector.h"
#include "VoidVector.h"
void trimMemory(vector* v){int option = curVector(v);if(option==0){int pos = v->size-1;while(pos != 0){int val = atVector(v, pos);if(val == 0)popBackVector(v);else if(val != 0) break; pos--;}}else{int pos = 0; while(pos < v->size){if(atVector(v,pos)==option)eraseVector(v,pos);else pos++;}}if(v->curpos >= v->size)v->curpos=v->size-1; else if(v->size <= 0){pushBackVector(v, 0);v->curpos=0;}}
int main(){
voidVector* parentVectors = initVoidVector(); pushBackVoidVector(parentVectors, initVector()); vector *tmp, *v = backVoidVector(parentVectors);
pushBackVector(v, 0);
int args_to_pass;
addVector(v, 3);addVector(v, 3);shiftRight(v);
addVector(v, 3);addVector(v, 3);pushBackVoidVector(parentVectors, initVector()); pushBackVector(backVoidVector(parentVectors), curVector(v)); v = backVoidVector(parentVectors);
addVector(v, 2);shiftRight(v);
incVector(v);
shiftLeft(v);
tmp = popBackVoidVector(parentVectors); v = backVoidVector(parentVectors); setVector(v, curVector(tmp)); freeVector(tmp);
shiftRight(v);
shiftRight(v);
while(curVector(v)){
decVector(v);
}
shiftLeft(v);
shiftLeft(v);
shiftLeft(v);
while(curVector(v)){
shiftRight(v);
shiftRight(v);
shiftRight(v);
incVector(v);
shiftLeft(v);
shiftLeft(v);
shiftLeft(v);
decVector(v);
}
shiftRight(v);
shiftRight(v);
shiftRight(v);
while(curVector(v)){
shiftLeft(v);
shiftLeft(v);
while(curVector(v)){
shiftLeft(v);
incVector(v);
shiftRight(v);
shiftRight(v);
incVector(v);
shiftLeft(v);
decVector(v);
}
shiftRight(v);
while(curVector(v)){
shiftLeft(v);
incVector(v);
shiftRight(v);
decVector(v);
}
shiftRight(v);
decVector(v);
}
shiftLeft(v);
while(curVector(v)){
decVector(v);
}
shiftLeft(v);
while(curVector(v)){
decVector(v);
}
shiftLeft(v);
putchar(curVector(v));
while(curVector(v)){
decVector(v);
}
addVector(v, 6);while(curVector(v)){
shiftRight(v);
addVector(v, 8);shiftLeft(v);
decVector(v);
}
shiftRight(v);
while(curVector(v)){
shiftLeft(v);
incVector(v);
shiftRight(v);
shiftRight(v);
incVector(v);
shiftLeft(v);
decVector(v);
}
shiftRight(v);
while(curVector(v)){
shiftLeft(v);
incVector(v);
shiftRight(v);
decVector(v);
}
shiftLeft(v);
incVector(v);
v->curpos=0;
putchar(curVector(v));
while(curVector(v)){
decVector(v);
}
shiftRight(v);
while(curVector(v)){
decVector(v);
}
shiftLeft(v);
while(curVector(v)){
decVector(v);
}
pushBackVoidVector(parentVectors, initVector()); tmp = backVoidVector(parentVectors); args_to_pass = curVector(v); if(args_to_pass == 0) pushBackVector(tmp, 0); for(int i=1; i<=args_to_pass; i++){pushBackVector(tmp, atVector(v, v->curpos+i));} v = backVoidVector(parentVectors);
addVector(v, 48);putchar(curVector(v));
while(curVector(v)){
decVector(v);
shiftRight(v);
incVector(v);
shiftLeft(v);
}
shiftRight(v);
putchar(curVector(v));
while(curVector(v)){
decVector(v);
}
addVector(v, 10);putchar(curVector(v));
while(curVector(v)){
decVector(v);
}
shiftLeft(v);
while(curVector(v)){
decVector(v);
}
addVector(v, 8);while(curVector(v)){
decVector(v);
shiftRight(v);
addVector(v, 6);shiftLeft(v);
}
shiftRight(v);
while(curVector(v)){
decVector(v);
shiftLeft(v);
incVector(v);
shiftRight(v);
}
shiftLeft(v);
shiftLeft(v);
shiftLeft(v);
shiftLeft(v);
shiftLeft(v);
putchar(curVector(v));
while(curVector(v)){
decVector(v);
}
addVector(v, 10);putchar(curVector(v));
while(curVector(v)){
decVector(v);
}
shiftLeft(v);
while(curVector(v)){
decVector(v);
}
shiftRight(v);
while(curVector(v)){
decVector(v);
}
addVector(v, 4);while(curVector(v)){
decVector(v);
shiftLeft(v);
decVector(v);
shiftRight(v);
}
shiftRight(v);
addVector(v, 8);while(curVector(v)){
decVector(v);
shiftLeft(v);
addVector(v, 6);shiftRight(v);
}
shiftLeft(v);
putchar(curVector(v));
while(curVector(v)){
decVector(v);
}
addVector(v, 10);putchar(curVector(v));
tmp = popBackVoidVector(parentVectors); v = backVoidVector(parentVectors); args_to_pass = curVector(tmp); for(int i=1; i<=args_to_pass;i++){assignOrPushVector(v, v->curpos+i, atVector(tmp, tmp->curpos+i));} freeVector(tmp);

freeVector(v);
}
