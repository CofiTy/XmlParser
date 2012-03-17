#include "../AnalyseurXML/src/commun.h"
#include "../AnalyseurXML/parse/xml.tab.h"
#include "../AnalyseurDTD/src/userClass.h"
#include "../AnalyseurDTD/parse/dtd.tab.h"

int parseXMLFile(char* file);
int parseDTDFile(char* file);

int main(int argc, char **argv)
{

  if(argc == 2)
  {
    parseXMLFile(argv[1]);
  }
  if(argc == 3)
  {
    parseDTDFile(argv[2]);
  }
  return 0;
}
