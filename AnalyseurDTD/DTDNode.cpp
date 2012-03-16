/* 
 * File:   DTDNode.cpp
 * Author: jonas
 * 
 * Created on 13 mars 2012, 10:04
 */

#include "DTDNode.h"

DTDNode::DTDNode() {
}

DTDNode::DTDNode(const DTDNode& orig) {
}

DTDNode::~DTDNode() {
}

bool DTDNode::validateChildString(std::string childString){
	//return regex_match(childString, this->regExpChildNodes);
	return true;
}


void DTDNode::setRegExpChildNodes(std::string regExpChildNodes){
	//this->regExpChildNodes(regExpChildNodes, boost::regex::basic);
}
