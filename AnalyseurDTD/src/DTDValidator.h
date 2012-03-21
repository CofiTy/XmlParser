/* 
 * File:   DTDValidator.h
 * Author: jonas
 *
 * Created on 13 mars 2012, 10:04
 */

#ifndef DTDVALIDATOR_H
#define	DTDVALIDATOR_H

#include <list>
#include <string>
#include <map>
#include <iostream>

#include "DTDNode.h"
#include "../../AnalyseurXML/src/NodeList.h"

using namespace std;

class DTDValidator {
public:
    DTDValidator();
    DTDValidator(const DTDValidator& orig);
    virtual ~DTDValidator();

    bool validate(NodeList & node);
    
    void addNode(DTDNode* node);
    
    void addAttribute(string node, string attribute);
    void addAttribute(pair<string, list<string> > * attr);

    void toString();

private:
    list<DTDNode*> nodes;
    multimap<string, string> attributes;

};

#endif	/* DTDVALIDATOR_H */


