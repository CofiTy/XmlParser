#ifndef H_NODE
#define H_NODE

#include <string>

class NodeList;

class Node
{
public:
  NodeList* parent;
  virtual std::string toString() = 0;
};

#endif 
