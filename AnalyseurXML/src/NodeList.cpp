#include "NodeList.h"

#include <iostream>
#include <sstream> 

#include "Data.h"

using namespace std;

string NodeList::getChildNodesString()
{
  stringstream out;

  //print all child nodes
  list<Node*>::iterator childIt = childNodeList.begin();
  for(;childIt != childNodeList.end(); childIt++){
    if (dynamic_cast<NodeList*>(*childIt) != NULL){
      out << dynamic_cast<NodeList*>(*childIt)->tagName << " ";
    }else if (dynamic_cast<Data*>(*childIt) != NULL){
      out << "PCDATA ";
    }else {
      cout << "Unknown type " << (*childIt);
    }
  }

  return out.str();
}

list<string>* NodeList::getAttributesList()
{
  list<string>* attList = new list<string>();

  map<string, string>::iterator attIt = attributes.begin();
  for(;attIt != attributes.end(); attIt++){
    attList->push_back(attIt->first);
  }

  return attList;
}

void NodeList::addAttribute(string key, string value)
{
  attributes[key] = value;
}

void NodeList::appendChild(Node*  node)
{
  node->parent = this;
  childNodeList.push_back(node);
}

void NodeList::setChildNodeList(list<Node*> children)
{
  //appedn and set parent on all all child nodes
  list<Node*>::iterator childIt = children.begin();
  for(;childIt != children.end(); childIt++){
    this->appendChild(dynamic_cast<Node*>(*childIt));
  } 
}

string NodeList::toString()
{
  stringstream out;
  //Start 
  out << "<";
  
  if(nameSpace != "")
  {
    out << nameSpace << ":";
  }

  out << tagName;
  
  //print all node attributes
  map<string, string>::iterator attIt = attributes.begin();
  for(;attIt != attributes.end(); attIt++){
    out << " " << attIt->first << "=" << attIt->second;
  }
  if(isAutoClosing == false)
  {
    //close opening 
    out << ">";

    //print all child nodes
    list<Node*>::iterator childIt = childNodeList.begin();
    for(;childIt != childNodeList.end(); childIt++){
      out << "\n" << (*childIt)->toString();
    }
  
    out << "\n</";

    if(nameSpace != "")
    {
      out << nameSpace << ":";
    }
    
    //Close
    out << tagName << ">";
  }
  else
  {
    out << "/>";
  }
  return out.str();
}

