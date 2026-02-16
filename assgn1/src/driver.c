#include <stdio.h>
#include <stdlib.h>
#include "tokendef.h"

extern FILE *yyin;
extern int yylex(void);
extern char *yytext, *lexstr;

extern int yylineno, yycol;

void printToken(const int tokenNum) {
  switch(tokenNum) {
  case VARIABLE:
    printf("<VARIABLE, %s> : (%d:%d)\n", yytext, yylineno, yycol);
    break;
  case INTCONST:
    printf("<INTEGER, %s> : (%d:%d)\n", yytext, yylineno, yycol);
    break;
  case FLOATCONST:
    printf("<FLOAT, %s> : (%d:%d)\n", yytext, yylineno, yycol);
    break;
  case LPAREN:
    printf("<PUNCTUATION, (> : (%d:%d)\n", yylineno, yycol);
    break;
  case RPAREN:
    printf("<PUNCTUATION, )> : (%d:%d)\n", yylineno, yycol);
    break;
  case UNKNOWN:
    printf("<%s> %s: (%d:%d)\n", lexstr, yytext, yylineno, yycol);
    break;
  // tokenNum isn't in tokendef.h or handled in cases above
  // (this shouldn't happen)
  default:
    printf("<???> : (%d:%d)\n", yylineno, yycol);
    break;
  }
  return;
}

int main(int argc,char **argv) {
  FILE *infile = NULL;
  if (argc == 2 && (infile = fopen(argv[1],"r"))) {
    yyin = infile;
  }
  int ret = yylex();
  while (ret) {
    printToken(ret);
    ret = yylex();
  }
  if (infile) {
    fclose(infile);
  }
  return EXIT_SUCCESS;
}
