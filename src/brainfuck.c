#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

typedef enum boolean {false, true} bool;

int main(int argc, char **argv)
{

	char fname[LINE_MAX];
	if(argc < 2){
		printf("No filename given. Please enter name of file to interpret: ");
		fgets(fname, LINE_MAX, stdin);
		fname[strlen(fname)-1] = 0x00;
	}


	/* Pointer */
	const long PTRSIZE = 16384;
	//uint64_t array[PTRSIZE];
	uint64_t *p = malloc(sizeof(uint64_t)*PTRSIZE);
	uint64_t *op;
	uint64_t ptrNum = 0;
	uint64_t *tempPtr = p;
	memset(p, 0x00, PTRSIZE);

	//uint32_t loop[4096] = {0};
	uint32_t *l = malloc(sizeof(uint32_t)*4096);
	uint32_t *tempLoop = l;
	uint32_t *ol;

	/* Files */
	FILE *f = fopen(((argc>1)?argv[1]:fname), "r");
	
	bool debug = false;
	if(argc >= 3)
		if(argv[2][0] == 'd')
		{
			printf("Debugging program.\nPrints will be with integers\n-----------------\n");
			debug = true;
		}

	/* Compile Loop */
	char c;
	bool comment = false;
	while((c = fgetc(f)) != EOF)
	{
		switch(c)
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
		if(!comment){
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
					p = malloc(sizeof(uint64_t)*PTRSIZE);
					op = p;
					*p = *tempPtr;
					tempLoop = l;
					l = malloc(sizeof(uint32_t)*4096);
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
	}
	printf("\n");
	/* Close Files */
	fclose(f);
	free(l);
	free(p);
}	
