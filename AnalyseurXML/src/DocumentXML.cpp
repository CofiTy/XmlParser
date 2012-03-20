#include "DocumentXML.h"
#include "commun.h"
#include "../parse/xml.tab.h"

using namespace std;

int parseXMLFile(char* file);

DocumentXML::DocumentXML(string document)
{
  this->document = document;
}

//this should set dtd and xsl
void DocumentXML::parseXML()
{
  //document is set
  if (document == "")
    return;

  parseXMLFile(document, this);

}

void DocumentXML::parseDTD()
{
  if (dtd == "")
    return;
}

void DocumentXML::parseXSL()
{
  if (xsl == "")
    return;
}

bool DocumentXML::validate()
{
  //TODO 
  return false;
}

bool DocumentXML::parse()
{
  parseXML();
  parseDTD();
  parseXSL();

  return validate();
}

void DocumentXML::render()
{

}
