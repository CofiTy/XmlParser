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

class DTDNode {
public:
    DTDNode();
    DTDNode(const DTDNode& orig);
    virtual ~DTDNode();

    std::string tagName;
    std::list<std::string> attributes;
    
    bool validateChildString(std::string childString);
    void setRegExpChildNodes(std::string regExpChildNodes);
private:

    //boost::regex regExpChildNodes;

};

#endif	/* DTDNODE_H */


