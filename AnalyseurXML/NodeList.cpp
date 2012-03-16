#include "NodeList.h"

#include <iostream>
#include <sstream> 

using namespace std;

string NodeList::getChildNodesString()
{
  stringstream out;

  //print all child nodes
  list<Node*>::iterator childIt = childNodeList.begin();
  for(;childIt != childNodeList.end(); childIt++){
    out << " " << (*childIt)->tagName;
  }

  return out.str();
}

list<string> NodeList::getAttributesList()
{
  
}

void NodeList::addAttribute(string key, string value)
{
  attributes[key] = value;
}

void NodeList::appendChild(Node*  node)
{
  childNodeList.push_back(node);
}

string NodeList::toString()
{
  stringstream out;
  //Start 
  out << "<" << tagName;

  //print all node attributes
  map<string, string>::iterator attIt = attributes.begin();
  for(;attIt != attributes.end(); attIt++){
    out << " " << attIt->first << "=" << attIt->second;
  }
  //close opening 
  out << ">";

  //print all child nodes
  list<Node*>::iterator childIt = childNodeList.begin();
  for(;childIt != childNodeList.end(); childIt++){
    out << (*childIt)->toString();
  }
  
  //Close
  out << "</" << tagName << ">";

  return out.str();
}
