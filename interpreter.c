#include "interpreter.h"

Interpreter* interpreter_init(Parser* parser)
{
	Interpreter* interpreter = (Interpreter*)malloc(sizeof(Interpreter));
	if (!interpreter)
	{
		printf("out of memory");
		exit(EXIT_FAILURE);
	}
	interpreter->parser = parser;

	return interpreter;
}

void interpreter_destroy(Interpreter* interpreter)
{
	parser_destroy(interpreter->parser);
	free(interpreter);
}

int interprete(Interpreter* interpreter)
{
	parse(interpreter->parser);

	return 0;
}