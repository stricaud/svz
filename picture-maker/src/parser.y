%define api.prefix {svzl}
%param {svz_t **svz_image} {int *foo}

%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <svz/svz.h>
#include <svz/encode.h>
#include <svz/image.h>
#include <svz/basic-shapes.h>
#include <svz/draw-text.h>
	
#include <parser.h>

int svzllex(); 
extern void svzlerror(svz_t **svz, int *foo, const char *p);

#define SVZL_ABORT return -1;
#define SVZLERROR_VERBOSE

%}

%union {
	char *string;
	int integer;
}

%token <string>TOK_STRING
%token <integer>TOK_INTEGER
%token TOK_POINT
%token TOK_LINE
%token TOK_TEXT
%token TOK_RECTANGLE
%token TOK_CIRCLE
%token TOK_IMAGE_SIZE

%start input
%%

input:
      | input line
      | input point
      | input text
      | input rectangle
      | input circle
      | input imagesize
      ;

line: TOK_LINE TOK_INTEGER TOK_INTEGER TOK_INTEGER TOK_INTEGER
      {
//	      printf("->line (%d,%d->%d,%d)\n", $2, $3, $4, $5);
	      svz_draw_line(*svz_image, $2, $3, $4, $5);
	      svz_image_pixels_debug(*svz_image);
      }
      ;

point: TOK_POINT TOK_INTEGER TOK_INTEGER
       {
//	       printf("->POINT\n");
	       svz_draw_point(*svz_image, $2, $3);
       }
       ;

text: TOK_TEXT TOK_STRING TOK_INTEGER TOK_INTEGER
      {
//	      printf("THE text: ->%s<-\n", $2);
	      svz_draw_text(*svz_image, $2, $3, $4);
	      free($2);
      }
      ;

rectangle: TOK_RECTANGLE TOK_INTEGER TOK_INTEGER TOK_INTEGER TOK_INTEGER
           {
		   svz_draw_rectangle(*svz_image, $2, $3, $4, $5);
           }
           ;

circle: TOK_CIRCLE TOK_INTEGER TOK_INTEGER TOK_INTEGER
        {
		svz_draw_circle(*svz_image, $2, $3, $4);
        }
        ;

imagesize: TOK_IMAGE_SIZE TOK_INTEGER TOK_INTEGER
           {
		   printf("Creating a new image size\n");
		   *svz_image = svz_new($2, $3);
		   if (!*svz_image) {
			   printf("svz is null\n");
		   }
		   *foo = 42;
           }
           ;


%%

char *svzlget_text(void);
int svzlget_lineno (void);

void svzlerror(svz_t **svz, int *foo, const char *str)
{
	fprintf(stderr, "Parsing error: invalid token '%s' line %d: %s\n", svzlget_text(), svzlget_lineno(), str);
	exit(1);
}
