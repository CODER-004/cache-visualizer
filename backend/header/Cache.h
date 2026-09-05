#pragma once

#include "Storage.h"
#include "EvictionPolicy.h"

#include <string>

using namespace std;


class Cache {

    EvictionPolicy* evictionPolicy;

    Storage* storage;


public:

    Cache(
        EvictionPolicy* policy,
        Storage* storage
    );


    void put(
        string key,
        string value
    );


    string get(
        string key
    );


    bool contains(
        string key
    );


    int size();

    int capacity();
};