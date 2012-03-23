#include <iostream>
#include "../AnalyseurXML/src/DocumentXML.h"
#include "../AnalyseurDTD/src/userClass.h"
#include "../AnalyseurDTD/parse/dtd.tab.h"

using namespace std;

int parseDTDFile(char* file);

int main(int argc, char **argv)
{
    cout << "Processing " << argv[1] << " and " << argv[2] << "..." << endl;
    DocumentXML document = DocumentXML(argv[1], argv[2]);
    cout << "Parsing XML..." << endl;
    document.parseXML();
    cout << document.XMLRootNode.toString() << endl;
    cout << "Parsing XSL..." << endl;
    document.parseXSL();
    cout << document.XMLRootNode.toString() << endl;
    cout << "Doing Things..." << endl;
    document.processXSLT();

  //if(argc == 2)
  //{
    //DocumentXML document = DocumentXML(argv[1]);
    /*document.parseXML();
    document.parseDTD();

    if(document.validate()){
      cout << "XML Validé !!" << endl;
    } else {
      cout << "XML NON Validé !!" << endl;
    }*/
    /*
    if(document.parse()){
      cout << "TOUT OK !!" << endl;
    } else {
      cout << "PAS OK =((  !!" << endl;
    }
    */
    //document.parseXML();
    //cout << document.XMLRootNode.toString() << endl;
    //document.parseXSL();
  //}
  //if(argc == 3)
  //{
    //parseDTDFile(argv[2]);
  //}

  return 0;
}
