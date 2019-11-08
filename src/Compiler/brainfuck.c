#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>

int main(int argc, char** argv){
	char *ifname = NULL, *ofname = NULL;

	int opt;
	while((opt = getopt(argc, argv, "o:f:h")) != -1){
		switch(opt){
			case 'o':
				puts(optarg);
				ofname = optarg;
				break;
			case 'f':
				puts(optarg);
				ifname = optarg;
				break;
			case 'h':
				break;
		}
	}

	if(!ifname){
		puts("Input file is required!\nUse -f flag to name input file");
		return -1;
	}

	FILE *infile = fopen(ifname, "r");
	FILE *outfile = fopen(((ofname)?ofname:"BFE.asm"), "w");


	char c;
	while((c = fgetc(infile))!=EOF){
		switch(c){
			
		}
	}


	fclose(infile);
	fclose(outfile);
}
