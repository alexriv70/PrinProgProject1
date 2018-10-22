/* -------------------------------------------------

            CFG for tinyL LANGUAGE

     PROGRAM ::= STMTLIST .
     STMTLIST ::= STMT MORESTMTS
     MORESTMTS ::= ; STMTLIST | epsilon
     STMT ::= ASSIGN | READ | PRINT
     ASSIGN ::= VARIABLE = EXPR
     READ ::= ! VARIABLE
     PRINT ::= # VARIABLE
     EXPR ::= + EXPR EXPR |
              - EXPR EXPR |
              * EXPR EXPR |
              VARIABLE | 
              DIGIT
     VARIABLE ::= a | b | c | d | e 
     DIGIT ::= 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9

     NOTE: tokens are exactly a single character long

     Example expressions:

           +12.
           +1b.
           +*34-78.
           -*+1+2a58.

     Example programs;

         !a;!b;c=+3*ab;d=+c1;#d.
         b=-*+1+2a58;#b.

 ---------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Instr.h"
#include "InstrUtils.h"
#include "Utils.h"

#define MAX_BUFFER_SIZE 500
#define EMPTY_FIELD 0xFFFFF
#define token *buffer

/* GLOBALS */
static char *buffer = NULL;	/* read buffer */
static int regnum = 1;		/* for next free virtual register number */
static FILE *outfile = NULL;	/* output of code generation */

/* Utilities */
static void CodeGen(OpCode opcode, int field1, int field2, int field3);
static inline void next_token();
static inline int next_register();
static inline int is_digit(char c);
static inline int to_digit(char c);
static inline int is_identifier(char c);
static char *read_input(FILE * f);

/* Routines for recursive descending parser LL(1) */
static void program();
static void stmtlist();
static void morestmts();
static void stmt();
static void assign();
static void read();
static void print();
static int expr();
static int variable();
static int digit();

/*************************************************************************/
/* Definitions for recursive descending parser LL(1)                     */
/*************************************************************************/
static int digit()
{
	int reg;

	if (!is_digit(token)) {
		ERROR("Expected digit\n");
		exit(EXIT_FAILURE);
	}
	reg = next_register();
	CodeGen(LOADI, reg, to_digit(token), EMPTY_FIELD);
	next_token();
	return reg;
}

static int variable()
{
	/* YOUR CODE GOES HERE */
	char tok = token;
if (!is_identifier(token)) {
		ERROR("Expected variable\n");
		exit(EXIT_FAILURE);
	}
	next_token();
	return tok;
}

static int expr()
{
	int reg, left_reg, right_reg;

	switch (token) {
	case '+':
		next_token();
		left_reg = expr();
		right_reg = expr();
		reg = next_register();
		CodeGen(ADD, reg, left_reg, right_reg);
		return reg;
		/* YOUR CODE GOES HERE */
	case '-':
		next_token();
		left_reg = expr();
		right_reg = expr();
		reg = next_register();
		CodeGen(SUB, reg, left_reg, right_reg);
		return reg;
	case '*':
		next_token();
		left_reg = expr();
		right_reg = expr();
		reg = next_register();
		CodeGen(MUL, reg, left_reg, right_reg);
		return reg;
	case '0':
		return digit();
	case '1':
		return digit();
	case '2':
		return digit();
	case '3':
		return digit();
	case '4':
		return digit();
	case '5':
		return digit();
	case '6':
		return digit();
	case '7':
		return digit();
	case '8':
		return digit();
	case '9':
		return digit();
	case 'a':
		return variable();
	case 'b':
		return variable();
	case 'c':
		return variable();
	case 'd':
		return variable();
	case 'e':
		return variable();
	default:
		ERROR("Symbol %c unknown\n", token);
		exit(EXIT_FAILURE);
	}
}

static void assign()
{
	/* YOUR CODE GOES HERE */
	int reg, left_reg, right_reg;
	switch(token){
		case 'a':
			left_reg = variable();
			right_reg =  expr();
			reg = next_register();
			CodeGen(STORE, reg,  left_reg, right_reg);
			next_token();
		case 'b':
			left_reg = variable();
			right_reg =  expr();
			reg = next_register();
			CodeGen(STORE, reg,  left_reg, right_reg);
			next_token();
		case 'c':
			left_reg = variable();
			right_reg =  expr();
			reg = next_register();
			CodeGen(STORE, reg,  left_reg, right_reg);
			next_token();
		case 'd':
			left_reg = variable();
			right_reg =  expr();
			reg = next_register();
			CodeGen(STORE, reg,  left_reg, right_reg);
			next_token();
		case 'e':
			left_reg = variable();
			right_reg =  expr();
			reg = next_register();
			CodeGen(STORE, reg,  left_reg, right_reg);
			next_token();
		default:
			ERROR("Assign error. Current input symbol is %c\n", token);
}}

