/* 
 * File:   DTDValidator.h
 * Author: jonas
 *
 * Created on 13 mars 2012, 10:04
 */

#ifndef DTDVALIDATOR_H
#define	DTDVALIDATOR_H

#include <list>

#include "DTDNode.h"

class DTDValidator {
public:
    DTDValidator();
    DTDValidator(const DTDValidator& orig);
    virtual ~DTDValidator();

    bool validate();

    void addNode(DTDNode* node);
private:
    std::list<DTDNode*> nodes;
};

#endif	/* DTDVALIDATOR_H */


