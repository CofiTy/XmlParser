#ifndef H_DOCUMENT_XML
#define H_DOCUMENT_XML

#include <string>

#include "NodeList.h"
#include "../../AnalyseurDTD/src/DTDValidator.h"

class DocumentXML
{
 public:
  std::string dtd;
  NodeList rootNode;
  DTDValidator validator;

  void parseDTD();
  void validate();
};

#endif
