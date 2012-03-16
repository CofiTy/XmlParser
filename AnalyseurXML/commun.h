#ifndef COMMUN_H
#define COMMUN_H

using namespace std;
#include "Node.h"
#include "NodeList.h"
#include "Data.h"
#include "DocumentXML.h"
#include <list>
#include <utility>
#include <string>

typedef pair<string,string> Attribut;
typedef list<Attribut> AttList;
typedef pair<string,string> ElementName;

#ifdef DEBUG
#define debug(x) (x)
#else
#define debug(x) ((void) 0)
#endif


#endif
