/* 
 * File:   DTDNode.h
 * Author: jonas
 *
 * Created on 13 mars 2012, 10:04
 */

#ifndef DTDNODE_H
#define	DTDNODE_H

#include <string>
#include <list>

class DTDNode {
public:
    DTDNode();
    DTDNode(const DTDNode& orig);
    virtual ~DTDNode();

    std::string tagName;
    std::string regExpChildNodes;
    std::list<std::string> attributes;
private:

};

#endif	/* DTDNODE_H */


