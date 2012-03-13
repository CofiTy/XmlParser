/* 
 * File:   DTDParser.h
 * Author: jonas
 *
 * Created on 13 mars 2012, 10:04
 */

#ifndef DTDPARSER_H
#define	DTDPARSER_H

#include <list>

#include "DTDNode.h"

class DTDParser {
public:
    DTDParser();
    DTDParser(const DTDParser& orig);
    virtual ~DTDParser();

    bool validate();
private:
    std::list<DTDNode> nodes;
};

#endif	/* DTDPARSER_H */


