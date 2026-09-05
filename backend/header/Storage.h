#pragma once

#include <string>
#include <unordered_map>

using namespace std;

class Storage {

    unordered_map<string, string> data;
    int capacity;

public:

    Storage(int cap);

    void add(string key, string value);

    void remove(string key);

    string get(string key);

    bool contains(string key);

    bool isFull();

    int size();

    int getCapacity();
};