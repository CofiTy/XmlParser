#include <iostream>
#include "../AnalyseurXML/src/DocumentXML.h"
#include "../AnalyseurDTD/src/userClass.h"
#include "../AnalyseurDTD/parse/dtd.tab.h"

using namespace std;

int parseDTDFile(char* file);

bool validateExt(char* fileName, char* extWanted)
{
  char * all, *file, *ext;
  all = (char*)malloc(strlen(fileName)+1);
  strcpy(all, fileName);

  file = (char *)malloc(strlen(fileName)+1);
  ext = (char *)malloc(strlen(fileName)+1);

  file = strtok(all, ".");
  ext = strtok(NULL, ".");

  if(ext == NULL)
    return false;

  return strcmp(ext, extWanted) == 0;
}

int main(int argc, char **argv)
{
  DocumentXML document = DocumentXML("");

  if(argc == 1)
  {
    cout << "analyse: opérande manquante" << endl;
    cout << "Pour en savoir plus, faites \"analyse --help\"" << endl;  
  }
  else if(argc == 2)
  {
    if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
    {
      cout << "Usage: analyse [OPTION] FILE[...]" << endl; 
      cout << " Analyse et transforme un fichier XML" << endl << endl;
      cout << " Les arguments obligatoires pour les options de formes longues le sont aussi pour les options de formes courtes." << endl;
      cout << "   -x, --xml FILE    parse le fichier xml" << endl;
      cout << "   -d, --dtd FILE    parse le fichier dtd" << endl;
      cout << "   -a, --all FILE   parse le fichier xml, le valide si une dtd est déclarée dans le fichier et le transforme si une xsl est déclarée" << endl;
      cout << "   -s, --xsl FILE1 FILE2   parse FILE1 comme fichier XML et le transforme selon la feuille xsl FILE2" << endl;
      cout << "   -d, --dtd FILE1 FILE2   parse FILE1 comme fichier XML et le valide par rapport à la dtd FILE2" << endl;
      cout << "   -h, --help    affiche cette aide" << endl;
    }
    else
    {
      if(validateExt(argv[1], "xml"))
      {
        document = DocumentXML(argv[1]);
        document.parse();
      }
      else
      {
        cout << "analyse: fichier xml attendu" << endl;
        cout << "Pour en savoir plus, faites \"analyse --help\"" << endl;
      }
    }
  }
  else if(argc == 3)
  {
    if(strcmp(argv[1], "-d")  == 0 || strcmp(argv[1], "--dtd") == 0)
    {
      if(validateExt(argv[2], "dtd"))
      {
        document.dtd = argv[2];
        document.parseDTD();
        document.XMLValidator.toString();
      }
      else
      {
        cout << "analyse: fichier dtd attendu" << endl;
        cout << "Pour en savoir plus, faites \"analyse --help\"" << endl;
      }
    }
    else if(strcmp(argv[1], "-x") == 0 || strcmp(argv[1], "--xml") == 0)
    {
      if(validateExt(argv[2], "xml"))
      {
        document = DocumentXML(argv[2]);
        document.parseXML();
        cout << document.XMLRootNode.toString() << endl;
      }
      else
      {
        cout << "analyse: fichier xml attendu" << endl;
        cout << "Pour en savoir plus, faites \"analyse --help\"" << endl;
      }
    }
    else if(strcmp(argv[1], "-a") == 0 || strcmp(argv[1], "--all") == 0)
    {
      if(validateExt(argv[2], "xml"))
      {
        document = DocumentXML(argv[2]);
        document.parse();
      }
      else
      {
        cout << "analyse: fichier xml attendu" << endl;
        cout << "Pour en savoir plus, faites \"analyse --help\"" << endl;
      }
    }
    else
    {
      cout << "analyse: option inconnue ou pas mal utilisée" << endl;
      cout << "Pour en savoir plus, faites \"analyse --help\"" << endl;
    }
  }
  else if(argc == 4)
  {
    if(strcmp(argv[1], "-s") == 0 || strcmp(argv[1], "--xsl") == 0)
    {
      if(validateExt(argv[2], "xml") && validateExt(argv[3], "xsl"))
      {
        document = DocumentXML(argv[2], argv[3]);
        if(document.parseXML())
        {
          if(document.parseXSL())
          {
            document.processXSLT();
          }else
          {
            cout << "Pas de XSL déclaré" << endl;
          }
        }else
        {
          cout << "Nom de fichier nul" << endl;
        }
      }
      else
      {
        cout << "analyse: fichiers xml puis xsl attendus" << endl;
        cout << "Pour en savoir plus, faites \"analyse --help\"" << endl;
      }
    }
    else if(strcmp(argv[1], "-d")  == 0 || strcmp(argv[1], "--dtd") == 0)
    {
      if(validateExt(argv[2], "xml") && validateExt(argv[3], "dtd"))
      {
        document = DocumentXML(argv[2]);
        if(document.parseXML())
        {
          document.dtd = argv[3];
          if(document.parseDTD())
          {
            if(document.validate())
            {
              cout << "XML Valide par rapport à sa DTD" << endl;
            }else
            {
              cout << "XML Non valide par rapport à sa DTD" << endl;
            }
          }else
          {
            cout << "Pas de DTD déclaré" << endl;
          }
        }else
        {
          cout << "Nom de fichier nul" << endl;
        }
      }
      else
      {
        cout << "analyse: fichier xml puis dtd attendus" << endl;
        cout << "Pour en savoir plus, faites \"analyse --help\"" << endl;
      }
    }
    else
    {
      cout << "analyse: option inconnue ou pas mal utilisée" << endl;
      cout << "Pour en savoir plus, faites \"analyse --help\"" << endl;
    }
  }
  else
  {
    cout << "analyse: trop d'opérandes" << endl;
    cout << "Pour en savoir plus, faites \"analyse --help\"" << endl;
  }
  return 1;
}
