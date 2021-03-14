#include "ast.h"
#include "token.h"

int visit(void* node)
{
	AST_TYPE type = *(AST_TYPE *) node;
	switch (type)
	{
	case AST_NUM:
		return visit_NumNode((NumAst_t*)node);
	case AST_BINARY_OP:
		return visit_BinNode((BinaryOp_t*)node);
	case AST_UNARY_OP:
		return visit_UnaryNode((UnaryOp_t*)node);
	default:
		printf("ast.c: unknown ast node");
		exit(EXIT_FAILURE);
		break;
	}
}

int visit_NumNode(NumAst_t* node)
{
	return *(int*)node->operand.value;
}

int visit_BinNode(BinaryOp_t* node)
{
	switch (node->op.type)
	{
	case PLUS:
		return visit(node->left) + visit(node->right);
	case MINUS:
		return visit(node->left) - visit(node->right);
	case MULTIPLY:
		return visit(node->left) * visit(node->right);
	case DIVIDE:
		return visit(node->left) / visit(node->right);
	default:
		printf("ast.c: Unavailable op type\n");
		exit(EXIT_FAILURE);
	}
}

int visit_UnaryNode(UnaryOp_t* node)
{
	switch (node->op.type)
	{
	case PLUS:
		return visit(node->right) * 1;
	case MINUS:
		return visit(node->right) * -1;
	default:
		printf("ast.c: unknown operator.");
		exit(EXIT_FAILURE);
	}
}

void free_node(void* node)
{
	AST_TYPE type = *(AST_TYPE*)node;
	switch (type)
	{
	case AST_NUM:
		free(((NumAst_t*) node)->operand.value);
		break;

	case AST_BINARY_OP:
		free(((BinaryOp_t*)node)->left);
		free(((BinaryOp_t*)node)->right);
		break;

	}
}