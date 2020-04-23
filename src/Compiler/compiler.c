#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "VoidVector.h"
#include <unistd.h>

void printToFile(char* str, FILE* outfile){
	fwrite(str, strlen(str), 1, outfile);
}

/* Given a file pointer and a file names,
 * this method gives the absolute path of
 * the root directory.
 */
char* rootDir(FILE* f, char* strname){
        /* Get full file path */
        int file_descriptor = fileno(f);
        char* dirname = malloc(1024);
        char fdpath[1024];
        ssize_t n;
        sprintf(fdpath, "/proc/self/fd/%d", file_descriptor);
        n = readlink(fdpath, dirname, 1024);
        if(n < 0)
                return 0x00;
        dirname[n] = 0x0;
        
        /* Remove original file name from root directory, up to the first '/' */
        int strLen = strlen(strname);
        for(int i = n - 1; i >= n - strLen; i--){
                if(dirname[i] == '/')
                        break;
                dirname[i]=0x0;
        }

        return dirname;
}

/* Get a file pointer for a file relative to another file's location,
 * given a file name.
 */
FILE* relativeFilePointer(FILE* f, char* strname, char* relativePath){
        /* Get Root Directory of file and string lengths */
        char* rootdir = rootDir(f, strname);
        int rlen = strlen(rootdir);
        int alen = strlen(relativePath);

        /* Add file name to absolute path */
        for(int i = rlen; i < rlen+alen; i++)
                rootdir[i] = relativePath[i-rlen];

        rootdir[rlen+alen] = 0x00;
        
        /* Open new file */
        FILE* newFile = fopen(rootdir, "r");
        
        /* Check if file is good */
        if(!newFile)
                perror("ERROR");

        /* Free memory */
        free(rootdir);

        return newFile;
}

int main(int argc, char** argv){
	/* FILES */
	FILE *f = fopen(argv[1], "r");
	FILE *out = fopen("bf.c", "w");
	voidVector* fileVector = initVoidVector();
	pushBackVoidVector(fileVector, f);
	voidVector* fnameVector = initVoidVector();
	pushBackVoidVector(fnameVector, argv[1]);

	/* File Setup */
	//Necessary Includes
	printToFile("#include <stdio.h>\n#include \"Vector.h\"\n#include \"VoidVector.h\"\n", out);
	//Function to trim memory appropriately. Copied from same function in Interpreter/brainfuck.h
	printToFile("void trimMemory(vector* v){int option = curVector(v);if(option==0){int pos = v->size-1;while(pos != 0){int val = atVector(v, pos);if(val == 0)popBackVector(v);else if(val != 0) break; pos--;}}else{int pos = 0; while(pos < v->size){if(atVector(v,pos)==option)eraseVector(v,pos);else pos++;}}if(v->curpos >= v->size)v->curpos=v->size-1; else if(v->size <= 0){pushBackVector(v, 0);v->curpos=0;}}\n", out);
	//Main function and vector declarations
	printToFile("int main(){\n", out);
	printToFile("voidVector* parentVectors = initVoidVector(); pushBackVoidVector(parentVectors, initVector()); vector *tmp, *v = backVoidVector(parentVectors);\npushBackVector(v, 0);\nint args_to_pass;\n", out);

	char c;
	while((c = fgetc(f)) != EOF){
		switch(c){
			case '>':
				printToFile("shiftRight(v);\n", out);
				break;
			case '<':
				printToFile("shiftLeft(v);\n", out);
				break;
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
				printToFile("while(curVector(v)){\n", out);
				break;
			case ']':
				printToFile("}\n", out);
			case '/':
				if(fgetc(f) == '*'){
					while(1){
						if(fgetc(f) == '*')
						{
							if(fgetc(f) == '/'){
								break;	
							}
						}
					}
				}else{
					fseek(f, -1, SEEK_CUR);
				}
				break;
			case '#':
				printToFile("printf(\"%d\", curVector(v));\n", out);
				break;
			case 'd':
				printToFile("printf(\"Current Cell: %d\\nCurrent Size: %d\\nCurrent Value: %d\\n\", v->curpos, v->size, curVector(v));\n", out);
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
				printToFile("pushBackVoidVector(parentVectors, initVector()); pushBackVector(backVoidVector(parentVectors), curVector(v)); v = backVoidVector(parentVectors);\n", out);
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
				pushBackVoidVector(fileVector, relativeFilePointer(f, backVoidVector(fnameVector), fname ));
				pushBackVoidVector(fnameVector, fname);
				f = backVoidVector(fileVector);
				printToFile("pushBackVoidVector(parentVectors, initVector()); tmp = backVoidVector(parentVectors); args_to_pass = curVector(v); if(args_to_pass == 0) pushBackVector(tmp, 0); for(int i=1; i<=args_to_pass; i++){pushBackVector(tmp, atVector(v, v->curpos+i));} v = backVoidVector(parentVectors);\n", out);
				break;
				}
			case '!':
				fclose(popBackVoidVector(fileVector));
				free(popBackVoidVector(fnameVector));
				f = backVoidVector(fileVector);
				printToFile("tmp = popBackVoidVector(parentVectors); v = backVoidVector(parentVectors); args_to_pass = curVector(tmp); for(int i=1; i<=args_to_pass;i++){assignOrPushVector(v, v->curpos+i-1, atVector(tmp, tmp->curpos+i));} freeVector(tmp);\n", out);
				break;
		}
	}

	printToFile("\nfreeVector(v);\n", out);
	printToFile("}\n", out);
	fclose(out);
	fclose(f);
}
