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
#include <boost/regex.hpp> 
#include <iostream>

using namespace std;
using namespace boost;

class DTDNode {
public:
    DTDNode();
    DTDNode(const DTDNode& orig);
    virtual ~DTDNode();

    string tagName;

    regex regExpChildNodes;
    
    bool validateChildString(const string childString);
    void setRegExpChildNodes(const string regExpChildNodes);
private:

};

#endif	/* DTDNODE_H */
