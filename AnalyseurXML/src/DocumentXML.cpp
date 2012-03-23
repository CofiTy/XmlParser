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

void DocumentXML::recursiveTreeSearch(Node *root)
{	
    NodeList *root_cur = NULL;
    if((root_cur = dynamic_cast<NodeList*>(root)) == NULL)
    {
        cout << "Root is not a nodelist" << endl;
    }

	//Looking for a template!
	list<Node *>::iterator templateLook;
	for (templateLook = (XSLRootNode.childNodeList).begin() ; templateLook != (XSLRootNode.childNodeList).end(); templateLook++)
	{
        NodeList *cur = NULL;
        if((cur = dynamic_cast<NodeList *>(*templateLook)) == NULL)
        {
            cout << "Node is not a nodelist..." << endl;
        }
		if(cur->nameSpace == "xsl"
		&& cur->tagName == "template"
		&& cur->attributes["match"] == root_cur->tagName)
		{
			cout << root_cur->tagName << endl;
			break;
		}
	}
	
	list<Node*>::iterator it;
	for (it = (root_cur->childNodeList).begin() ; it != (root_cur->childNodeList).end(); it++)
	{
		recursiveTreeSearch(*it);
	}
}

void DocumentXML::processXSLT()
{
  /*  
  if (XMLRootNode == NULL
	|| XSLRootNode == NULL)
    return;
*/
	// Useless
  this->state = "ProcessXSLT";
  
  string currentXMLTag = XMLRootNode.tagName;
  
  recursiveTreeSearch(&XMLRootNode);
  
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
