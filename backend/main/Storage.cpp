#include "../header/Storage.h"

Storage::Storage(int cap) : capacity(cap) {}

void Storage::add(string key, string value) {
    data[key] = value;
}

void Storage::remove(string key) {

    if(data.find(key) != data.end()) {
        data.erase(key);
    }
}

string Storage::get(string key) {

    if(data.find(key) != data.end()) {
        return data[key];
    }

    return "";
}

bool Storage::contains(string key) {
    return data.find(key) != data.end();
}

bool Storage::isFull() {
    return data.size() >= capacity;
}

int Storage::size() {
    return data.size();
}

int Storage::getCapacity() {
    return capacity;
}