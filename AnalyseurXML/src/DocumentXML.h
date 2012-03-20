#ifndef H_DOCUMENT_XML
#define H_DOCUMENT_XML

#include <string>

#include "NodeList.h"
#include "../../AnalyseurDTD/src/DTDValidator.h"
#include "commun.h"

class DocumentXML
{
 public:
  char *dtd, *document, *xsl;
  NodeList XMLRootNode;
  NodeList XSLRootNode;
  NodeList XMLOutputRootNode;
  DTDValidator XMLValidator;
  DTDValidator XSLValidator;

  DocumentXML(char* document, char* xsl = NULL);
  void parseXML();
  void parseDTD();
  void parseXSL();
  bool validate();
  
  void processXSLT();

  bool parse();
  void render();
};

#endif
