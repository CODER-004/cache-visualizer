#include "../header/LFUEvictionPolicy.h"


LFUEvictionPolicy::LFUEvictionPolicy() {

    minFrequency = 0;
}


void LFUEvictionPolicy::keyAccessed(
    string key,
    string value
) {

    /*
        Existing key
    */

    if(nodeMap.find(key) != nodeMap.end()) {

        LFUNode* node = nodeMap[key];

        node->value = value;


        int oldFrequency = node->frequency;


        /*
            Remove from old frequency list
        */

        freqMap[oldFrequency].erase(
            positionMap[node]
        );


        /*
            Update minimum frequency
        */

        if(
            freqMap[oldFrequency].empty() &&
            minFrequency == oldFrequency
        ) {

            minFrequency++;
        }


        /*
            Increase frequency
        */

        node->frequency++;


        /*
            Add to new frequency list
        */

        freqMap[node->frequency].push_back(node);


        auto iterator =
            freqMap[node->frequency].end();

        --iterator;


        positionMap[node] = iterator;

        return;
    }


    /*
        New key
    */

    LFUNode* node =
        new LFUNode(key, value);


    nodeMap[key] = node;


    freqMap[1].push_back(node);


    auto iterator =
        freqMap[1].end();

    --iterator;


    positionMap[node] = iterator;


    minFrequency = 1;
}


string LFUEvictionPolicy::evictKey() {

    if(freqMap[minFrequency].empty())
        return "";


    /*
        For the same frequency,
        remove the oldest element.
    */

    LFUNode* node =
        freqMap[minFrequency].front();


    string key = node->key;


    freqMap[minFrequency].pop_front();


    nodeMap.erase(key);

    positionMap.erase(node);


    delete node;


    return key;
}


vector<tuple<string, string, int>>
LFUEvictionPolicy::getState() {

    vector<tuple<string, string, int>> result;


    for(auto& entry : freqMap) {

        int frequency = entry.first;


        for(auto node : entry.second) {

            result.push_back({
                node->key,
                node->value,
                frequency
            });
        }
    }


    return result;
}