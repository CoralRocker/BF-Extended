#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum boolean {false, true} bool;

int main(int argc, char **argv)
{
	/* Pointer */
	const long PTRSIZE = 16384;
	unsigned long array[PTRSIZE];
	unsigned long *p = array;
	unsigned long *op;
	unsigned long ptrNum = 0;
	unsigned long *tempPtr = p;
	memset(p, 0x00, PTRSIZE);

	int loop[4096] = {0};
	int *l = loop;
	int *tempLoop = l;
	int *ol;

	/* Files */
	FILE *f = fopen(argv[1], "r");
	
	bool debug = false;
	if(argc >= 3)
		if(argv[2][0] == 'd')
		{
			printf("Debugging program.\nPrints will be with integers\n-----------------\n");
			debug = true;
		}

	/* Compile Loop */
	char c;
	while((c = fgetc(f)) != EOF)
	{

		switch(c)
		{
			case '>':
				if(ptrNum + 1 < PTRSIZE)
				{
					++p;
					++ptrNum;
				}
				break;
			case '<':
				if(ptrNum != 0)
				{
					--p;
					--ptrNum;
				}
				break;
			case '+':
				++*p;
				break;
			case '-':
				if(*p <= 0)
					*p = 0;
				else
					--*p;
				break;
			case '.':
				if(!debug)
					printf("%c", *p);
				else
					printf("%d\n", *p);
				break;
			case ',':
				*p = getchar();
				break;
			case '[':
				++l;
				*l = ftell(f);
				
				break;
			case ']':
				if(*p == 0)
				{	
					*l = 0;
					--l;
				}else{
					fseek(f, *l, SEEK_SET);
				}
				break;
			case '{':
				tempPtr = p;
				p = malloc(sizeof(long)*PTRSIZE);
				op = p;
				*p = *tempPtr;
				tempLoop = l;
				l = malloc(sizeof(int)*4096);
				ol = l;
				break;
			case '}':
				*tempPtr = *p;
				free(op);
				p = tempPtr;
				free(ol);
				l = tempLoop;
				break;
		}
	}
	printf("\n");
	/* Close Files */
	fclose(f);
}	
