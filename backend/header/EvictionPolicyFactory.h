#pragma once

#include "EvictionPolicy.h"
#include "LRUEvictionPolicy.h"
#include "LFUEvictionPolicy.h"
#include "FIFOEvictionPolicy.h"


enum class PolicyType {

    LRU,

    LFU,

    FIFO
};


class EvictionPolicyFactory {

public:

    static EvictionPolicy*
    createPolicy(PolicyType type) {

        if(type == PolicyType::LRU) {

            return new LRUEvictionPolicy();
        }


        if(type == PolicyType::LFU) {

            return new LFUEvictionPolicy();
        }


        if(type == PolicyType::FIFO) {

            return new FIFOEvictionPolicy();
        }


        return nullptr;
    }
};