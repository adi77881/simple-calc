/* Simple integer arithmetic calculator

  according to the EBNF:
   <exp> ->  <term> ( <addop> <term> )
   <addop> -> + | -
   <term> -> <factor> ( <mulop> <factor> }
   <mulop> -> *
   <factor> -> ( <exp> ) | Number
   Inputs a line of text from stdin
   Outputs "Error" or the result.
*/

#include <stdio.h>
#include <stdlib.h>

char token; /* global token variable */

/* function prototypes for recursive calls */
int exp(void);
int term(void);
int factor(void);

void error(void)
{ fprintf(stderr,"Error\n");
  exit(1);
}

void match( char expectedToken)
{ if (token==expectedToken) {
    printf("%c",token);
    token = getchar();
  }
  else error();
}

main()
{ int result;
  printf("Enter any arithmetic expression: ");
  token = getchar(); /* load token with first
                        character for lookahead */
  result = exp();
  if (token=='\n') /* check for end of line */
    printf("\nResult = %d\n",result);
  else error(); /* extraneous chars on line */
  return 0;
}

int exp(void)
{ printf("E");
  int temp = term();
  while ((token=='+')||(token=='-'))
    switch (token) {
    case '+': match('+');
              temp+=term();
              break;
    case '-': match('-');
              temp-=term();
              break;
    }
  return temp;
}

int term(void)
{ printf("T");
  int temp = factor();
  while (token=='*') {
    match('*');
    temp*=factor();
  }
  return temp;
}

int factor(void)
{ printf("F");
  int temp;
  if (token=='(') {
    match('(');
    temp = exp();
    match(')');
  }
  else if (isdigit(token)) {
    ungetc(token,stdin);
    scanf("%d",&temp);
    printf("%d",temp);
    token = getchar();
  }
  else error();
  return temp;
}
