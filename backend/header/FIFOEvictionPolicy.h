#pragma once

#include "EvictionPolicy.h"
#include "DLL.h"

#include <unordered_map>
#include <vector>

using namespace std;


class FIFOEvictionPolicy : public EvictionPolicy {

    DLL* dll;

    unordered_map<string, Node*> nodeMap;


public:

    FIFOEvictionPolicy();

    void keyAccessed(string key, string value) override;

    string evictKey() override;

    vector<pair<string, string>> getState();
};