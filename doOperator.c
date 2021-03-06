#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "doOperator.h"
#include "tokenStack.h"
#include "lexical.h"

/* Operations to complete Lab requirements
    Need to add 6 more methods/routines
*/
static int op_quit(struct tokenStack *stack);
static int op_print(struct tokenStack *stack);
static int op_dump(struct tokenStack *stack);
static int op_add(struct tokenStack *stack);

static int op_diff(struct tokenStack *stack);
static int op_mult(struct tokenStack *stack);
static int op_div(struct tokenStack *stack);
static int op_grtr(struct tokenStack *stack);
static int op_less(struct tokenStack *stack);
static int op_grtEq(struct tokenStack *stack);
static int op_lsEq(struct tokenStack *stack);
static int op_eqlt(struct tokenStack *stack);
static int op_modQt(struct tokenStack *stack);
static int op_if(struct tokenStack *stack);  /* is v passed as parameter?*/
static int op_mdCp(struct tokenStack *stack);
static int op_swap(struct tokenStack *stack);
static int op_help(struct tokenStack *stack);
static int op_rotat(struct tokenStack *stack);
static int op_rtMn(struct tokenStack *stack);
static int op_drop(struct tokenStack *stack);
static int op_prtS(struct tokenStack *stack);


/* From Jenkin*/
static struct operator_struct {
  char *name;
  int (*fn_ptr)(struct tokenStack *);
} ops[] = {
  {"quit",  op_quit},
  {"print", op_print},
  {"dump",  op_dump},
  {"+",     op_add},
  {"-",     op_diff},
  {"*",     op_mult},
  {"/",     op_div},
  {"GT",     op_grtr},
  {"LT",     op_less},
  {"GE",    op_grtEq},
  {"LE",    op_lsEq},
  {"EQ",    op_eqlt},
  {"MOD",   op_mdCp},
  {"IF",     op_if},
  {"MODQUOT",     op_modQt},
  {"SWAP",    op_swap},
  {"HELP",   op_help},
  {"ROT",    op_rotat},
  {"ROTMINUS", op_rtMn},
  {"DROP", op_drop},
  {"S",     op_prtS},
  {(char *)NULL, (int(*)(struct tokenStack *)) NULL}
};


/* YOU WRITE THIS */
static int popInt(struct tokenStack *s)
{
	struct lexToken *tokenCoiner = popTokenStack(s);
	return atoi(tokenCoiner->symbol);
		/*
    if((s != (struct tokenStack *)NULL) && (s->top > 0))
    {
        return atoi(s->e[s->top--]->symbol);
    }*/
}

/* YOU WRITE THIS */
static void pushInt(struct tokenStack *s, int v)
{
    struct lexToken *tokenInt = allocToken();
    sprintf(tokenInt->symbol,"%d", v);
    tokenInt->kind = LEX_TOKEN_NUMBER;
	pushTokenStack(s , tokenInt);

/*    s->e[s->top++] = tokenInt; */
    /* might need to use free(tokenInt); to deallocate it. */
}

int doOperator(struct tokenStack *stack, char *o) 
{
  struct operator_struct *op = ops;
  for(op=ops;op->name != (char *)NULL; op++) {
    if(!strcmp(op->name, o))
      return op->fn_ptr(stack);
  }
  return(-1);
}

/*ARGSUSED*/
static int op_quit(struct tokenStack *stack)
{
  printf("[quit]\n");
  exit(0);
  /*NOTREACHED*/
}

static int op_print(struct tokenStack *stack)
{
  struct lexToken *t = popTokenStack(stack);
  printToken(stdout, t);
  freeToken(t);
  return(0);
}

static int op_dump(struct tokenStack *stack)
{
  struct lexToken *t = popTokenStack(stack);
  dumpToken(stdout, t);
  freeToken(t);
  return(0);
}

static int op_add(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v1+v2);
  return(0);
}

static int op_drop(struct tokenStack *stack)
{
    popTokenStack(stack);
    return (0);
}

static int op_diff(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v2-v1); 
    return (0);
}

static int op_mult(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v1*v2); 
    return (0);
}

static int op_div(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
	if(v1 == 0)
	{
		return fprintf(stderr, "%s", "Can't devide by zero"); 
		
	}
  pushInt(stack, v2/v1); 
    return (0);
}
/*  GT (n1 n2 — gt) -push 1 if n1 > n2 and 0 otherwise  */
static int op_grtr(struct tokenStack *stack)
{
  int v1, v2;
  v2 = popInt(stack);
  v1 = popInt(stack);
  if(v1 > v2)
  {
    pushInt(stack, 1); 
  }
  else
  {
    pushInt(stack, 0);   
  }
    return 0;
}

/* LT (n1 n2 — lt) -push 1 if n1 < n2 and 0 otherwise */
static int op_less(struct tokenStack *stack)
{
  int v1, v2;
  v2 = popInt(stack);
  v1 = popInt(stack);
  if(v1 < v2)
  {
    pushInt(stack, 1); 
  }
  else
  {
    pushInt(stack, 0);   
  }
    return (0);
}

