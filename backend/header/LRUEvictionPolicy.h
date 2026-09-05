#pragma once

#include "EvictionPolicy.h"
#include "DLL.h"

#include <unordered_map>
#include <vector>

using namespace std;


class LRUEvictionPolicy : public EvictionPolicy {

    DLL* dll;

    unordered_map<string, Node*> nodeMap;


public:

    LRUEvictionPolicy();

    void keyAccessed(string key, string value) override;

    string evictKey() override;

    vector<pair<string, string>> getState();
};