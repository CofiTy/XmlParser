#include <cstring>
#include <iostream>

#include "DocumentXML.h"

using namespace std;


int parseXMLFile(char* file, DocumentXML * doc);
int parseDTDFile(DocumentXML * doc, DTDValidator * XMLValidator);


DocumentXML::DocumentXML(char* document, char* xsl)
{
  this->dtd = NULL;
  this->xsl = NULL;
  this->dtdNameIsSet = false;
  this->xslNameIsSet = false;

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
  if (dtd == NULL)
    return;

  parseDTDFile(this, &(this->XMLValidator));

  this->state = "DTD";

  //TODO supprimer
  //this->XMLValidator.toString();

}

void DocumentXML::parseXSL()
{
  if (xsl == NULL)
    return;

  this->state = "XSL";
  parseXMLFile(xsl, this);
}

<<<<<<< HEAD
void recursiveTreeSearch(NodeList root)
{	
	
	//Looking for a template!
	map<string, string>::iterator templateLook;
	for (templateLook = (XSLRootNode.childNodeList).begin() ; templateLook != (XSLRootNode.childNodeList).end(); templateLook++)
	{
		if(templateLook->nameSpace == "xsl"
		&& templateLook->tagName == "template"
		&& templateLook->attributes["match"] == root.tagName())
		{
			cout << root.tagName() << endl;
			break;
		}
	}
	
	
	list<Node*>::iterator it;
	for (it = (root.childNodeList).begin() ; it != (root.childNodeList).end(); it++)
	{
		recursiveTreeSearch(*it);
	}
}

void DocumentXML::processXSLT()
{
  if (XMLRootNode == NULL
	|| XSLRootNode == NULL)
    return;

	// Useless
  this->state = "ProcessXSLT";
  
  string currentXMLTag = XMLRootNode.tagName;
  string currentXSLNode = XSLRootNode;
  
  recursiveTreeSearch(XMLRootNode);
  
}

=======
>>>>>>> parent of 9f99bf9... First Processor
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

bool DocumentXML::validate()
{
  return validateXML() && validateXSL();
}

bool DocumentXML::validateXML(){
  return validateNode(this->XMLRootNode, this->XMLValidator);
}

bool DocumentXML::validateXSL(){
  //TODO
  //return validateNode(this->XSLRootNode, this->XSLValidator);
  return true;
}

bool DocumentXML::validateNode(NodeList & l, DTDValidator & d){
  bool b = true;
  if(d.validate(l)){
    for(list<Node*>::iterator it = l.childNodeList.begin(); it != l.childNodeList.end(); it++){
      NodeList *nl = dynamic_cast<NodeList*>(*it);
      if(nl != NULL){
        if(!validateNode(*nl, d)){
          b = false;
          break;
        }
      }
    }
  } else {
    b = false;
  }

  return b;
}
