#include <stdio.h>
#include <compile.h>

static int counter(const char * code_point, const char plus);

/* Translates Brainfuck source into C source code
 * Compile the C source code however you wish for a native binary
 * */

int compile(const char const * filename, const char const * code)
{
	FILE * output = fopen(filename,"w");

	if (NULL == output) return 1;

	int depth = 1;

	int i = 0,j = 0;
	int count = 1;

	fprintf(output, "#include <stdio.h>\nint main()\n{\n");
	fprintf(output, "\tunsigned char buf[%i] = { 0 };\n", BUFFERSIZE);
	fprintf(output, "\tint p = 0;\n\n");

	while (code[i])
	{
		switch (code[i])
		{
			case '>':
				count = counter(code + sizeof(char) * i, '>');
				for (j = 0; j < depth; j++) fprintf(output,"\t");
				fprintf(
					output, 
					"p += %i; if (p >= %i) return 1;\n", 
					count, BUFFERSIZE
				);
				break;

			case '<':
				count = counter(code + sizeof(char) * i, '<');
				for (j = 0; j < depth; j++) fprintf(output,"\t");
				fprintf(output, "p -= %i; if (p < 0) return 1;\n", count);
				break;

			case '+':
				count = counter(code + sizeof(char) * i, '+');
				for (j = 0; j < depth; j++) fprintf(output,"\t");
				fprintf(output, "buf[p] += %i;\n", count & 0xff);
				break;

			case '-':
				count = counter(code + sizeof(char) * i, '-');
				for (j = 0; j < depth; j++) fprintf(output,"\t");
				fprintf(output, "buf[p] -= %i;\n", count & 0xff);
				break;

			case ',':
				count = 1;
				for (j = 0; j < depth; j++) fprintf(output,"\t");
				fprintf(output,
					"if (!feof(stdin)) buf[p] = getchar(); else buf[p] = 0xff;\n"
				);
				break;

			case '.':
				count = 1;
				for (j = 0; j < depth; j++) fprintf(output,"\t");
				fprintf(output, "putchar(buf[p]);\n");
				break;

			case '[':
				count = 1;
				for (j = 0; j < depth; j++) fprintf(output,"\t");
				fprintf(output, "while (buf[p])\n");
				for (j = 0; j < depth; j++) fprintf(output,"\t");
				fprintf(output, "{\n");
				depth++;
				break;

			case ']':
				count = 1;
				depth--;
				for (j = 0; j < depth; j++) fprintf(output,"\t");
				fprintf(output, "}\n");
				break;

			default:
				count = 1;
				break;
		}//end switch

		i += count;
	}//end while

	fprintf(output, "\n\treturn 0;\n}\n");
	fclose(output);

	return 0;
}



//count consecutive operations so we can combine incs or shifts
static int counter(const char * code_point, const char plus)
{
	int count = 0;
	int i = 0;

	while (plus == code_point[i++]) count++;

	return count;
}
