#pragma once

#include "EvictionPolicy.h"

#include <unordered_map>
#include <list>
#include <vector>

using namespace std;


class LFUEvictionPolicy : public EvictionPolicy {

    struct LFUNode {

        string key;
        string value;

        int frequency;

        LFUNode(string k, string v)
            : key(k),
              value(v),
              frequency(1) {}
    };


    unordered_map<string, LFUNode*> nodeMap;


    unordered_map<int, list<LFUNode*>> freqMap;


    unordered_map<
        LFUNode*,
        list<LFUNode*>::iterator
    > positionMap;


    int minFrequency;


public:

    LFUEvictionPolicy();

    void keyAccessed(string key, string value) override;

    string evictKey() override;

    vector<tuple<string, string, int>> getState();
};