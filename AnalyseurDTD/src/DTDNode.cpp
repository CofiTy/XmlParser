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

bool DTDNode::validateChildString(const string childString){
  //cout << "Regex text : " << childString << " : " << this->regExpChildNodes << "\n";
  return regex_match(childString, this->regExpChildNodes);
}

void DTDNode::setRegExpChildNodes(string regExpChildNodes){
  this->regExpChildNodes = regex(regExpChildNodes, boost::regex::extended);
}
