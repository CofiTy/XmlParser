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

bool DTDValidator::validate(){
	
}

void DTDValidator::addNode(DTDNode* node){
	this->nodes.push_back(node);			
}

int main(){

}
