#include "parser.h"
#include "ast.h"

Parser* parser_init(Lexer* lexer)
{
	Parser* parser = (Parser*)malloc(sizeof(Parser));
	if (!parser)
	{
		printf("out of memory");
		exit(EXIT_FAILURE);
	}
	parser->lexer = lexer;

	return parser;
}

void parser_destroy(Parser* parser)
{
	if (parser->ast)
		free_node(parser->ast);

	lexer_destroy(parser->lexer);
	free(parser);
}

void* parse(Parser* parser) 
{
	parser->ast = parse_expression(parser);
}

void* parse_expression(Parser* parser)
{
	Lexer* lexer = parser->lexer;
	void* node = parse_term(parser);

	while (lexer->current_token.type == PLUS || lexer->current_token.type == MINUS)
	{
		token_t current_token = lexer->current_token;
		match(lexer, current_token.type); // eat the token

		BinaryOp_t* binop = (BinaryOp_t*)malloc(sizeof(BinaryOp_t));
		if (!binop)
		{
			printf("out of memory");
			exit(EXIT_FAILURE);
		}

		binop->type = AST_BINARY_OP;
		binop->left = node;
		binop->op = current_token;
		binop->right = parse_term(parser);

		node = binop; // con que este es el truco verdad?
	}

	return node;
}

void* parse_term(Parser* parser)
{
	Lexer* lexer = parser->lexer;
	void* node = parse_factor(parser);
	while (lexer->current_token.type == MULTIPLY || lexer->current_token.type == DIVIDE)
	{
		token_t current_token = lexer->current_token;
		match(lexer, current_token.type);

		BinaryOp_t* binop = (BinaryOp_t*)malloc(sizeof(BinaryOp_t));
		if (!binop)
		{
			printf("out of memory");
			exit(EXIT_FAILURE);
		}

		binop->type = AST_BINARY_OP;
		binop->left = node;
		binop->op = current_token;
		binop->right = parse_factor(parser);

		node = binop;
	}
	return node;
}

void* parse_factor(Parser* parser)
{
	Lexer* lexer = parser->lexer;
	token_t current_token = lexer->current_token;

	if (current_token.type == INTEGER)
	{
		match(lexer, INTEGER);
		NumAst_t* node = (NumAst_t*)malloc(sizeof(NumAst_t));
		if (!node)
		{
			printf("out of memory");
			exit(EXIT_FAILURE);
		}

		node->type = AST_NUM;
		node->operand = current_token;

		return node;
	}
	else if (current_token.type == LPAREN)
	{
		match(lexer, LPAREN);
		void* exp = parse_expression(parser);
		match(lexer, RPAREN);

		return exp;
	} 
	else if (current_token.type == PLUS || current_token.type == MINUS)
	{
		match(lexer, current_token.type); // match PLUS or MINUS (we dont need to know).
		UnaryOp_t* unaryop = (UnaryOp_t*)malloc(sizeof(UnaryOp_t));
		if (!unaryop)
		{
			printf("out of memory");
			exit(EXIT_FAILURE);
		}
		unaryop->type = AST_UNARY_OP;
		unaryop->op = current_token;
		unaryop->right = parse_expression(parser);

		return unaryop;
	}

}