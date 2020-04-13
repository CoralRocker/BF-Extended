#include <stdio.h>
#include "Vector.h"
void trimMemory(vector* v){int option = curVector(v);if(option==0){int pos = v->size-1;while(pos != 0){int val = atVector(v, pos);if(val == 0)popBackVector(v);else if(val != 0) break; pos--;}}else{int pos = 0; while(pos < v->size){if(atVector(v,pos)==option)eraseVector(v,pos);else pos++;}}if(v->curpos >= v->size)v->curpos=v->size-1; else if(v->size <= 0){pushBackVector(v, 0);v->curpos=0;}}
int main(){
vector *v = initVector();
pushBackVector(v, 0);
addVector(v, 2);shiftRight(v);addVector(v, 4);addVector(v, 4);addVector(v, 4);addVector(v, 4);shiftRight(v);while(curVector(v)){decVector(v);}v->curpos=0;while(curVector(v)){shiftRight(v);shiftRight(v);incVector(v);shiftLeft(v);shiftLeft(v);decVector(v);}incVector(v);shiftRight(v);while(curVector(v)){shiftLeft(v);while(curVector(v)){shiftRight(v);shiftRight(v);shiftRight(v);shiftRight(v);incVector(v);shiftLeft(v);shiftLeft(v);shiftLeft(v);shiftLeft(v);decVector(v);}shiftRight(v);shiftRight(v);shiftRight(v);shiftRight(v);while(curVector(v)){shiftLeft(v);shiftLeft(v);while(curVector(v)){shiftLeft(v);shiftLeft(v);incVector(v);shiftRight(v);shiftRight(v);shiftRight(v);incVector(v);shiftLeft(v);decVector(v);}shiftRight(v);while(curVector(v)){shiftLeft(v);incVector(v);shiftRight(v);decVector(v);}shiftRight(v);decVector(v);}shiftLeft(v);shiftLeft(v);shiftLeft(v);decVector(v);}shiftLeft(v);printf("%d", curVector(v));
freeVector(v);
}
