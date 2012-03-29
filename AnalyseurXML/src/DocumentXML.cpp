#include <cstring>
#include <iostream>
#include <fstream>

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
bool DocumentXML::parseXML()
{
  //document is set
  if (document == NULL)
    return false;

  this->state = "XML";

  if(parseXMLFile(document, this) != 0)
    return false;

  return true;
}

bool DocumentXML::parseDTD()
{
  if (dtd == NULL)
    return false;

  this->state = "DTD";

  if(parseDTDFile(this, &(this->XMLValidator)) != 0)
    return false;

  return true;
}

bool DocumentXML::parseXSL()
{
  if (xsl == NULL){
    return false;
  }

  this->state = "XSL";

  if(parseXMLFile(xsl, this) != 0)
    return false;

  return true;
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
        
        NodeList *prev = *toInsert;
        *toInsert = n;

        list<Node*>::iterator child;
        for (child = (cur->childNodeList).begin() ; child != (cur->childNodeList).end(); child++)
        {
            NODE_TYPE node_ret = recursiveXSLTreeSearch(*child, toInsert);
            if(node_ret == APPLY_NODE)
                return APPLY_NODE;
            else if(node_ret == DATA_NODE)
                *toInsert = prev;
        }
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
          /*
             cout << "Node : " << root_cur->tagName << endl;
             cout << "XSL : " << cur->attributes["match"] << endl;
          // Penser à vider la liste
          list<string *> list_par;
          while (pch != NULL)
          {
          //string *test = new string(pch);
          string *test = new string(pch);
          cout << "Test : " << *test << endl;
          list_par.push_back(test);

          //if(*test == root_cur->tagName)
          //{
          //    delete test;
          //    found = true;
          //    break;
          //}
          //delete test;

          pch = strtok (NULL, "/");
          } 
          list<string *>::iterator par;
          NodeList *cur_test = root_cur;
          found = true;
          for (par = list_par.begin(); par != list_par.end(); par++)
          {
          cout << "Yahouuu " << **par << " et " << cur_test->tagName << endl;
          if(cur_test == NULL 
          || **par != cur_test->tagName)
          {
          cout << "WHAAAAAAT" << endl;
          found = false;
          break;
          }
          cur_test = cur_test->parent;
          }
          */
          while (pch != NULL)
          {
            string *test = new string(pch);

            if(*test == root_cur->tagName)
            {
              delete test;
              found = true;
              break;
            }
            delete test;

            pch = strtok (NULL, "/");
          } 

        }

        delete cstr;
        if(cur->attributes["match"] == root_cur->tagName 
            || found)
        {
          cout << "### Found a Matching Template! " << cur->attributes["match"] << endl;
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
    cout << "### No Matching Template, Nothing to Do Here..." << endl;
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
    cout << "### Found a template..." << endl;
    /**
     * We test want to add each child of the template.
     */
    list<Node*>::iterator child;
    for (child = (templateMatch->childNodeList).begin(); child != (templateMatch->childNodeList).end(); child++)
    {
      NodeList *prev = toInsert;

      if(toInsert != NULL)
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

  this->state = "ProcessXSLT";

  string currentXMLTag = XMLRootNode.tagName;

  recursiveXMLTreeSearch(&XMLRootNode, NULL);

  cout << "================ Arbre de Fin ==================" << endl;
  cout << outputRootNode.toString() << endl;
  cout << "================================================" << endl;

  ofstream myfile ("XMLOutput.xml"); //TODO: améliorer le nom de ficher
  if (myfile.is_open())
  {
    myfile << outputRootNode.toString();
    myfile.close();
  }
}


bool DocumentXML::parse()
{
  if(parseXML())
  {
    if(parseDTD())
    {
      if(validate())
      {
        cout << "XML Valide par rapport à sa DTD" << endl;
      }else
      {
        cout << "XML Non valide par rapport à sa DTD" << endl;
      }
    }else
    {
      cout << "Pas de DTD déclarée" << endl;
    }
    if(parseXSL())
    {
      processXSLT();
    }else
    {
      cout << "Pas de XSL déclaré" << endl;
    }
  }else
  {
    cout << "Nom de fichier nul" << endl;
  }
  return true;
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

bool DocumentXML::validate()
{
  return validateXML();
}

bool DocumentXML::validateXML(){
  return validateNode(this->XMLRootNode, this->XMLValidator);
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
