%{
#include <iostream>
#include "../src/userClass.h"

using namespace std;
void yyerror(char *msg);
int yywrap(void);
int yylex(void);

%}

%union { 
   char *s; 
   DTDValidator * v;
   DTDNode * n;
   std::string * st;
   std::list<std::string> * ls;
   }

%token ELEMENT ATTLIST CLOSE OPENPAR CLOSEPAR COMMA PIPE FIXED EMPTY ANY PCDATA AST QMARK PLUS CDATA
%token <s> IDENT TOKENTYPE DECLARATION STRING
%type <st> attribute 
%type <ls> att_definition_opt

%%


main:  dtd_list_opt ;

dtd_list_opt
: dtd_element dtd_list_opt 
| dtd_attlist dtd_list_opt {/*$$ = $2; $$->addNode($1);*/} 
| {/*$$ = new DTDValidator();*/} ;

dtd_element
: ELEMENT IDENT cp CLOSE 
;
dtd_attlist
: ATTLIST IDENT att_definition_opt CLOSE {cout <<"NEW ATTLIS "<<$2<<" "<<$3->front()<<"\n";}
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
: att_definition_opt attribute { $$->push_back(*$2);}
| /* empty */ {$$ = new std::list<std::string>();}
;

attribute
: IDENT att_type default_declaration { $$ = new string($1);}
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

void dtdrestart(FILE * );

int parseDTDFile(char* file)
{
  int err;
  
  //yydebug = 1; // pour enlever l'affichage de l'éxécution du parser, commenter cette ligne

  printf("Trying to Parse %s\n", file);
  FILE * f;
  if((f = fopen(file, "r")) == NULL)
  {
    fprintf(stderr, "ERROR: No file named %s\n", file);
  }
  dtdrestart(f);
  err = dtdparse();
  fclose(f);
  
  if (err != 0) printf("Parse ended with %d error(s)\n", err);
    else  printf("Parse ended with success\n");
  
  return err;
}

int yywrap(void)
{
  return 1;
}

void yyerror(char *msg)
{
  fprintf(stderr, "%s\n", msg);
}


