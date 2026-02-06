#include <stdio.h>
#include <stdlib.h>
#include "tokendef.h"

//extern int yylex(void);
extern char *yytext;

extern int yylineno;
extern int yycol;

void printToken(const int tokenNum) {
  switch(tokenNum) {
  case CHARSCONST:
    printf("<CHARS, %s> : (%d:%d)\n", yytext, yylineno, yycol);
    break;
  case INTCONST:
    printf("<INTEGER, %s> : (%d:%d)\n", yytext, yylineno, yycol);
    break;
  case LPAREN:
    printf("<PUNCTUATION, (> : (%d:%d)\n", yylineno, yycol);
    break;
  case RPAREN:
    printf("<PUNCTUATION, )> : (%d:%d)\n", yylineno, yycol);
    break;
  case UNKNOWN:
    printf("<UNKNOWN TOKEN> %s: (%d:%d)\n", yytext, yylineno, yycol);
    break;
  default:
    printf("<???> : (%d:%d)\n", yylineno, yycol);
    break;
  }
  return;
}

int main(int argc,char **argv) {
  int ret = yylex();
  while (ret) {
    printToken(ret);
    ret = yylex();
  }
  return EXIT_SUCCESS;
}
