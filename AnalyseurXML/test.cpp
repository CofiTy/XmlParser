#include <iostream>

#include "src/NodeList.h"
#include "src/Data.h"

using namespace std;

int main(int argc, char ** argv)
{
  NodeList n;
  n.tagName = "node";

  NodeList n2;
  n2.tagName = "child";
  n2.addAttribute("value", "ten");

  Data d;
  d.value = "lol";

  Data d2;
  d2.value = "du texte";

  Data d3; 
  d3.value = "super";

  n.addAttribute("att", "42");
  n.appendChild(&d);
  n.appendChild(&n2);
  n.appendChild(&d3);
  n2.appendChild(&d2);

  cout << n.toString() << endl;

  cout << n.getChildNodesString() << endl;
}
