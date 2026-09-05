#pragma once

#include <string>

using namespace std;

class EvictionPolicy {

public:
    virtual void keyAccessed(string key, string value) = 0;

    virtual string evictKey() = 0;

    virtual ~EvictionPolicy() {}
};