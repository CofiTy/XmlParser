#include <iostream>
#include "../AnalyseurXML/src/DocumentXML.h"
#include "../AnalyseurDTD/src/userClass.h"
#include "../AnalyseurDTD/parse/dtd.tab.h"

using namespace std;

int parseDTDFile(char* file);

int main(int argc, char **argv)
{
  DocumentXML document = DocumentXML("");

  if(argc == 2)
  {
      document = DocumentXML(argv[1]);
      document.parseXML();
      cout << document.XMLRootNode.toString() << endl;
  }
  else if(argc == 3)
  {
    if(strcmp(argv[1], "-d")  == 0 || strcmp(argv[1], "--dtd") == 0)
    {
      document.dtd = argv[2];
      document.parseDTD();
    }
    else if(strcmp(argv[1], "-x") == 0 || strcmp(argv[1], "--xml") == 0)
    {
      document = DocumentXML(argv[2]);
      document.parseXML();
      cout << document.XMLRootNode.toString() << endl;
    }
    else if(strcmp(argv[1], "-a") == 0 || strcmp(argv[1], "--all") == 0)
    {
      document = DocumentXML(argv[2]);
      document.parseXML();
      cout << document.XMLRootNode.toString() << endl;
    }
  }
  else if(argc == 4)
  {
    if(strcmp(argv[1], "-s") == 0 || strcmp(argv[1], "--xsl") == 0)
    {
      document = DocumentXML(argv[2], argv[3]);
      document.parseXML();
      document.parseXSL();
      cout << document.XSLRootNode.toString() << endl;
      document.processXSLT();
    }
  }
  return 1;
}
