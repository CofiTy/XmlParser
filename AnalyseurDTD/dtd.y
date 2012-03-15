%{
#define YYSTYPE double
#include <iostream>
#include "userClass.h"

void yyerror(char *msg);
int yywrap(void);
int yylex(void);

%}

%union { 
   char *s; 
   DTDValidator * v;
   DTDNode * n;
   }

%token ELEMENT ATTLIST CLOSE OPENPAR CLOSEPAR COMMA PIPE FIXED EMPTY ANY PCDATA AST QMARK PLUS CDATA
%token <s> IDENT TOKENTYPE DECLARATION STRING
%%


main: dtd_list_opt;

dtd_list_opt: dtd_list_opt dtd_element | dtd_list_opt dtd_attlist | ;

dtd_element
: ELEMENT IDENT cp CLOSE 
;
dtd_attlist
: ATTLIST IDENT att_definition_opt CLOSE         
;

cp: item card_opt;

item: IDENT | PCDATA | children;

children: choice_card | seq_card;

choice_card: choice card_opt;

seq_card: seq card_opt;

card_opt: QMARK | PLUS | AST | /*empty*/;

choice: OPENPAR choice_list_plus CLOSEPAR;
choice_list_plus: cp PIPE choice_list;
choice_list: choice_list PIPE cp | cp;

seq: OPENPAR seq_list CLOSEPAR;
seq_list: seq_list COMMA cp | cp;


att_definition_opt
: att_definition_opt attribute
| /* empty */
;

attribute
: IDENT att_type default_declaration
;

att_type
: CDATA    
| TOKENTYPE
| enumerate
;

enumerate
: OPENPAR enum_list_plus CLOSEPAR
;

enum_list_plus
: enum_list PIPE item_enum
;

enum_list
: item_enum               
| enum_list PIPE item_enum
;

item_enum
: IDENT
;

default_declaration
: DECLARATION 
| STRING     
| FIXED STRING 
;
%%
int main(int argc, char **argv)
{
  int err;

//  yydebug = 1; // pour désactiver l'affichage de l'exécution du parser LALR, commenter cette ligne

  err = yyparse();
  if (err != 0) printf("Parse ended with %d error(s)\n", err);
        else  printf("Parse ended with success\n", err);
  return 0;
}
int yywrap(void)
{
  return 1;
}

void yyerror(char *msg)
{
  fprintf(stderr, "%s\n", msg);
}


