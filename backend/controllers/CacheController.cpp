#include "CacheController.h"

CacheController::CacheController() {

    storage = new Storage(5);

    currentPolicy = PolicyType::LRU;

    policy =
        EvictionPolicyFactory::createPolicy(
            currentPolicy
        );


    cache =
        new Cache(
            policy,
            storage
        );
}


void CacheController::put(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback
) {

    auto json = req->getJsonObject();


    if(!json ||
       !json->isMember("key") ||
       !json->isMember("value")) {

        Json::Value response;

        response["success"] = false;

        response["message"] =
            "key and value are required";


        auto resp =
            HttpResponse::newHttpJsonResponse(
                response
            );

        resp->setStatusCode(
            k400BadRequest
        );


        callback(resp);

        return;
    }


    string key =
        (*json)["key"].asString();


    string value =
        (*json)["value"].asString();


    bool existed =
        cache->contains(key);


    cache->put(
        key,
        value
    );


    Json::Value response;

    response["success"] = true;

    response["operation"] =
        existed ? "UPDATE" : "PUT";

    response["key"] = key;

    response["value"] = value;


    auto resp =
        HttpResponse::newHttpJsonResponse(
            response
        );


    callback(resp);
}

void CacheController::get(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    string key
) {

    string value =
        cache->get(key);


    Json::Value response;

    response["key"] = key;


    if(value.empty()) {

        response["success"] = false;

        response["hit"] = false;

        response["value"] = "";
    }

    else {

        response["success"] = true;

        response["hit"] = true;

        response["value"] = value;
    }


    auto resp =
        HttpResponse::newHttpJsonResponse(
            response
        );


    callback(resp);
}


void CacheController::state(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback
) {

    Json::Value response;


    if(currentPolicy == PolicyType::LRU) {

        auto* lru =
            dynamic_cast<LRUEvictionPolicy*>(
                policy
            );


        auto items =
            lru->getState();


        response["policy"] = "LRU";


        for(auto& item : items) {

            Json::Value node;

            node["key"] = item.first;

            node["value"] = item.second;


            response["items"].append(
                node
            );
        }
    }


    else if(currentPolicy == PolicyType::FIFO) {

        auto* fifo =
            dynamic_cast<FIFOEvictionPolicy*>(
                policy
            );


        auto items =
            fifo->getState();


        response["policy"] = "FIFO";


        for(auto& item : items) {

            Json::Value node;

            node["key"] = item.first;

            node["value"] = item.second;


            response["items"].append(
                node
            );
        }
    }


    else {

        auto* lfu =
            dynamic_cast<LFUEvictionPolicy*>(
                policy
            );


        auto items =
            lfu->getState();


        response["policy"] = "LFU";


        for(auto& item : items) {

            Json::Value node;

            node["key"] =
                std::get<0>(item);

            node["value"] =
                std::get<1>(item);

            node["frequency"] =
                std::get<2>(item);


            response["items"].append(
                node
            );
        }
    }


    response["size"] =
        cache->size();


    response["capacity"] =
        cache->capacity();


    auto resp =
        HttpResponse::newHttpJsonResponse(
            response
        );


    callback(resp);
}

void CacheController::setPolicy(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback
) {

    auto json =
        req->getJsonObject();


    if(!json ||
       !json->isMember("policy")) {

        Json::Value response;

        response["success"] = false;

        response["message"] =
            "policy is required";


        callback(
            HttpResponse::newHttpJsonResponse(
                response
            )
        );

        return;
    }


    string policyName =
        (*json)["policy"].asString();


    PolicyType newPolicy;


    if(policyName == "LRU") {

        newPolicy = PolicyType::LRU;
    }

    else if(policyName == "LFU") {

        newPolicy = PolicyType::LFU;
    }

    else if(policyName == "FIFO") {

        newPolicy = PolicyType::FIFO;
    }

    else {

        Json::Value response;

        response["success"] = false;

        response["message"] =
            "Invalid policy";


        auto resp =
            HttpResponse::newHttpJsonResponse(
                response
            );

        resp->setStatusCode(
            k400BadRequest
        );


        callback(resp);

        return;
    }


    /*
        For simplicity, changing policy
        starts a fresh cache.
    */

    delete policy;

    delete storage;


    storage =
        new Storage(
            5
        );


    currentPolicy =
        newPolicy;


    policy =
        EvictionPolicyFactory::createPolicy(
            currentPolicy
        );


    delete cache;


    cache =
        new Cache(
            policy,
            storage
        );


    Json::Value response;

    response["success"] = true;

    response["policy"] = policyName;


    callback(
        HttpResponse::newHttpJsonResponse(
            response
        )
    );
}

void CacheController::reset(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback
) {

    delete policy;

    delete storage;

    delete cache;


    storage =
        new Storage(5);


    policy =
        EvictionPolicyFactory::createPolicy(
            currentPolicy
        );


    cache =
        new Cache(
            policy,
            storage
        );


    Json::Value response;

    response["success"] = true;

    response["message"] =
        "Cache reset successfully";


    callback(
        HttpResponse::newHttpJsonResponse(
            response
        )
    );
}