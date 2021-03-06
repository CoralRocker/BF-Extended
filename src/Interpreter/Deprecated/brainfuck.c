#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <unistd.h>

typedef enum boolean {false, true} bool;

int main(int argc, char **argv)
{
	
	long PTRSIZE = 16384, LOOPSIZE = 4096;
	char str[LINE_MAX];
	char *fname = str;
	bool debug  = false, name = false;

	int opt;
	while((opt = getopt(argc, argv, "dc:f:l:")) != -1){
		switch(opt)
		{
			case 'c':
				PTRSIZE = atoi(optarg);
				break;
			case 'f':
				fname = optarg;
			//	printf("%s :: %d\n", fname, strlen(fname));
				name = true;
				break;
			case 'l':
				LOOPSIZE = atoi(optarg);
				break;
			case 'd':
				debug = true;
				break;
			
				
		}
	}

	if(!name){
		printf("No filename given. Please enter name of file to interpret: ");
		fgets(fname, LINE_MAX, stdin);
		fname[strlen(fname)-1] = 0x00;
	}


	/* Pointer */
	//uint64_t array[PTRSIZE];
	uint64_t *p = malloc(sizeof(uint64_t)*PTRSIZE);
	uint64_t *op;
	uint64_t ptrNum = 0;
	uint64_t *tempPtr = p;
	memset(p, 0x00, PTRSIZE);

	//uint32_t loop[4096] = {0};
	uint32_t *l = malloc(sizeof(uint32_t)*LOOPSIZE);
	uint32_t *tempLoop = l;
	uint32_t *ol;

	/* Files */
	FILE *f = fopen(fname, "r");
	
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
