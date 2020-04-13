#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printToFile(char* str, FILE* outfile){
	fwrite(str, strlen(str), 1, outfile);
}

int main(int argc, char** argv){
	/* FILES */
	FILE *f = fopen(argv[1], "r");
	FILE *out = fopen("bf.c", "w");

	/* File Setup */
	//Necessary Includes
	printToFile("#include <stdio.h>\n#include \"Vector.h\"\n#include \"VoidVector.h\"\n", out);
	//Function to trim memory appropriately. Copied from same function in Interpreter/brainfuck.h
	printToFile("void trimMemory(vector* v){int option = curVector(v);if(option==0){int pos = v->size-1;while(pos != 0){int val = atVector(v, pos);if(val == 0)popBackVector(v);else if(val != 0) break; pos--;}}else{int pos = 0; while(pos < v->size){if(atVector(v,pos)==option)eraseVector(v,pos);else pos++;}}if(v->curpos >= v->size)v->curpos=v->size-1; else if(v->size <= 0){pushBackVector(v, 0);v->curpos=0;}}\n", out);
	//Main function and vector declarations
	printToFile("int main(){\n", out);
	printToFile("voidVector* parentVectors = initVoidVector(); pushBackVoidVector(parentVectors, initVector()); vector *v = backVoidVector(parentVectors);\npushBackVector(v, 0);\n", out);

	char c;
	while((c = fgetc(f)) != EOF){
		switch(c){
			case '>':
				printToFile("shiftRight(v);", out);
				break;
			case '<':
				printToFile("shiftLeft(v);", out);
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
					printToFile("incVector(v);", out);
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
					printToFile("decVector(v);", out);
				}
				break;
			case ',':
				printToFile("v->arr[v->curpos] = getchar();", out);
				break;
			case '.':
				printToFile("putchar(curVector(v));", out);
				break;
			case '[':
				printToFile("while(curVector(v)){", out);
				break;
			case ']':
				printToFile("}", out);
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
				printToFile("printf(\"%d\", curVector(v));", out);
				break;
			case 'd':
				printToFile("printf(\"Current Cell: %d\\nCurrent Size: %d\\nCurrent Value: %d\\n\", v->curpos, v->size, curVector(v));", out);
				break;
			case '^':
				printToFile("v->curpos=0;", out);
				break;
			case '~':
				printToFile("v->curpos=v->size-1;", out);
				break;
			case '|':
				printToFile("trimMemory(v);", out); //Call function declared earlier. More efficient 
				break;
			case '{':
				printToFile("pushBackVoidVector(parentVectors, initVector()); pushBackVector(backVoidVector(parentVectors), curVector(v)); v = backVoidVector(parentVectors);", out);
				break;
			case '}':
				printToFile("vector* tmp = popBackVoidVector(parentVectors); v = backVoidVector(parentVectors); setVector(v, curVector(tmp)); freeVector(tmp);", out);
		}
	}

	printToFile("\nfreeVector(v);\n", out);
	printToFile("}\n", out);
	fclose(out);
	fclose(f);
}
