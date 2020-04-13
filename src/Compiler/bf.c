#include <stdio.h>
#include "Vector.h"
void trimMemory(vector* v){int option = curVector(v);if(option==0){int pos = v->size-1;while(pos != 0){int val = atVector(v, pos);if(val == 0)popBackVector(v);else if(val != 0) break; pos--;}}else{int pos = 0; while(pos < v->size){if(atVector(v,pos)==option)eraseVector(v,pos);else pos++;}}if(v->curpos >= v->size)v->curpos=v->size-1; else if(v->size <= 0){pushBackVector(v, 0);v->curpos=0;}}
int main(){
vector *v = initVector();
pushBackVector(v, 0);
addVector(v, 2);shiftRight(v);addVector(v, 3);shiftRight(v);addVector(v, 2);shiftRight(v);incVector(v);shiftRight(v);while(curVector(v)){decVector(v);}shiftLeft(v);shiftLeft(v);shiftLeft(v);shiftLeft(v);while(curVector(v)){printf("%d", curVector(v));shiftRight(v);}addVector(v, 3);trimMemory(v);shiftLeft(v);shiftLeft(v);shiftLeft(v);shiftLeft(v);while(curVector(v)){printf("%d", curVector(v));shiftRight(v);}
freeVector(v);
}
