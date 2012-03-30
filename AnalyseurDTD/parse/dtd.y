%{
#include <iostream>
#include "../src/userClass.h"
#include "../../AnalyseurXML/src/DocumentXML.h"

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


main: dtd_list_opt {*validator = $1;};

dtd_list_opt
: dtd_element dtd_list_opt {$$ = $2; $$->addNode($1);}
| dtd_attlist dtd_list_opt {$$ = $2; $$->addAttribute($1);}
| {$$ = new DTDValidator();} ;

dtd_element
: ELEMENT IDENT cp CLOSE	{$$ = new DTDNode(); $$->tagName = $2; $$->setRegExpChildNodes(*$3);};

dtd_attlist
: ATTLIST IDENT att_definition_opt CLOSE {
  $$ = new std::pair<std::string, std::list<std::string> >();
  $$->first = $2;
  $$->second = *$3;
  };

cp: item card_opt	{$$ = new string(*$1); $$->append(*$2);};

item: IDENT {$$ = new string("("); $$->append($1); $$->append(" )");}
| PCDATA {$$ = new string("("); $$->append("PCDATA"); $$->append(" )");}
| children {$$ = new string(*$1);};

children: choice_card {$$ = new string(*$1);}
| seq_card	{$$ = new string(*$1);};

choice_card: choice card_opt	{$$ = new string(*$1); $$->append(*$2);};

seq_card: seq card_opt	{$$ = new string(*$1); $$->append(*$2);};

card_opt: QMARK {$$ = new string("?");}
| PLUS {$$ = new string("+");}
| AST  {$$ = new string("*");}
| /*empty*/ {$$ = new string("");};

choice: OPENPAR choice_list_plus CLOSEPAR   {$$ = new string("("); $$->append(*$2); $$->append(")");};
choice_list_plus: cp PIPE choice_list {$$ = new string(*$1); $$->append("|"); $$->append(*$3);};
choice_list: choice_list PIPE cp {$$ = new string(*$1); $$->append("|"); $$->append(*$3);};
| cp 	{$$ = new string(*$1);};

seq: OPENPAR seq_list CLOSEPAR		{$$ = new string("("); $$->append(*$2); $$->append(")");};
seq_list: seq_list COMMA cp {$$ = new string(*$1); $$->append(*$3);};
| cp		{$$ = new string(*$1);};

att_definition_opt
: att_definition_opt attribute {$$->push_back(*$2);}
| /* empty */ {$$ = new std::list<std::string>();}
;

attribute
: IDENT att_type default_declaration {$$ = new string($1);}
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

int parseDTDFile(DocumentXML* doc, DTDValidator * XMLValidator)
{
  int err;
  
  //yydebug = 1; // pour enlever l'affichage de l'éxécution du parser, commenter cette ligne

  printf("Trying to Parse %s\n", doc->dtd);
  FILE * f;
  if((f = fopen(doc->dtd, "r")) == NULL)
  {
    fprintf(stderr, "ERROR: No file named %s\n", doc->dtd);
    exit(-1);
  }
  dtdrestart(f);

  DTDValidator * tmp;

  err = dtdparse(&tmp);
  fclose(f);

  if (err != 0)
  {
    printf("Parse ended with %d error(s)\n", err);
  }
  else  
  {
    *XMLValidator = *tmp;
    printf("Parse ended with success\n");
  }

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
