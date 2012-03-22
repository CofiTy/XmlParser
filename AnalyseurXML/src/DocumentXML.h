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
  std::string state;
  bool dtdNameIsSet;
  bool xslNameIsSet;
  NodeList XMLRootNode;
  NodeList XSLRootNode;
  NodeList XHTMLRootNode;
  DTDValidator XMLValidator;
  DTDValidator XSLValidator;

  DocumentXML(char* document, char* xsl = NULL);
  void parseXML();
  void parseDTD();
  void parseXSL();
  bool validate();
<<<<<<< HEAD
  
  void processXSLT();
  void setActiveRootNode(NodeList node);
=======
>>>>>>> parent of 9f99bf9... First Processor

  bool parse();
  void render();

private:
  bool validateXML();
  bool validateXSL();

  bool validateNode(NodeList & l, DTDValidator & d);
};

#endif