static void read()
{
	CodeGen(READ, token, EMPTY_FIELD, EMPTY_FIELD);
	next_token();
	/* YOUR CODE GOES HERE */
}

static void print()
{
	CodeGen(WRITE,token, EMPTY_FIELD, EMPTY_FIELD),
	next_token();
	/* YOUR CODE GOES HERE */
}

static void stmt()
{
	/* YOUR CODE GOES HERE */
	switch(token){
	case 'a':
		assign();
	case 'b':
		assign();
	case 'c':
		assign();
	case 'd':
		assign();
	case 'e':
		assign();
	case '!':
		read();
	case '#':
		print();
	}
}

static void morestmts()
{
	/* YOUR CODE GOES HERE */
	switch(token){
		case ';':
			stmtlist();
		default:
			return;
}
}

static void stmtlist()
{
	/* YOUR CODE GOES HERE */
	switch(token){
	case 'a':
		stmt();
		morestmts();
	case 'b':
		stmt();
		morestmts();
	case 'c':
		stmt();
		morestmts();
	case 'd':
		stmt();
		morestmts();
	case 'e':
		stmt();
		morestmts();
	case '!':
		stmt();
		morestmts();
	case '#':
		stmt();
		morestmts();
	default:
	ERROR("Statement List error. Current input symbol is %c\n", token);
}
}
static void program()
{
	/* YOUR CODE GOES HERE */
	switch (token){
	case 'a':
		stmtlist();
	case 'b':
		stmtlist();
	case 'c':
		stmtlist();
	case 'd':
		stmtlist();
	case 'e':
		stmtlist();
	case '!':
		stmtlist();
	case '#':
		stmtlist();
	}
	next_token();
	if (token != '.') {
		ERROR("Program error. Current input symbol is %c\n", token);
		exit(EXIT_FAILURE);
	}
	return;
}


/*************************************************************************/
/* Utility definitions                                                   */
/*************************************************************************/
static void CodeGen(OpCode opcode, int field1, int field2, int field3)
{
	Instruction instr;

	if (!outfile) {
		ERROR("File error\n");
		exit(EXIT_FAILURE);
	}
	instr.opcode = opcode;
	instr.field1 = field1;
	instr.field2 = field2;
	instr.field3 = field3;
	PrintInstruction(outfile, &instr);
}

static inline void next_token()
{
	if (*buffer == '\0') {
		ERROR("End of program input\n");
		exit(EXIT_FAILURE);
	}
	printf("%c ", *buffer);
	if (*buffer == ';')
		printf("\n");
	buffer++;
	if (*buffer == '\0') {
		ERROR("End of program input\n");
		exit(EXIT_FAILURE);
	}
	if (*buffer == '.')
		printf(".\n");
}

static inline int next_register()
{
	return regnum++;
}

static inline int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return 1;
	return 0;
}

static inline int to_digit(char c)
{
	if (is_digit(c))
		return c - '0';
	WARNING("Non-digit passed to %s, returning zero\n", __func__);
	return 0;
}

static inline int is_identifier(char c)
{
	if (c >= 'a' && c <= 'e')
		return 1;
	return 0;
}

static char *read_input(FILE * f)
{
	size_t size, i;
	char *b;
	int c;

	for (b = NULL, size = 0, i = 0;;) {
		if (i >= size) {
			size = (size == 0) ? MAX_BUFFER_SIZE : size * 2;
			b = (char *)realloc(b, size * sizeof(char));
			if (!b) {
				ERROR("Realloc failed\n");
				exit(EXIT_FAILURE);
			}
		}
		c = fgetc(f);
		if (EOF == c) {
			b[i] = '\0';
			break;
		}
		if (isspace(c))
			continue;
		b[i] = c;
		i++;
	}
	return b;
}

/*************************************************************************/
/* Main function                                                         */
/*************************************************************************/

int main(int argc, char *argv[])
{
	const char *outfilename = "tinyL.out";
	char *input;
	FILE *infile;

	printf("------------------------------------------------\n");
	printf("CS314 compiler for tinyL\n");
	printf("------------------------------------------------\n");
	if (argc != 2) {
		ERROR("Use of command:\n  compile <tinyL file>\n");
		exit(EXIT_FAILURE);
	}
	infile = fopen(argv[1], "r");
	if (!infile) {
		ERROR("Cannot open input file \"%s\"\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	outfile = fopen(outfilename, "w");
	if (!outfile) {
		ERROR("Cannot open output file \"%s\"\n", outfilename);
		exit(EXIT_FAILURE);
	}
	input = read_input(infile);
	buffer = input;
	program();
	printf("\nCode written to file \"%s\".\n\n", outfilename);
	free(input);
	fclose(infile);
	fclose(outfile);
	return EXIT_SUCCESS;
}