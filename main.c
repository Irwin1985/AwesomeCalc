#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "token.h"
#include "parser.h"
#include "interpreter.h"
#define MAX_STRING_LEN 1024

int main(int argc, char* argv[])
{
	char text[MAX_STRING_LEN];
	printf(">>");
	while (1)
	{
		if (fgets(text, MAX_STRING_LEN, stdin) && strlen(text) >= 2)
		{
			Lexer* lexer = lexer_init(text);
			Parser* parser = parser_init(lexer);
			Interpreter* interpreter = interpreter_init(parser);
			interprete(interpreter);
			int result = visit(interpreter->parser->ast);
			printf("%d\n", result);
			interpreter_destroy(interpreter);
			printf(">>");
		}
	}
	return 0;
}