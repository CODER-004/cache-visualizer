#pragma once

#include <drogon/HttpController.h>

#include "Cache.h"
#include "EvictionPolicyFactory.h"

using namespace drogon;


class CacheController
    : public drogon::HttpController<CacheController> {

private:

    Storage* storage;

    EvictionPolicy* policy;

    Cache* cache;

    PolicyType currentPolicy;


public:

    CacheController();


    METHOD_LIST_BEGIN

    ADD_METHOD_TO(
        CacheController::put,
        "/cache/put",
        Post
    );


    ADD_METHOD_TO(
        CacheController::get,
        "/cache/get/{key}",
        Get
    );


    ADD_METHOD_TO(
        CacheController::state,
        "/cache/state",
        Get
    );


    ADD_METHOD_TO(
        CacheController::setPolicy,
        "/cache/policy",
        Post
    );


    ADD_METHOD_TO(
        CacheController::reset,
        "/cache/reset",
        Post
    );

    METHOD_LIST_END


    void put(
        const HttpRequestPtr& req,
        std::function<void(const HttpResponsePtr&)>&& callback
    );


    void get(
        const HttpRequestPtr& req,
        std::function<void(const HttpResponsePtr&)>&& callback,
        string key
    );


    void state(
        const HttpRequestPtr& req,
        std::function<void(const HttpResponsePtr&)>&& callback
    );


    void setPolicy(
        const HttpRequestPtr& req,
        std::function<void(const HttpResponsePtr&)>&& callback
    );


    void reset(
        const HttpRequestPtr& req,
        std::function<void(const HttpResponsePtr&)>&& callback
    );
};