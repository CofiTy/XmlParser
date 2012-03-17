#ifndef H_DATA
#define H_DATA

#include "Node.h"

class Data : public Node
{
public:
  std::string value;

  std::string toString();
};

#endif