/* GE (n1 n2 — ge) -push 1 if n1 >= n2 and 0 otherwise */
static int op_grtEq(struct tokenStack *stack)
{
  int v1, v2;
  v2 = popInt(stack);
  v1 = popInt(stack);
  if(v1 >= v2)
  {
    pushInt(stack, 1); 
  }
  else
  {
    pushInt(stack, 0);   
  }
    return (0);
}

/* LE (n1 n2 — le) -push 1 if n1 <= n2 and 0 otherwise */
static int op_lsEq(struct tokenStack *stack)
{
  int v1, v2;
  v2 = popInt(stack);
  v1 = popInt(stack);
  if(v1 <= v2)
  {
    pushInt(stack, 1); 
  }
  else
  {
    pushInt(stack, 0);   
  }
    return (0);
}

/* EQ (n1 n2 — eq) -push 1 if n1 == n2 and 0 otherwise */
static int op_eqlt(struct tokenStack *stack)
{
  int v1, v2;
  v2 = popInt(stack);
  v1 = popInt(stack);
  if(v1 == v2)
  {
    pushInt(stack, 1); 
  }
  else
  {
    pushInt(stack, 0);   
  }
    return (0);
}

/*  MOD (n1 - n1 n1) - push two copies of n1 onto the stack  */
static int op_mdCp(struct tokenStack *stack)
{
    int v1;
    v1 = popInt(stack);
    pushInt(stack, v1); 
    pushInt(stack, v1); 
    return (0);
}

/* IF (n1 n2 v — x) - if v is not zero then push n1 otherwise n2  */

static int op_if(struct tokenStack *stack)
{
  int v1, v2 , n;
  n = popInt(stack);
  v2 = popInt(stack);
  v1 = popInt(stack);
  if(n == 0)
  {
    pushInt(stack, v2); 
  }
  else
  {
    pushInt(stack, v1);   
  }
    return (0);
}


/* MODQUOT (n1 n2 — rem quotient) - push remainder then quotient  */
static int op_modQt(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v2%v1);
  pushInt(stack, v2/v1);
    return (0);
}

/* SWAP (n1 n2 — n2 n1) - swap the order of the top two elements on
the stack  */
static int op_swap(struct tokenStack *stack)
{
  int v1, v2;
  v2 = popInt(stack);
  v1 = popInt(stack);
  pushInt(stack, v1);
  pushInt(stack, v2);
    return (0);
}

/* HELP (—) - print out all commands plus a line of documentation. Note:
This is made easier due to the help string in the table.  */
static int op_help(struct tokenStack *stack)
{
  	printf("%s\n", "To ADD values together, use the + operator ");
    printf("%s\n", "To SUBTRACT values together, use the - operator ");
    printf("%s\n", "To MULTIPLY values together, use *");
    printf("%s\n", "To DIVIDE values, use the / operator");
    printf("%s\n", "To COMPARE LARGER (>) values, use the GT operator");
    printf("%s\n", "To COMPARE LESS (<) values, use the LT operator");
    printf("%s\n", "TO COMPARE GREATER THAN or EQUAL (>=), use the GE operator");
    printf("%s\n", "TO COMPARE LESS THAN or EQUAL (>=), use the GE operator");
    printf("%s\n", "To COMPARE EQUAL (==) values, use the EQ operator");
    printf("%s\n", "To push 2 copies of n1 onto the stack use MOD operator");

    printf("%s\n", "To create if statement, use IF operator");
    printf("%s\n", "Push remainder then quotient use MODQUOT");
    printf("%s\n", "To create SWAP operator, use the SWAP");
    printf("%s\n", "To rotate top 3 elements on stack use ROT");
    printf("%s\n", "To rotate top 3 elements on the stack, use ROTMINUS");
    printf("%s\n", "To drop the top element off of the stack use DROP");
    printf("%s\n", "Print all elements on the stack non destructively, use S");
    return 0;
}

/* ROT (n1 n2 n3 — n2 n3 n1) - rotate top 3 elements on the stack  */
static int op_rotat(struct tokenStack *stack)
{
  int v1, v2, v3;
  v3 = popInt(stack);
  v2 = popInt(stack);
  v1 = popInt(stack);
  pushInt(stack, v1);
  pushInt(stack, v3);
  pushInt(stack, v2);
    return (0);
}

/* ROTMINUS (n1 n2 n3 — n3 n1 n2) - rotate top 3 elements on the stack  */
static int op_rtMn(struct tokenStack *stack)
{
  int v1, v2, v3;
  v3 = popInt(stack);
  v2 = popInt(stack);
  v1 = popInt(stack);
  pushInt(stack, v2);
  pushInt(stack, v1);
  pushInt(stack, v3);
    return (0);
}

/* S (—) - print all elements on the stack non destructively  */
static int op_prtS(struct tokenStack *stack)
{
	int j;
	j = stack->top;
	if(j <= 0)
	{
		return fprintf(stderr,"%s", "there is nothing on the stack, Program still runs");
	}
	while(j != 0)
	{
		printf("%s\n",stack->e[--j]->symbol);
	}
    return (0);
}

