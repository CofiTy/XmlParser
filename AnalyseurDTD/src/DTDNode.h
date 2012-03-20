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

using namespace std;
using namespace boost;

class DTDNode {
public:
    DTDNode();
    DTDNode(const DTDNode& orig);
    virtual ~DTDNode();

    string tagName;
    list<string> attributes;
    
    bool validateChildString(const string childString);
    void setRegExpChildNodes(const string regExpChildNodes);
private:

    regex regExpChildNodes;

};

#endif	/* DTDNODE_H */
