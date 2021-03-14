#ifndef AST_H_
#define AST_H_

#include "token.h"

typedef enum {
	AST_UNARY_OP,
	AST_BINARY_OP,
	AST_NUM,
} AST_TYPE;

typedef struct __unary_operation_ast UnaryOp_t;

struct __unary_operation_ast {
	AST_TYPE type;
	token_t op;
	void* right;
};

typedef struct __binary_operation_ast BinaryOp_t;
struct __binary_operation_ast {
	AST_TYPE type;
	token_t op;
	void* left;
	void* right;
};

typedef struct __number_ast NumAst_t;
struct __number_ast {
	AST_TYPE type;
	token_t operand;
};

int visit(void* node);
void free_node(void* node);

#endif