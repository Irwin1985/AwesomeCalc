#ifndef PARSER_H_
#define PARSER_H_

#include "token.h"
#include "lexer.h"
#include "ast.h"

typedef struct __parser Parser;

struct __parser {
	Lexer* lexer;
	void* ast;
};

Parser* parser_init(Lexer* lexer);
void parser_destroy(Parser* parser);
void* parse(Parser* parser);
void* parse_expression(Parser* parser);
void* parse_term(Parser* parser);
void* parse_factor(Parser* parser);

#endif