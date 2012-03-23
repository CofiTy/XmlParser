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
  if (xsl == NULL){
    return;
  }

  this->state = "XSL";
  parseXMLFile(xsl, this);
}

list<Node *> * DocumentXML::recursiveTreeSearch(Node *root)
{	
    /* Current Root Converted to NodeList. */
    NodeList *root_cur = NULL;
    
    /* Output List of Nodes. */
    list<Node *> * node_list = new list<Node *>();
    
    /* List of Nodes from Templates. */
    list<Node *>::iterator templateLook;
    
    /* Matching Template Node to Root */
    NodeList *templateMatch = NULL;
    
    /**
     * Test if current Node is Data.
     * Stop if it is.
     */
    if((root_cur = dynamic_cast<NodeList*>(root)) == NULL)
    {
        cout << "Current XML Node is a Data : " << ((Data *)root)->value << endl;
        Data *d = new Data();
        d->value = ((Data *)root)->value;
        node_list->push_back(d);
        return node_list;
    }

    cout << "Current XML Node is a NodeList : " << ((NodeList *)root)->tagName << endl;
    cout << "== Looking for a template in XSL" << endl;
    
    /**
     * Check XSL To Find a Matching Template.
     */
    for (templateLook = (XSLRootNode.childNodeList).begin(); templateLook != (XSLRootNode.childNodeList).end(); templateLook++)
    {
        NodeList *cur = NULL;
        if((cur = dynamic_cast<NodeList *>(*templateLook)) == NULL)
        {
            cout << "## Current XSL Node is a Data : " << ((Data *)(*templateLook))->value << endl;
        }
        else
        {
            /* TODO: Penser à gérer les Slashes!!! avec Strtok */
            cout << "## Current XSL Node : " << cur->tagName  << " - " << cur->attributes["match"] << endl;
            if(cur->nameSpace == "xsl"
                && cur->tagName == "template"
                && cur->attributes["match"] == root_cur->tagName)
            {
                cout << "### Matching Template!" << endl;
                templateMatch = cur;
                break;
            }  
        }
    }
    
    /**
     * If no template found, we look for children.
     */
    if(!templateMatch)
    {
        cout << "### No Matching Template, Nothing to Do Here..." << endl;
        list<Node*>::iterator child;
        for (child = (root_cur->childNodeList).begin() ; child != (root_cur->childNodeList).end(); child++)
        {
            // = recursiveTreeSearch(*child);
        }
    }
    /**
     * If we found a template.
     */
    else
    {
        // Do Something
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
