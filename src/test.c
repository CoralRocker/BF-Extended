#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	FILE *program;
//	char **memstream;
//	size_t mem_len;
//	program = open_memstream(memstream, &mem_len);
	program = fopen(".BFE-env", "w+");	
	char* line = NULL;
	size_t len = 0;
	int counter = 0;
	off_t pos;

	while(getline(&line, &len, stdin) != -1){
		//puts(memstream[0]);
		pos = ftell(program);
		fputs(line, program);
		fseek(program, pos, SEEK_SET);
		char c;
		while((c = fgetc(program))!=EOF){
			switch(c){
				case 'a':
					printf("a");
					break;
				case 'b':
					printf("b");
					break;
			}
		}
		puts("");

		counter++;
		if(counter == 4)
			break;
		free(line);
		len = 0;
	}

	

	fclose(program);
	//free(memstream);
	remove(".BFE-env");
}
