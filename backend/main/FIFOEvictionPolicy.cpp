#include "../header/FIFOEvictionPolicy.h"


FIFOEvictionPolicy::FIFOEvictionPolicy() {

    dll = new DLL();
}


void FIFOEvictionPolicy::keyAccessed(string key, string value) {

    /*
        If key already exists,
        FIFO does not change its position.
    */

    if(nodeMap.find(key) != nodeMap.end()) {

        nodeMap[key]->value = value;

        return;
    }


    Node* node = new Node(key, value);

    nodeMap[key] = node;

    dll->addNodeAtEnd(node);
}


string FIFOEvictionPolicy::evictKey() {

    /*
        Oldest element is at HEAD.
    */

    Node* node = dll->getHead();

    if(!node)
        return "";


    string key = node->key;

    dll->detachNode(node);

    nodeMap.erase(key);

    delete node;

    return key;
}


vector<pair<string, string>> FIFOEvictionPolicy::getState() {

    vector<pair<string, string>> result;

    Node* current = dll->getHead();

    while(current) {

        result.push_back({
            current->key,
            current->value
        });

        current = current->next;
    }

    return result;
}