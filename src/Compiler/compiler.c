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
	printToFile("#include <stdio.h>\n#include \"Vector.h\"\nint main(){\n", out);
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
				printToFile("incVector(v);", out);
				break;
			case '-':
				printToFile("decVector(v);", out);
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

		}
	}

	printToFile("\nfreeVector(v);\n", out);
	printToFile("}\n", out);
	fclose(out);
	fclose(f);
}
