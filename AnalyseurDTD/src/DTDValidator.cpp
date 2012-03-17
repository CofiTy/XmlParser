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
	for(list<DTDNode*>::iterator it = this->nodes.begin(); it != this->nodes.end(); it++){
		if((*it)->tagName == node.tagName){
			//Check la liste des fils
			if(!((*it)->validateChildString(node.getChildNodesString()))){
				return false;
			}
			
			//Check la liste des attributs
			list<string> attr = node.getAttributesList();
			
			pair<multimap<string,string>::iterator,multimap<string,string>::iterator> ret;
			multimap<string,string>::iterator ita2;
			
			for(list<string>::iterator ita = attr.begin(); ita != attr.end(); ita++){ //Pour chaque attribut A du node en cours
				ret = attributes.equal_range((*it)->tagName); //On recupere tous les attributs valides du node en cours
				
				bool b = false;
				for (ita2=ret.first; ita2!=ret.second; ++ita2) { //Et on cherche l'attribut A dans les attributs valides
					if((*ita2).second == *ita){
						b = true;
						break;
					}
				}
				
				if(!b){//Si on a pas trouvé A dans les attributs possibles du node en cours
					return false;
				}
			}
		}
	}
	
	return true;
}

void DTDValidator::addNode(DTDNode* node){
	this->nodes.push_back(node);
}

void DTDValidator::addAttribute(std::string node, std::string attribute){
	this->attributes.insert(std::pair<std::string,std::string>(node, attribute));
}

