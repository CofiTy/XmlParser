%{

using namespace std;
#include "commun.h"
#include <iostream>

int yywrap(void);
void yyerror(char *msg);
int yylex(void);

%}

%union {
   char * s;
   NodeList * nl;
   Data * d;
   list<Node*> * listN;
   map<string,string> * m;
   ElementName * en;  /* le nom d'un element avec son namespace */
}

%token EQ SLASH CLOSE CLOSESPECIAL DOCTYPE
%token <s> ENCODING STRING DATA COMMENT IDENT NSIDENT
%token <en> NSSTART START STARTSPECIAL END NSEND
%type <nl> xml_element start document
%type <m> attributs_opt
%type <listN> content_opt close_content_and_end empty_or_content

%%

document
 : declarations_opt xml_element misc_seq_opt {$$ = $2; cout << $$->toString() << endl;} 
 ;
misc_seq_opt
 : misc_seq_opt comment
 | /*empty*/
 ;
comment
 : COMMENT {cout << "# " << $1 << " #";}
 ;

declarations_opt
 : declaration
 | /*empty*/
 ;
 
declaration
 : DOCTYPE IDENT IDENT STRING CLOSE {cout << "<!Doctype " << $2 << " " << $3 << " " << $4 << ">" << endl;}
 ;

xml_element
 : start attributs_opt empty_or_content {$$ = $1; $$->attributes = *$2; $$->childNodeList = *$3;}
 ;
start
 : START		{$$ = new NodeList(); $$->tagName = $1->second; $$->nameSpace = $1->first;}
 | NSSTART	{$$ = new NodeList(); $$->tagName = $1->second; $$->nameSpace = $1->first;}
 ;
empty_or_content
 : SLASH CLOSE {$$ = NULL;}
 | close_content_and_end CLOSE {$$ = $1;}
 ;
close_content_and_end
 : CLOSE	content_opt END {$$ = $2;}
 ;
attributs_opt
 : attributs_opt IDENT EQ STRING {$$ = $1; (*$$)[$2] = $4;}
 | /*empty*/ {$$ = new map<string,string>;}
 ;
content_opt 
 : content_opt DATA    {$$ = $1; Data* temp = new Data; temp->value = string($2); $$->push_back((Node*)temp); free($2);} //TODO: Check cast
 | content_opt comment
 | content_opt xml_element  {$$ = $1; $$->push_back($2);} //TODO: cast?
 | /*empty*/ {$$ = new list<Node*>;}
 ;
%%

void xmlrestart(FILE * );

int main(int argc, char **argv)
{
  int err;

  //yydebug = 1; // pour enlever l'affichage de l'éxécution du parser, commenter cette ligne

  if(argc == 2)
  {
    char * file = argv[1];
    printf("Trying to Parse %s\n", file);
    FILE * f;
    if((f = fopen(file, "r")) == NULL)
    {
      fprintf(stderr, "ERROR: No file named %s\n", file);
    }
    xmlrestart(f);
    err = xmlparse();
    fclose(f);
  
    if (err != 0) printf("Parse ended with %d error(s)\n", err);
  	  else  printf("Parse ended with success\n", err);
  }
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

