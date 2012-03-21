%{

using namespace std;
#include "../src/commun.h"
#include <iostream>
#include <cstring>

//int yywrap(void);
void yyerror(DocumentXML *doc, char *msg);
int yylex(void);

%}

%parse-param {DocumentXML * documentXML}

%union {
   char * s;
   NodeList * nl;
   Data * d;
   list<Node*> * listN;
   DocumentXML * doc;
   map<string,string> * m;
   ElementName * en;  /* le nom d'un element avec son namespace */
}

%token EQ SLASH CLOSE CLOSESPECIAL DOCTYPE
%token <s> ENCODING STRING DATA COMMENT IDENT NSIDENT
%token <en> NSSTART START STARTSPECIAL END NSEND
%type <nl> xml_element start
%type <doc> document
%type <m> attributs_opt
%type <s> declarations_opt declaration
%type <listN> content_opt close_content_and_end empty_or_content

%%

document
 : special_dec_opt declarations_opt xml_element misc_seq_opt {$$ = documentXML; 
                                              $$->setActiveRootNode(*$3); 
                                              if(documentXML->dtdNameIsSet == false)
                                              {
                                                $$->dtd = $2; 
                                                $$->dtdNameIsSet = true;
                                              };} 
 ;
special_dec_opt
 : STARTSPECIAL attributs_sp_opt
 | /*empty*/
 ;
attributs_sp_opt
 : attributs_sp_opt IDENT EQ STRING {
                                      if(strcmp($2,"xml-stylesheet") == 0)
                                      {
                                        if(documentXML->xslNameIsSet == false)
                                        {
                                          documentXML->xsl = $4;
                                          documentXML->xslNameIsSet = true;
                                        }
                                      };}
 | /* empty */
 ;
misc_seq_opt
 : misc_seq_opt comment
 | /*empty*/
 ;
comment
 : COMMENT {cout << "# " << $1 << " #";}
 ;

declarations_opt
 : declaration {$$ = $1;}
 | /*empty*/ {$$ = NULL;}
 ;
 
declaration
 : DOCTYPE IDENT IDENT STRING CLOSE {$$ = $4; cout << "<!Doctype " << $2 << " " << $3 << " " << $4 << ">" << endl;}
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

int parseXMLFile(char * file, DocumentXML * documentXML)
{
  int err;
  
  //yydebug = 1; // pour enlever l'affichage de l'éxécution du parser, commenter cette ligne

  printf("Trying to Parse %s\n", file);
  FILE * f;
  if((f = fopen(file, "r")) == NULL)
  {
    fprintf(stderr, "ERROR: No file named %s\n", file);
  }
  xmlrestart(f);
  err = xmlparse(documentXML);
  fclose(f);
  
  if (err != 0) printf("Parse ended with %d error(s)\n", err);
    else  printf("Parse ended with success\n");
  
  return err;
}

/*int yywrap(void)
{
  return 1;
}*/

void yyerror(DocumentXML * doc, char *msg)
{
  fprintf(stderr, "%s\n", msg);
}

