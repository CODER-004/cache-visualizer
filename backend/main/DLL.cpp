#include "../header/DLL.h"

DLL::DLL() : head(nullptr), tail(nullptr) {}


void DLL::addNodeAtEnd(Node* node) {

    if(!head) {

        head = tail = node;

        node->prev = nullptr;
        node->next = nullptr;

        return;
    }

    node->prev = tail;
    node->next = nullptr;

    tail->next = node;

    tail = node;
}


void DLL::detachNode(Node* node) {

    if(!node)
        return;


    if(node->prev) {
        node->prev->next = node->next;
    }
    else {
        head = node->next;
    }


    if(node->next) {
        node->next->prev = node->prev;
    }
    else {
        tail = node->prev;
    }


    node->prev = nullptr;
    node->next = nullptr;
}


Node* DLL::getHead() {
    return head;
}


Node* DLL::getTail() {
    return tail;
}