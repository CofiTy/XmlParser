#include "../AnalyseurXML/src/DocumentXML.h"
#include "../AnalyseurDTD/src/userClass.h"
#include "../AnalyseurDTD/parse/dtd.tab.h"

int parseDTDFile(char* file);

int main(int argc, char **argv)
{

  if(argc == 2)
  {
    DocumentXML document = DocumentXML(argv[1]);
    document.parseXML();
  }
  if(argc == 3)
  {
    parseDTDFile(argv[2]);
  }
  return 0;
}
