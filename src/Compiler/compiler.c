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
	printToFile("#include <stdio.h>\n#include \"Vector.h\"\n", out);
	printToFile("void trimMemory(vector* v){int option = curVector(v);if(option==0){int pos = v->size-1;while(pos != 0){int val = atVector(v, pos);if(val == 0)popBackVector(v);else if(val != 0) break; pos--;}}else{int pos = 0; while(pos < v->size){if(atVector(v,pos)==option)eraseVector(v,pos);else pos++;}}if(v->curpos >= v->size)v->curpos=v->size-1; else if(v->size <= 0){pushBackVector(v, 0);v->curpos=0;}}\n", out);
	printToFile("int main(){\n", out);
	printToFile("vector *v = initVector();\npushBackVector(v, 0);\n", out);

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
					int breakout = 0;
					printf("Entering comment\n");
					while(1){
						if(fgetc(f) == '*')
						{
							//puts("Found *");
							if(fgetc(f) == '/'){
							//	printf("Exiting comment\n");
								break;	
							}
						}
							//printf("going back one\t");
							//fseek(f, -1, SEEK_CUR); // Skip one character ahead
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
				printToFile("trimMemory(v);", out);
				break;
		}
	}

	printToFile("\nfreeVector(v);\n", out);
	printToFile("}\n", out);
	fclose(out);
	fclose(f);
}
