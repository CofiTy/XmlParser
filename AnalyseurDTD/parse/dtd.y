%{
#include <iostream>
#include "../src/userClass.h"

using namespace std;
void yyerror(DTDValidator ** validator, char *msg);
int yywrap(void);
int yylex(void);

%}

%parse-param {DTDValidator ** validator}

%union { 
   char *s; 
   DTDValidator * v;
   DTDNode * n;
   std::string * st;
   std::list<std::string> * ls;
   std::pair<std::string, std::list<std::string> > * p;
   }

%token ELEMENT ATTLIST CLOSE OPENPAR CLOSEPAR COMMA PIPE FIXED EMPTY ANY  AST QMARK PLUS CDATA
%token <s> IDENT TOKENTYPE DECLARATION STRING PCDATA
%type <st> attribute item card_opt cp children choice_card choice choice_list_plus seq seq_card seq_list choice_list
%type <ls> att_definition_opt
%type <n> dtd_element
%type <v> main dtd_list_opt
%type <p> dtd_attlist
%%


main: dtd_list_opt {*validator = $1};

dtd_list_opt
: dtd_element dtd_list_opt {$$ = $2; $$->addNode($1);}
| dtd_attlist dtd_list_opt {$$ = $2; $$->addAttribute($1);}
| {$$ = new DTDValidator();} ;

dtd_element
: ELEMENT IDENT cp CLOSE	{/*Moises*/$$ = new DTDNode(); $$->tagName = $2; $$->setRegExpChildNodes(*$3);/*Fin Moises*/}
;
dtd_attlist
: ATTLIST IDENT att_definition_opt CLOSE {
  $$ = new std::pair<std::string, std::list<std::string> >();
  $$->first = $2;
  $$->second = *$3;
  }
;

cp: item card_opt	{$$ = new string(*$1); $$ -> append(*$2);};

item: IDENT {/*Moises*/ $$ = new string("(");$$ -> append($1);$$ -> append(")");/*Fin Moises*/}
| PCDATA {/*Moises*/ $$ = new string("(");$$ -> append("PCDATA");$$ -> append(")");/*Fin Moises*/}
| children {/*Moises*/ $$ = new string(*$1);/*Fin Moises*/};

children: choice_card {/*Moises*/ $$ = new string(*$1);/*Fin Moises*/}
| seq_card	{/*Moises*/ $$ = new string(*$1);/*Fin Moises*/};

choice_card: choice card_opt	{/*Moises*/ $$ = new string(*$1); $$ -> append(*$2);/*Fin Moises*/};

seq_card: seq card_opt	{/*Moises*/ $$ = new string(*$1); $$ -> append(*$2);/*Fin Moises*/};

card_opt: QMARK {/*Moises*/ $$ = new string("?");/*Fin Moises*/}
| PLUS {/*Moises*/ $$ = new string("+");/*Fin Moises*/}
| AST  {/*Moises*/ $$ = new string("*");/*Fin Moises*/}
| /*empty*/ {/*Moises*/ $$ = new string("");/*Fin Moises*/};

choice: OPENPAR choice_list_plus CLOSEPAR   {/*Moises*/$$ = new string("("); $$ -> append(*$2); $$ -> append(")");/*Fin Moises*/};
choice_list_plus: cp PIPE choice_list {/*Moises*/$$ = new string(*$1); $$ -> append("|"); $$ -> append(*$3);/*Fin Moises*/};
choice_list: choice_list PIPE cp {/*Moises*/$$ = new string(*$1); $$ -> append("|"); $$ -> append(*$3);/*Fin Moises*/};
| cp 	{/*Moises*/$$ = new string(*$1)/*Fin Moises*/};

seq: OPENPAR seq_list CLOSEPAR		{/*Moises*/$$ = new string("("); $$ -> append(*$2); $$ -> append(")");/*Fin Moises*/};
seq_list: seq_list COMMA cp {/*Moises*/$$ = new string(*$1);$$ -> append(*$3);/*Fin Moises*/};
| cp		{/*Moises*/$$ = new string(*$1)/*Fin Moises*/};

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

  DTDValidator * v;

  err = dtdparse(&v);
  fclose(f);

  //v->toString();
  
  if (err != 0) printf("Parse ended with %d error(s)\n", err);
    else  printf("Parse ended with success\n");
  
  return err;
}

int yywrap(void)
{
  return 1;
}

void yyerror(DTDValidator ** v, char *msg)
{
  fprintf(stderr, "%s\n", msg);
}
