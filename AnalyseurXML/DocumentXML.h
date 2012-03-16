#ifndef H_DATA
#define H_DATA

#include <string>

#include "NodeList.h"
#include "../AnalyseurDTD/DTDValidator.h"

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
