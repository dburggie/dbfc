#include <stdio.h>
#include <compile.h>

int main(int argc, char * argv[])
{
	//default filename
	char * output_filename = "output.bf.c";

	//3 args means we've passed an output filename and an input filename
	if (3 == argc)
	{
		output_filename = argv[1];
	}

	//if not 2 or 3 args, we didn't pass filenames right
	else if (2 != argc) return 1;

	//open input file
	FILE * input = fopen(argv[argc-1],"r");
	if (NULL == input) return 1;

	//read from input file
	char code[BUFFERSIZE];
	size_t codeLength = fread(code, sizeof(char), BUFFERSIZE, input);
	fclose(input);

	//exit if our file was too large
	if (codeLength >= BUFFERSIZE) return 1;

	//null terminate our code
	code[codeLength] = '\0';

	//compile and return
	if (compile(output_filename, code)) return 1;

	return 0;
}
