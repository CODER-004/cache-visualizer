#include "../header/Cache.h"


Cache::Cache(
    EvictionPolicy* policy,
    Storage* storage
)
    : evictionPolicy(policy),
      storage(storage) {}


void Cache::put(
    string key,
    string value
) {

    /*
        Existing key
    */

    if(storage->contains(key)) {

        storage->add(key, value);

        evictionPolicy->keyAccessed(
            key,
            value
        );

        return;
    }


    /*
        Cache is full
    */

    if(storage->isFull()) {

        string keyToEvict =
            evictionPolicy->evictKey();


        storage->remove(
            keyToEvict
        );
    }


    /*
        Add new key
    */

    storage->add(
        key,
        value
    );


    evictionPolicy->keyAccessed(
        key,
        value
    );
}


string Cache::get(string key) {

    string value =
        storage->get(key);


    if(!value.empty()) {

        evictionPolicy->keyAccessed(
            key,
            value
        );
    }


    return value;
}


bool Cache::contains(string key) {

    return storage->contains(key);
}


int Cache::size() {

    return storage->size();
}


int Cache::capacity() {

    return storage->getCapacity();
}