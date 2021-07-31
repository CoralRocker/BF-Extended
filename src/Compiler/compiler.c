#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "VoidVector.h"
#include <unistd.h>
#include "PreProcess.h"

void printToFile(char* str, FILE* outfile){
	fwrite(str, strlen(str), 1, outfile);
}

struct relativeFILE{
	FILE* fptr;
	char* fname;
	char* absDirectory;
} relativeFILE;

/* Given a file pointer and a file names,
 * this method gives the absolute path of
 * the root directory.
 */
char* rootDir(struct relativeFILE* rf){
        /* Get full file path */
        int file_descriptor = fileno(rf->fptr);
        char* dirname = malloc(1024);
        char fdpath[1024];
        ssize_t n;
        sprintf(fdpath, "/proc/self/fd/%d", file_descriptor);
        n = readlink(fdpath, dirname, 1024);
        if(n < 0)
                return 0x00;
        dirname[n] = 0x0;
       
	printf("Full file path: %s\n", dirname);

        /* Remove original file name from root directory, up to the first '/' */
        int strLen = strlen(rf->fname);
        for(int i = n - 1; i >= n - strLen; i--){
                if(dirname[i] == '/')
                        break;
                dirname[i]=0x0;
        }

        return dirname;
}

struct relativeFILE* initRF(FILE* f, char* fname){
	struct relativeFILE *rf = malloc(sizeof(struct relativeFILE));
	rf->fptr = f;
	rf->fname = fname;
	rf->absDirectory = rootDir(rf);
	return rf;
}
void freeRF(struct relativeFILE* rf){
	fclose(rf->fptr);
	free(rf->absDirectory);
	free(rf);
}

/* Get a file pointer for a file relative to another file's location,
 * given a file name.
 */
FILE* relativeFilePointer(struct relativeFILE* rf, char* relativePath){
	/* Get Root Directory of file and string lengths */
	char* rootdir = malloc(512);
	printf("\tOld AbsDir: %s\n\tAbsDir Len: %d\n", rf->absDirectory, strlen(rf->absDirectory));
	strncpy(rootdir, rf->absDirectory, strlen(rf->absDirectory)+1);
	int rlen = strlen(rootdir);
	int alen = strlen(relativePath);

	printf("\tNew AbsDir: %s\n", rootdir);
	/* Add file name to absolute path */
	for(int i = rlen; i < rlen+alen; i++)
		rootdir[i] = relativePath[i-rlen];

	rootdir[rlen+alen] = 0x00;

	/* Open new file */
	FILE* newFile = fopen(rootdir, "r");
	printf("\tOpening %s\n\n", rootdir);	
	/* Check if file is good */
	if(!newFile)
		perror("OOPSIES");

	/* Free memory */
	free(rootdir);

	return newFile;
}


