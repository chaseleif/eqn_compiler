/* The definition section contains a literal block and regular definitions */

%{
/* The literal block is C code in between %{ and %}
    We declare variables and prototype functions in this block
*/
#include <stdio.h>
#include <stdlib.h>
#include "tokendef.h"

 /* to pass static strings to driver */
char *lexstr;

 /* integers to track line and column numbers */
int scancol = 1;
int yycol = 1;
int scanlineno = 1;

/* TODO: functions to update line and column numbers */
void updateCol();
void countLines();

%}
/* regular definitions assign a regular expression to a name
    we assign newline to be an optional \r followed by a \n
    yylineno is set to 1 here
*/

newline    [\r]?[\n]
whitespace [\t ]+
integer    0|[1-9][0-9]*
float      {integer}\.(0|[0-9]*[1-9])
variable   [a-zA-Z]+

yylineno = 1;

/* the %% separates the next section */

%%

 /* The rules section associates regular expressions with C
    Each line has {expression} {C code}
 */
 /* NOTE: these comments cannot be at the beginning of the line ! */
 /*
    We can just use the character for the ( ) symbols
    regex special characters lose their meaning within quotes
    C escape characterse retain their meaning within quotes
    we use {newline} to refer to the definition in the section above
    return values are defined in tokendef.h
 */

"("           {updateCol(); return LPAREN;}
")"           {updateCol(); return RPAREN;}

{newline}     {countLines();}
{whitespace}  {updateCol();}

{integer}     {updateCol(); return INTCONST;}
{float}       {updateCol(); return FLOATCONST;}
{variable}    {updateCol(); return processChars();}

 /* The . regex matches everything except \n
    This is at the end of this section to catch anything not handled
    yytext is a char pointer handled externally
    We have char *yytext we can use with strcpy, printf, etc.
    Don't use functions that affect the memory, e.g., free, strdup, realloc.
 */
.             {
                lexstr = "IGNORED";
                updateCol();
                return UNKNOWN;
              }

%%

/* The user routine section provides space to define functions
*/
/* Make any characters in variables lowercase */
int processChars() {
  for (int i=0;yytext[i];++i) {
    yytext[i] |= 0x20;
  }
  return VARIABLE;
}

/* TODO:
    Implement functions to correctly keep track of column numbers
*/
void updateCol() {
  yycol=scancol;
  ++scancol;
}
void countLines() {
  yycol=scancol;
  scancol=1;
  ++yylineno;
}
