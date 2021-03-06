#ifndef H_DOCUMENT_XML
#define H_DOCUMENT_XML

#include <string>

#include "NodeList.h"
#include "../../AnalyseurDTD/src/DTDValidator.h"
#include "commun.h"

enum NODE_TYPE {APPLY_NODE, END_NODE, DATA_NODE};

class DocumentXML
{
 public:
  char *dtd, *document, *xsl;
  std::string state;
  bool dtdNameIsSet;
  bool xslNameIsSet;
  NodeList XMLRootNode;
  NodeList XSLRootNode;
  NodeList outputRootNode;
  DTDValidator XMLValidator;

  DocumentXML(char* document, char* xsl = NULL);
  bool parseXML();
  bool parseDTD();
  bool parseXSL();
  bool validate();
  
  void processXSLT();

  void setActiveRootNode(NodeList node);

  bool parse();
  void render();
  
private:
    void recursiveXMLTreeSearch(Node * root, NodeList *toInsert);
    
    NODE_TYPE recursiveXSLTreeSearch(Node *root, NodeList **toInsert);
    bool validateXML();
    bool validateXSL();

    bool validateNode(NodeList & l, DTDValidator & d);
};

#endif
