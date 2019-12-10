#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


char* rootDir(FILE* f, char* strname);
FILE* rootFile(FILE* f, char* strname, char* relativePath);

int main(int argc, char** argv){
	FILE* f = fopen(argv[1],"r");
	FILE* nf = rootFile(f, argv[1], argv[2]);
	if(nf)
		puts("NOT NULL");
	else
		puts("NULL");
	fputc('0', nf);
	fclose(f);
}

char* rootDir(FILE* f, char* strname){
	int file_descriptor = fileno(f);
	char* dirname = malloc(1024);
	char fdpath[1024];
	ssize_t n;
	sprintf(fdpath, "/proc/self/fd/%d", file_descriptor);
	n = readlink(fdpath, dirname, 1024);
	if(n < 0)
		return NULL;
	dirname[n] = 0x0;
	
	int strLen = strlen(strname);
	for(int i = n-1; i >= n - strLen; i--){
		if(dirname[i] == '/')
			break;
		dirname[i]=0x0;
	}
	printf("N: %d, STRLEN: %d\n", n, strlen(dirname));

	return dirname;
}

FILE* rootFile(FILE* f, char* strname, char* relativePath){
	char* rootdir = rootDir(f, strname);
	int rlen = strlen(rootdir);
	int alen = strlen(relativePath);

	for(int i = rlen; i < rlen+alen; i++)
		rootdir[i] = relativePath[i-rlen];

	rootdir[rlen+alen] = 0x00;
	puts(rootdir);
	
	FILE* newFile = fopen(rootdir, "w");

	free(rootdir);

	return newFile;
}
