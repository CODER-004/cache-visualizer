#pragma once

#include <string>

using namespace std;

class Node {

public:

    string key;
    string value;

    Node* prev;
    Node* next;

    Node(string k, string v)
        : key(k),
          value(v),
          prev(nullptr),
          next(nullptr) {}
};


class DLL {

    Node* head;
    Node* tail;

public:

    DLL();

    void addNodeAtEnd(Node* node);

    void detachNode(Node* node);

    Node* getHead();

    Node* getTail();
};