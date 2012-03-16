/* 
 * File:   DTDParser.h
 * Author: jonas
 *
 * Created on 13 mars 2012, 10:04
 */

#ifndef DTDVALIDATOR_H
#define	DTDVALIDATOR_H

#include <list>
#include <string>
#include <map>

#include "DTDNode.h"

class DTDValidator {
public:
    DTDValidator();
    DTDValidator(const DTDValidator& orig);
    virtual ~DTDValidator();

    bool validate();
    
    void addNode(DTDNode* node);
    
    void addAttribute(std::string node, std::string attribute);

private:
    std::list<DTDNode*> nodes;
    std::multimap<std::string, std::string> attributes;
};

#endif	/* DTDVALIDATOR_H */


