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

NODE_TYPE DocumentXML::recursiveXSLTreeSearch(Node *root, NodeList **toInsert)
{
    
    NodeList *cur;
    if((cur = dynamic_cast<NodeList*>(root)) == NULL)
    {
        //cout << "=== Current XSL Node is a Data: " << ((Data *)root)->value << endl;
        Data *d = new Data();
        d->value = ((Data *)root)->value; 
        (*toInsert)->childNodeList.push_back(d);
        return DATA_NODE;
    }
    else
    {
        //cout << "=== Current XSL Node is a NodeList: " << cur->tagName << endl;
        
        if(cur->nameSpace == "xsl"
            && cur->tagName == "apply-templates")
        {
            //cout << "=== Found an Apply-Templates!" << endl;
            //cout << "=== ParentNode : " << (*toInsert)->tagName << endl;
            //cout << "=================" << endl << outputRootNode.toString() << endl << "=================" << endl;
            return APPLY_NODE;
        }
        
        NodeList *n;
        if(*toInsert == NULL)
            n = &outputRootNode;
        else
            n = new NodeList();
        
        n->tagName = cur->tagName;
        n->nameSpace = cur->nameSpace;
        n->attributes = cur->attributes;
        n->isAutoClosing = cur->isAutoClosing;
        
        if(*toInsert != NULL)
        {
            //cout << "=== Inserting Node " << n->tagName << endl;
            //cout << "=== ParentNode : " << (*toInsert)->tagName << endl;
            //cout << "=================" << endl << (*toInsert)->toString() << endl << "=================" << endl;
            (*toInsert)->childNodeList.push_back(n);
        }
        
        *toInsert = n;

        list<Node*>::iterator child;
        for (child = (cur->childNodeList).begin() ; child != (cur->childNodeList).end(); child++)
        {
            if(recursiveXSLTreeSearch(*child, toInsert) == APPLY_NODE)
                return APPLY_NODE;
        }
    }
    
    return END_NODE;
}

void DocumentXML::recursiveXMLTreeSearch(Node *root, NodeList *toInsert)
{	
    /* Current Root Converted to NodeList. */
    NodeList *root_cur = NULL;
    
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
        //cout << "### Current XML Node is a Data : " << ((Data *)root)->value << endl;
        Data *d = new Data();
        d->value = ((Data *)root)->value;
        //cout << "### Parent Node : " << toInsert->tagName << endl;
        toInsert->childNodeList.push_back(d);
        return;
    }

    //cout << "### Current XML Node is a NodeList : " << ((NodeList *)root)->tagName << endl;
    //cout << "### Looking for a template in XSL" << endl;
    
    /**
     * Check XSL To Find a Matching Template.
     */
    for (templateLook = (XSLRootNode.childNodeList).begin(); templateLook != (XSLRootNode.childNodeList).end(); templateLook++)
    {
        NodeList *cur = NULL;
        if((cur = dynamic_cast<NodeList *>(*templateLook)) == NULL)
        {
            //cout << "### Current XSL Node is a Data (Not Supposed to Happen): " << ((Data *)(*templateLook))->value << endl;
        }
        else
        {
            /* TODO: Penser à gérer les Slashes!!! avec Strtok */
            //cout << "### Current XSL TestNode : " << cur->tagName  << " | " << cur->attributes["match"] << endl;
            if(cur->nameSpace == "xsl"
                && cur->tagName == "template")
            {
                bool found = false;
                char *cstr = new char [cur->attributes["match"].size()+1];
                strcpy(cstr, cur->attributes["match"].c_str());
                char *pch = strtok (cstr, "/");
                
                if(pch == NULL && XMLRootNode.tagName == root_cur->tagName)
                    found = true;
                else
                {
                    while (pch != NULL)
                    {
                        string *test = new string(pch);
                        if(*test == root_cur->tagName)
                        {
                            delete test;
                            found = true;
                            break;
                        }
                        pch = strtok (NULL, "/");
                    }
                }

                delete cstr;
                if(cur->attributes["match"] == root_cur->tagName 
                    || found)
                {
                    //cout << "### Found a Matching Template!" << endl;
                    templateMatch = cur;
                    break;
                }
            }  
        }
    }
    
    /**
     * If no template found, we look for children.
     */
    if(!templateMatch)
    {
        //cout << "### No Matching Template, Nothing to Do Here..." << endl;
        list<Node*>::iterator child;
        for (child = (root_cur->childNodeList).begin(); child != (root_cur->childNodeList).end(); child++)
        {
            recursiveXMLTreeSearch(*child, toInsert);
        }
    }
    /**
     * If we found a template.
     */
    else
    {
        /**
         * We test want to add each child of the template.
         */
        list<Node*>::iterator child;
        for (child = (templateMatch->childNodeList).begin(); child != (templateMatch->childNodeList).end(); child++)
        {
            NodeList *prev = toInsert;
            /**
             * Adding child, if we find an "apply-templates" node, we go recursive.
             */
            if(recursiveXSLTreeSearch(*child, &toInsert) == APPLY_NODE)
            {
                list<Node*>::iterator child_bis;
                for (child_bis = (root_cur->childNodeList).begin() ; child_bis != (root_cur->childNodeList).end(); child_bis++)
                {
                    recursiveXMLTreeSearch(*child_bis, toInsert);
                }
                toInsert = prev;
            }
        }
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
  
  recursiveXMLTreeSearch(&XMLRootNode, NULL);
  
  //cout << "================ Arbre de Fin ==================" << endl;
  //cout << outputRootNode.toString() << endl;
  //cout << "================================================" << endl;
  
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
