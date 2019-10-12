#include <stdio.h>
#include <sys/types.h>

int main(int argc, char **argv)
{
	/* Pointer */
	long array[16384];
	long *p = array;

	/* Files */
	FILE *f = fopen(argv[1], "r");
	FILE *out = fopen("bf.c", "w");
	
	/* File Setup */
	fwrite("#include <stdio.h>\nint main(){\n", 31, 1, out);
	fwrite("char arr[1024] = {0};\nchar *p = arr;\n", 37, 1, out);
	
	/* Compile Loop */
	char cur;
	while((cur = fgetc(f)) != EOF)
	{

		switch(cur)
		{
			case '>':
				fwrite("++p;\n", 5 , 1, out);
				break;
			case '<':
				fwrite("--p;\n", 5, 1, out);
				break;
			case '+':
				fwrite("++*p;\n", 6, 1, out);
				break;
			case '-':
				fwrite("--*p;\n", 6, 1, out);
				break;
			case '.':
				fwrite("printf(\"%c\", *p);\n", 18, 1, out);	
				break;
			case ',':
				fwrite("*p = getchar();\n", 16, 1, out);
				break;
			case '[':
				if(fgetc(f) == '-' && fgetc(f) == ']')
				{
					fwrite("*p = 0;\n",8, 1, out);
				}else{
					fseek(f, -1, SEEK_CUR);
					fwrite("while(*p){\n", 11, 1, out);
				}
				break;
			case ']':
				fwrite("}\n", 2, 1, out);
				break;
		}
	}
	/* Close Files */
	fwrite("}\n", 2, 1, out);
	fclose(out);
	fclose(f);
}	
