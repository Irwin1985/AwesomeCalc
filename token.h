#ifndef TOKEN_H_
#define TOKEN_H_
#include <stdlib.h>
#include <stdio.h>

typedef enum {
	INTEGER,
	PLUS,
	MINUS,
	MULTIPLY,
	DIVIDE,
	LPAREN,
	RPAREN,
	NONE
} TYPE;

typedef struct __token token_t;
struct __token {
	TYPE type;
	void* value;
};

#endif