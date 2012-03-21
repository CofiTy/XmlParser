#include <cstring>
#include <iostream>

#include "DocumentXML.h"

using namespace std;


int parseXMLFile(char* file, DocumentXML * doc);
int parseDTDFile(DocumentXML * doc, DTDValidator * XMLValidator);


DocumentXML::DocumentXML(char* document, char* xsl)
{
  dtd = NULL;
  dtdNameIsSet = false;

  this->document = (char*)malloc(strlen(document)+1);
  strcpy(this->document, document);

  if (xsl != NULL){
    this->xsl = (char*)malloc(strlen(xsl)+1);
    strcpy(this->xsl, xsl);
  }
}

//this should set dtd and xsl
void DocumentXML::parseXML()
{
  //document is set
  if (document == NULL)
    return;

  this->state = "XML";
  parseXMLFile(document, this);
}

void DocumentXML::parseDTD()
{
  //TODO supprimer
  dtd = "AnalyseurDTD/rap3.dtd";

  if (dtd == NULL)
    return;

  parseDTDFile(this, &(this->XMLValidator));

  this->state = "DTD";

  //TODO supprimer
  this->XMLValidator.toString();

  //TODO supprimer
  cout << "C'est bon ? : " << ((this->XMLValidator.validate(this->XMLRootNode)) == true?"OUI":"NON") << "\n";

}

void DocumentXML::parseXSL()
{
  if (xsl == NULL)
    return;

  this->state = "XSL";
  parseXMLFile(xsl, this);
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

void DocumentXML::setActiveRootNode(NodeList node)
{
    if(state == "XML")
    {
      XMLRootNode = node;
    }
    else if(state == "XSL")
    {
      XSLRootNode = node;
    }
    else
    {
      cout << "Unknown state" << endl;
    }
}

void DocumentXML::render()
{
  
}
