#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include <stdlib.h>
#include <stdio.h>
#include "token.h"
#include "lexer.h"
#include "ast.h"
#include "parser.h"

typedef struct __interpreter Interpreter;

struct __interpreter {
	Parser* parser;
};

Interpreter* interpreter_init(Parser* parser);
void interpreter_destroy(Interpreter* interpreter);
int interprete(Interpreter* interpreter);

#endif