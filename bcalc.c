#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
// #include <math.h>

// -----------------------------------
// Tokenizer
// -----------------------------------
// A tokenizer converts the input expression into a sequence of tokens that the
// parser can process. Each token can represent:
// - Numbers
// - Operators {+, -, *, /}
// - Parenthesis {(. )}
// -----------------------------------

typedef enum
{
	TOKEN_NUMBER,
	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_MULTIPLY,
	TOKEN_DIVIDE,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_END,
	TOKEN_INVALID
} TokenType;

typedef struct
{
	TokenType type;
	double value; // Only used for numbers
} Token;

const char *input;
size_t pos = 0;

Token get_next_token()
{
	Token token = {TOKEN_INVALID, 0};
	while (input[pos] != '\0' && isspace(input[pos]))
	{
		pos++; // Skip white spaces
	}

	if (input[pos] == '\0')
	{
		token.type = TOKEN_END;
		return token;
	}

	if (isdigit(input[pos]) || input[pos] == '.')
	{
		token.type = TOKEN_NUMBER;
		token.value = 0;
		int decimal_point = 0;

		while (isdigit(input[pos]) || (input[pos] == '.' && !decimal_point))
		{
			if (input[pos] == '.') 
			{
				decimal_point = 1;	// Only one decimal point allowed
				pos++;
				continue;
			}
			
			token.value = token.value * 10 + (input[pos] - '0');
			if (decimal_point)
			{
				decimal_point *= 10;
			}
			pos++;
		}

		if (decimal_point)
		{
			token.value /= decimal_point;
		}
		return token;
	}

	switch (input[pos])
	{
	case '+':
	{
		token.type = TOKEN_PLUS;
		pos++;
		break;
	}
	case '-':
	{
		token.type = TOKEN_MINUS;
		pos++;
		break;
	}
	case '*':
	{
		token.type = TOKEN_MULTIPLY;
		pos++;
		break;
	}
	case '/':
	{
		token.type = TOKEN_DIVIDE;
		pos++;
		break;
	}
	case '(':
	{
		token.type = TOKEN_LPAREN;
		pos++;
		break;
	}
	case ')':
	{
		token.type = TOKEN_RPAREN;
		pos++;
		break;
	}
	default:
	{
		token.type = TOKEN_INVALID;
		break;
	}
	}
	return token;
}

// -----------------------------------
// Recusive-decent parser
// -----------------------------------
// Implementing functions for each of the operations, starting from the highest
// precedence (*, /) to lowerst precedence (+, -)
// The structure of the parser should be:
// - Expression: Handles addition and subtraction
// - Term: Handles multiplication and division
// - Factor: Handles numbers and parenthesized expressions
// -----------------------------------

Token current_token;

void next_token()
{
	current_token = get_next_token();
}

// Forward declarations for parser functions
double parse_expression();
double parse_term();
double parse_factor();

// Factor: Handles numbers and parenthesis
double parse_factor()
{
	double result = 0;

	if (current_token.type == TOKEN_NUMBER)
	{
		result = current_token.value;
		next_token(); // Move to next token
	}
	else if (current_token.type == TOKEN_LPAREN)
	{
		next_token();				 // Consume '('
		result = parse_expression(); // Parse inside parenthesis
		if (current_token.type != TOKEN_RPAREN)
		{
			fprintf(stderr, "Error: Expected closing parenthesis\n");
			exit(1);
		}
		next_token(); // Consume ')'
	}
	else
	{
		fprintf(stderr, "Error: Unexpected token\n");
		exit(1);
	}
	return result;
}

// Term: Handles multiplication and division
double parse_term()
{
	double result = parse_factor();

	while (current_token.type == TOKEN_MULTIPLY || current_token.type == TOKEN_DIVIDE)
	{
		if (current_token.type == TOKEN_MULTIPLY)
		{
			next_token(); // Consume '*'
			result *= parse_factor();
		}
		else if (current_token.type == TOKEN_DIVIDE)
		{
			next_token(); // Consume '/'
			double divisor = parse_factor();
			if (divisor == 0)
			{
				fprintf(stderr, "Error: Division by zero\n");
				exit(1);
			}
			result /= divisor;
		}
	}
	return result;
}

// Expression: Handles addition and subtraction
double parse_expression()
{
	double result = parse_term();

	while (current_token.type == TOKEN_PLUS || current_token.type == TOKEN_MINUS)
	{
		if (current_token.type == TOKEN_PLUS)
		{
			next_token(); // Consume '+'
			result += parse_term();
		}
		else if (current_token.type == TOKEN_MINUS)
		{
			next_token(); // Consume '-'
			result -= parse_term();
		}
	}
	return result;
}

// -----------------------------------
// Evaluate line
// -----------------------------------
// It initializes first token and resets position so that parse_expression() is called
// -----------------------------------

double eval(const char *line)
{
	input = line;
	pos = 0;	  // Reset position
	next_token(); // Initialize first token

	double result = parse_expression();

	if (current_token.type != TOKEN_END)
	{
		fprintf(stderr, "Error: Unexpected token after expression\n");
		exit(1);
	}

	return result;
}

// -----------------------------------
// bcalc main
// -----------------------------------

void print_help()
{
	printf("usage: bcalc [options] [file ...]\n");
	printf("  -h  --help		print this usage and exit\n");
	printf("  -l  --mathlib		use the predefined math routines\n");
	printf("  -q  --quiet		don't print initial banner\n");
	printf("  -v  --version		print version information and exit\n");
}

void print_version()
{
	printf("bcalc 1.0.0\n");
}

int main(int argc, char *argv[])
{
	int quiet = 0;
	int mathlib = 0;
	// ---- Option Parsing ----
	if (argc > 1)
	{
		char *arg = argv[1];
		if (strcmp(arg, "-h") == 0 || strcmp(arg, "--help") == 0)
		{
			print_help();
			return 0;
		}
		else if (strcmp(arg, "-v") == 0 || strcmp(arg, "--version") == 0)
		{
			print_version();
			return 0;
		}
		else if (strcmp(arg, "-q") == 0 || strcmp(arg, "--quiet") == 0)
		{
			quiet = 1;
		}
		else if (strcmp(arg, "-l") == 0 || strcmp(arg, "--mathlib") == 0)
		{
			mathlib = 1;
		}
		else
		{
			printf("Invalid option: %s\n", arg);
			print_help();
			return 1;
		}
	}
	// ---- BANNER ----
	if (!quiet)
	{
		print_version();
		printf("Press Ctrl+C to quit...\n");
	}
	// ---- MATHLIB INITIALIZATION ----
	if (mathlib)
	{
		printf("Mathlib Initialized...\n");
	}

	char line[128];
	while (fgets(line, sizeof(line), stdin))
	{
		double result = eval(line);
		printf("%g\n", result);
	}

	return 0;
}
