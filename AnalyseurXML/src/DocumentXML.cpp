#include "DocumentXML.h"

using namespace std;

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
