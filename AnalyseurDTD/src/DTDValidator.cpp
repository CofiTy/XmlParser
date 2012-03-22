/* 
 * File:   DTDValidator.cpp
 * Author: jonas
 * 
 * Created on 13 mars 2012, 10:04
 */

#include "DTDValidator.h"

DTDValidator::DTDValidator() {
}

DTDValidator::DTDValidator(const DTDValidator& orig) {
}

DTDValidator::~DTDValidator() {
}

bool DTDValidator::validate(NodeList & node){
  bool b = false;

  for(list<DTDNode*>::iterator it = this->nodes.begin(); it != this->nodes.end(); it++){
    if((*it)->tagName == node.tagName){
      b = true;

      //Check la liste des fils
      if(!((*it)->validateChildString(node.getChildNodesString()))){
        cout << "Erreur lors de la validation DTD : Les fils du node " << (*it)->tagName << " ne sont pas valides\n";
        return false;
      }
      //Check la liste des attributs
      list<string> * attr = node.getAttributesList();

      pair<multimap<string,string>::iterator,multimap<string,string>::iterator> ret;
      multimap<string,string>::iterator ita2;

      for(list<string>::iterator ita = attr->begin(); ita != attr->end(); ita++){ //Pour chaque attribut A du node en cours
        ret = attributes.equal_range((*it)->tagName); //On recupere tous les attributs valides du node en cours

        bool b = false;
        for (ita2=ret.first; ita2!=ret.second; ++ita2) { //Et on cherche l'attribut A dans les attributs valides
          if((*ita2).second == *ita){
            b = true;
            break;
          }
        }

        if(!b){//Si on a pas trouvé A dans les attributs possibles du node en cours
          cout << "Erreur lors de la validation DTD : " << *ita << " n'a pas été trouvé\n";
          return false;
        }
      }

      delete attr;
    }
  }

  if(!b){ //Si on a pas trouvé le node
    cout << "Erreur lors de la validation DTD : " << node.tagName << " n'a pas été trouvé\n";
    return false;
  }

  return true;
}

void DTDValidator::addNode(DTDNode* node){
  this->nodes.push_back(node);
}

void DTDValidator::addAttribute(std::string node, std::string attribute){
  this->attributes.insert(std::pair<std::string,std::string>(node, attribute));
}


void DTDValidator::addAttribute(pair<string, list<string> > * attr){
  for(list<string>::iterator it = attr->second.begin(); it != attr->second.end(); it++){
    this->addAttribute(attr->first, *it);
  }
}

void DTDValidator::toString(){
  for(list<DTDNode*>::iterator it = nodes.begin(); it != nodes.end(); it++){
    cout << "<!ELEMENT " << (*it)->tagName << " " << (*it)->regExpChildNodes << " >\n";
  }

  for(multimap<string, string>::iterator it = attributes.begin(); it != attributes.end(); it++){
    cout << "<!ATTLIST " << (*it).first << " " << (*it).second << " >\n";
  }

}





























