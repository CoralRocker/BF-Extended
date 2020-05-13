#include <stdio.h>
#include <string.h>

const char DISREGARD_NEWLINE = '\n';

/* Removes all useless spaces from source file and returns temporary
 * file with correct spaces.
 * closes file given.
 */
FILE* fremoveSpace(FILE* infile, FILE *tmp){
	char c, found;
	int charRead = 0;
	while((c = fgetc(infile))!=EOF){
		switch(c){
			case '"':
			case '@':
				found = c;
				fputc(c, tmp);
				char t;
				while((t = fgetc(infile)) != found){
					fputc(t, tmp);
				}
				putc(c, tmp);
				break;
			case '\n':
				//fputc(DISREGARD_NEWLINE, tmp);
				break;
			case '/':
				c = fgetc(infile);
				if(c == '*'){
					while(1){
						if(fgetc(infile) == '*')
						{
							if(fgetc(infile) == '/'){
								break;	
							}
						}
					}
				}else if(c == '/'){
					while(1){
						c = fgetc(infile);
						if(c == '\n' || c == EOF)
							break;
					}
				}else{
					fseek(infile, -1, SEEK_CUR);
				}
				break;
			case ' ':
				break;
			default:
				fputc(c, tmp);
				break;
		}
	}
	fclose(infile);
	rewind(tmp);
	return tmp;
}
