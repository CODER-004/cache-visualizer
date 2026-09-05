#include "../header/LRUEvictionPolicy.h"


LRUEvictionPolicy::LRUEvictionPolicy() {

    dll = new DLL();
}


void LRUEvictionPolicy::keyAccessed(string key, string value) {

    if(nodeMap.find(key) != nodeMap.end()) {

        Node* node = nodeMap[key];

        node->value = value;

        dll->detachNode(node);

        dll->addNodeAtEnd(node);
    }

    else {

        Node* node = new Node(key, value);

        nodeMap[key] = node;

        dll->addNodeAtEnd(node);
    }
}


string LRUEvictionPolicy::evictKey() {

    Node* node = dll->getTail();

    if(!node)
        return "";


    string key = node->key;

    dll->detachNode(node);

    nodeMap.erase(key);

    delete node;

    return key;
}


vector<pair<string, string>> LRUEvictionPolicy::getState() {

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