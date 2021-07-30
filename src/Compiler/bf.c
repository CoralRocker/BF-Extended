#include <stdio.h>
#include "Vector.h"
#include "VoidVector.h"
void trimMemory(vector* v){int option = curVector(v);if(option==0){int pos = v->size-1;while(pos != 0){int val = atVector(v, pos);if(val == 0)popBackVector(v);else if(val != 0) break; pos--;}}else{int pos = 0; while(pos < v->size){if(atVector(v,pos)==option)eraseVector(v,pos);else pos++;}}if(v->curpos >= v->size)v->curpos=v->size-1; else if(v->size <= 0){pushBackVector(v, 0);v->curpos=0;}}
int main(){
voidVector* parentVectors = initVoidVector(); pushBackVoidVector(parentVectors, initVector()); vector *tmp, *v = backVoidVector(parentVectors);
pushBackVector(v, 0);
int args_to_pass;
addVector(v, 2);shiftByVector(v, 1);
addVector(v, 8);shiftByVector(v, 1);
addVector(v, 8);v->curpos=0;
pushBackVoidVector(parentVectors, initVector()); tmp = backVoidVector(parentVectors); args_to_pass = curVector(v); if(args_to_pass == 0) pushBackVector(tmp, 0); for(int i=1; i<=args_to_pass; i++){pushBackVector(tmp, atVector(v, v->curpos+i));} v = backVoidVector(parentVectors);
shiftByVector(v, 2);
setVector(v, 0);
shiftByVector(v, -2);
assignOrPushVector(v, v->curpos + 2, curVector(v));
setVector(v, 0);
incVector(v);
shiftByVector(v, 1);
while(curVector(v)){
shiftByVector(v, 2);
setVector(v, 0);
shiftByVector(v, 1);
setVector(v, 0);
v->curpos=0;
while(curVector(v)){
v->curpos=v->size-1;
incVector(v);
v->curpos=0;
decVector(v);
}
v->curpos=v->size-1;
while(curVector(v)){
shiftByVector(v, -2);
while(curVector(v)){
shiftByVector(v, -2);
incVector(v);
shiftByVector(v, 3);
incVector(v);
shiftByVector(v, -1);
decVector(v);
}
shiftByVector(v, 1);
while(curVector(v)){
shiftByVector(v, -1);
incVector(v);
shiftByVector(v, 1);
decVector(v);
}
shiftByVector(v, 1);
decVector(v);
}
v->curpos=0;
shiftByVector(v, 1);
decVector(v);
}
v->curpos=0;
assignOrPushVector(v, v->curpos + 1, curVector(v));
setVector(v, 0);
incVector(v);
tmp = popBackVoidVector(parentVectors); v = backVoidVector(parentVectors); args_to_pass = curVector(tmp); for(int i=1; i<=args_to_pass;i++){assignOrPushVector(v, v->curpos+i-1, atVector(tmp, tmp->curpos+i));} freeVector(tmp);
printf("%d", curVector(v));
shiftByVector(v, 1);
setVector(v, 0);
shiftByVector(v, 1);
setVector(v, 0);
shiftByVector(v, -2);
assignOrPushVector(v, v->curpos + 1, curVector(v));
setVector(v, 0);
addVector(v, 10);putchar(curVector(v));
setVector(v, 0);
shiftByVector(v, 2);
addVector(v, 4);shiftByVector(v, -2);
addVector(v, 2);pushBackVoidVector(parentVectors, initVector()); tmp = backVoidVector(parentVectors); args_to_pass = curVector(v); if(args_to_pass == 0) pushBackVector(tmp, 0); for(int i=1; i<=args_to_pass; i++){pushBackVector(tmp, atVector(v, v->curpos+i));} v = backVoidVector(parentVectors);
shiftByVector(v, 1);
assignOrPushVector(v, v->curpos + 1, curVector(v));
setVector(v, 0);
shiftByVector(v, -1);
while(curVector(v)){
decVector(v);
shiftByVector(v, 1);
incVector(v);
shiftByVector(v, 1);
decVector(v);
while(curVector(v)){
shiftByVector(v, 1);
incVector(v);
shiftByVector(v, 2);
}
shiftByVector(v, 1);
while(curVector(v)){
incVector(v);
while(curVector(v)){
decVector(v);
shiftByVector(v, -1);
incVector(v);
shiftByVector(v, 1);
}
shiftByVector(v, 1);
incVector(v);
shiftByVector(v, 2);
}
shiftByVector(v, -6);
}
v->curpos=v->size-1;
shiftByVector(v, -3);
setVector(v, 0);
incVector(v);
tmp = popBackVoidVector(parentVectors); v = backVoidVector(parentVectors); args_to_pass = curVector(tmp); for(int i=1; i<=args_to_pass;i++){assignOrPushVector(v, v->curpos+i-1, atVector(tmp, tmp->curpos+i));} freeVector(tmp);
printf("%d", curVector(v));
addVector(v, 10);putchar(curVector(v));
setVector(v, 0);

freeVector(v);
}
