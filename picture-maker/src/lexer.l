%{
/* svzl: svz language */
#include <stdio.h>
#include <svz/svz.h>
#include <parser.h>

void svzlerror (const char *s);

#define YY_EXTRA_TYPE struct svz_t *

%}

%option noyywrap
%option 8bit prefix="svzl"


VOID [ \t]+
COMMENT #.*\n

%%

{VOID} {}
{COMMENT} {}

image\.size { return TOK_IMAGE_SIZE; }

\"(.*)\" {
           svzllval.string = strdup(svzltext);
           return TOK_STRING;
         }
[0-9]+   {
           svzllval.integer = (int)strtol(svzltext, NULL, 10);
           return TOK_INTEGER;
         }

point { return TOK_POINT; }
line { return TOK_LINE; }
text { return TOK_TEXT; }
rectangle { return TOK_RECTANGLE; }
circle { return TOK_CIRCLE; }

\n { svzlset_lineno(svzlget_lineno()+1); }

%%