int main(int argc, char** argv){
	/* FILES */
	FILE *f = fopen(argv[1], "r");
	//FILE *f = fremoveSpace(fopen(argv[1], "r"), fopen("test.dat", "w+"));
	FILE *out = fopen("bf.c", "w");
	
	voidVector* rfVector = initVoidVector();
	pushBackVoidVector(rfVector, initRF(f, argv[1]));
	puts(((struct relativeFILE*)backVoidVector(rfVector))->absDirectory);
	
	//f = fremoveSpace(f, fopen("test.dat", "w+"));
	f = fremoveSpace(f, tmpfile());
	((struct relativeFILE*)backVoidVector(rfVector))->fptr = f;

	/* File Setup */
	//Necessary Includes
	printToFile("#include <stdio.h>\n#include \"Vector.h\"\n#include \"VoidVector.h\"\n", out);
	//Function to trim memory appropriately. Copied from same function in Interpreter/brainfuck.h
	printToFile("void trimMemory(vector* v){int option = curVector(v);if(option==0){int pos = v->size-1;while(pos != 0){int val = atVector(v, pos);if(val == 0)popBackVector(v);else if(val != 0) break; pos--;}}else{int pos = 0; while(pos < v->size){if(atVector(v,pos)==option)eraseVector(v,pos);else pos++;}}if(v->curpos >= v->size)v->curpos=v->size-1; else if(v->size <= 0){pushBackVector(v, 0);v->curpos=0;}}\n", out);
	//Main function and vector declarations
	printToFile("int main(){\n", out);
	printToFile("voidVector* parentVectors = initVoidVector(); pushBackVoidVector(parentVectors, initVector()); vector *tmp, *v = backVoidVector(parentVectors);\npushBackVector(v, 0);\nint args_to_pass;\n", out);

	char c;
	int tmp;
	while((c = fgetc(f)) != EOF){
		switch(c){
			case '>':
				{;
				tmp = 1;
				while(fgetc(f) == '>')
					tmp++;
				fseek(f, -1, SEEK_CUR);
				char str[256];
				sprintf(&str, "shiftByVector(v, %d);\n", tmp);
				printToFile(str, out);
				break;
				}
			case '<':
				{;
				int tmp = -1;
				while(fgetc(f) == '<')
					tmp--;
				fseek(f, -1, SEEK_CUR);
				char str[256];
				sprintf(&str, "shiftByVector(v, %d);\n", tmp);

				printToFile(str, out);

				break;
				}
			case '+':
				
				if(fgetc(f) == '+'){
					int count = 2;
					while(fgetc(f) == '+'){
						count++;
					}
					fseek(f, -1, SEEK_CUR);
					char res[16], o[64] = "addVector(v, ";
					sprintf(res, "%d", count);
					strncat(o, res, 64);
					strncat(o, ");", 64);
					printToFile(o, out);
				}else{
					fseek(f, -1, SEEK_CUR);
					printToFile("incVector(v);\n", out);
				
				}
				break;
			case '-':
				if(fgetc(f) == '-'){
					int count = 2;
					while(fgetc(f) == '-'){
						count++;
					}
					fseek(f, -1, SEEK_CUR);
					char res[16], o[64] = "subVector(v, ";
					sprintf(res, "%d", count);
					strncat(o, res, 64);
					strncat(o, ");", 64);
					printToFile(o, out);
				}else{
					fseek(f, -1, SEEK_CUR);
					printToFile("decVector(v);\n", out);
				}
				break;
			case ',':
				printToFile("v->arr[v->curpos] = getchar();\n", out);
				break;
			case '.':
				printToFile("putchar(curVector(v));\n", out);
				break;
			case '[': 
				{;
				long tmp = ftell(f);
				if(fgetc(f) == '>'){
					int RshiftCount = 1;
					while(fgetc(f) == '>')
						RshiftCount++;
					fseek(f, -1, SEEK_CUR);
					printf("RSHIFT: %d\n", RshiftCount);
					if(fgetc(f) == '+' && fgetc(f) == '<'){
						int LshiftCount = 1;
						while(fgetc(f) == '<')
							LshiftCount++;
						fseek(f, -1, SEEK_CUR);
						printf("LSHIFT: %d\n", LshiftCount);
						if(LshiftCount != RshiftCount)
							fseek(f, tmp, SEEK_SET);
						else if(fgetc(f) == '-' && fgetc(f) == ']'){
							puts("Found copy");
							char tmp[256];
							sprintf(&tmp, "assignOrPushVector(v, v->curpos + %d, curVector(v));\nsetVector(v, 0);\n", RshiftCount);
							printToFile(tmp, out);
							break;
						}
					}
				}
				fseek(f, tmp, SEEK_SET);
				if(fgetc(f) == '-' && fgetc(f) == ']'){
					printToFile("setVector(v, 0);\n", out);
				}else{
					printToFile("while(curVector(v)){\n", out);
					fseek(f, tmp, SEEK_SET);
				}
				break;
				}
			case ']':
				printToFile("}\n", out);
			case '/':
				c = fgetc(f);
				if(c == '*'){
					while(1){
						if(fgetc(f) == '*')
						{
							if(fgetc(f) == '/'){
								break;	
							}
						}
					}
				}else if(c == '/'){
					while(1){
						c = fgetc(f);
						if(c == '\n' || c == EOF)
							break;
					}
				}else{
					fseek(f, -1, SEEK_CUR);
				}
				break;
			case '#':
				printToFile("printf(\"%d\", curVector(v));\n", out);
				break;
			case 'd':
				printToFile("printf(\"Current Cell: %d\\nCurrent Size: %d\\nCurrent Value: %d\\nCurrent Value (Hex): %X\\n\", v->curpos, v->size, curVector(v), curVector(v));\n", out);
				break;
			case '^':
				printToFile("v->curpos=0;\n", out);
				break;
			case '~':
				printToFile("v->curpos=v->size-1;\n", out);
				break;
			case '|':
				printToFile("trimMemory(v);\n", out); //Call function declared earlier. More efficient 
				break;
			case '{':
				printToFile("pushBackVoidVector(parentVectors, initVector());", out);
				printToFile("pushBackVector(backVoidVector(parentVectors),curVector(v));", out);
				printToFile("v = backVoidVector(parentVectors);\n", out);
				break;
			case '}':
				printToFile("tmp = popBackVoidVector(parentVectors); v = backVoidVector(parentVectors); setVector(v, curVector(tmp)); freeVector(tmp);\n", out);
				break;
			case '@':{
				char *fname = malloc(sizeof(char)*256);
				int counter = 0;
				while((c = fgetc(f))!='@'){
					fname[counter]=c; // strncat wasn't working for some damn reason. 
					counter++;
				}
				printf("Including file %s\n", fname);
				printf("\tOld file: %s\n\tNew File: %s\n", ((struct relativeFILE*)backVoidVector(rfVector))->fname, fname);
				printf("\tOld AbsDir: %s\n", ((struct relativeFILE*)backVoidVector(rfVector))->absDirectory);
				
				pushBackVoidVector(rfVector, initRF(relativeFilePointer(backVoidVector(rfVector), fname), fname));
				
				puts(((struct relativeFILE*)backVoidVector(rfVector))->absDirectory);
				f = ((struct relativeFILE*)backVoidVector(rfVector))->fptr;
				f = fremoveSpace(f, tmpfile());
				((struct relativeFILE*)backVoidVector(rfVector))->fptr = f;
				printToFile("pushBackVoidVector(parentVectors, initVector()); tmp = backVoidVector(parentVectors); args_to_pass = curVector(v); if(args_to_pass == 0) pushBackVector(tmp, 0); for(int i=1; i<=args_to_pass; i++){pushBackVector(tmp, atVector(v, v->curpos+i));} v = backVoidVector(parentVectors);\n", out);
				break;
				}
			case '!':
				free(((struct relativeFILE*)backVoidVector(rfVector))->fname);
				freeRF(((struct relativeFILE*)popBackVoidVector(rfVector)));	
				f = ((struct relativeFILE*)backVoidVector(rfVector))->fptr;
				puts(((struct relativeFILE*)backVoidVector(rfVector))->absDirectory);
				printToFile("tmp = popBackVoidVector(parentVectors); v = backVoidVector(parentVectors); args_to_pass = curVector(tmp); for(int i=1; i<=args_to_pass;i++){assignOrPushVector(v, v->curpos+i-1, atVector(tmp, tmp->curpos+i));} freeVector(tmp);\n", out);
				break;
		}
	}

	printToFile("\nfreeVector(v);\n", out);
	printToFile("}\n", out);
	freeRF(backVoidVector(rfVector));
	freeVoidVector(rfVector);
	fclose(out);
}
