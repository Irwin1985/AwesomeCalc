#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "token.h"
#include "lexer.h"

Lexer* lexer_init(const char* text)
{
	Lexer* lexer = (Lexer*)malloc(sizeof(Lexer));
	if (!lexer) exit(EXIT_FAILURE, "out of memory");
	
	lexer->pos = 0;
	lexer->text = text;
	lexer->len = strlen(text);
	lexer->current_char = lexer->text[0];
	lexer->current_token = get_next_token(lexer);

	return lexer;
}

void lexer_destroy(Lexer* lexer)
{
	free(lexer);
}

static void advance(Lexer* lexer)
{
	lexer->pos += 1;
	if (lexer->pos >= lexer->len)
	{
		lexer->current_char = EOF;
	}
	else
	{
		lexer->current_char = lexer->text[lexer->pos];
	}
}

token_t integer(Lexer* lexer)
{
	char number[_AVAILABLE_DIGITS];
	int i = 0;
	do
	{
		number[i++] = lexer->current_char;
		advance(lexer);
	} while (lexer->current_char != EOF && isdigit(lexer->current_char));
	number[i] = '\0';

	token_t ret = { .type = NONE, .value = NULL };
	ret.value = malloc(sizeof(int));

	if (!ret.value)
	{
		printf("out of memory");
		exit(EXIT_FAILURE);
	}

	*(int*)ret.value = atoi(number);
	ret.type = INTEGER;

	return ret;
}

void skip_whitespace(Lexer* lexer)
{
	do {
		advance(lexer);
	} while (lexer->current_char != EOF && isspace(lexer->current_char));
}

token_t get_next_token(Lexer* lexer)
{
	token_t ret = { .type = NONE, .value = NULL };
	while (lexer->current_char != EOF)
	{
		if (isspace(lexer->current_char))
		{
			skip_whitespace(lexer);
			continue;
		}
		if (isdigit(lexer->current_char))
		{
			return integer(lexer);
		}
		if (lexer->current_char == '+')
		{
			ret.type = PLUS;
			advance(lexer);
			return ret;
		}
		if (lexer->current_char == '-')
		{
			ret.type = MINUS;
			advance(lexer);
			return ret;
		}
		if (lexer->current_char == '*')
		{
			ret.type = MULTIPLY;
			advance(lexer);
			return ret;
		}
		if (lexer->current_char == '/')
		{
			ret.type = DIVIDE;
			advance(lexer);
			return ret;
		}
		if (lexer->current_char == '(')
		{
			ret.type = LPAREN;
			advance(lexer);
			return ret;
		}
		if (lexer->current_char == ')')
		{
			ret.type = RPAREN;
			advance(lexer);
			return ret;
		}
		printf("unknown character '%c'\n", lexer->current_char);
		exit(EXIT_FAILURE);
	}
	return ret;
}

void match(Lexer* lexer, TYPE type)
{
	if (lexer->current_token.type == type)
	{
		lexer->current_token = get_next_token(lexer);
	}
	else
	{
		printf("unexpected token. got='%s', want='%d'", (char*)lexer->current_token.value, type);
		exit(EXIT_FAILURE);
	}
}