#ifndef H_NODE_L
#define H_NODE_L

#include <map>
#include <list>
#include <string>

#include "Node.h"

class NodeList : public Node
{
public:
  //NodeList(std::string tagName);
  std::string tagName;
  std::string nameSpace;
  std::map<std::string, std::string> attributes;
  std::list<Node*> childNodeList;
  bool isAutoClosing;
 
  std::string getChildNodesString();
  std::list<std::string>* getAttributesList();
  void addAttribute(std::string key, std::string value);
  void appendChild(Node * node);
  void setChildNodeList(std::list<Node*> children);
  std::string toString();
};

#endif
