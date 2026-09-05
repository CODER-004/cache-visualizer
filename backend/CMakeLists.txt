cmake_minimum_required(VERSION 3.10)

project(CacheVisualizer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Drogon CONFIG REQUIRED)


add_executable(
    cache_server

    main/main.cpp

    main/Cache.cpp
    main/Storage.cpp
    main/DLL.cpp

    main/LRUEvictionPolicy.cpp
    main/LFUEvictionPolicy.cpp
    main/FIFOEvictionPolicy.cpp

    controllers/CacheController.cpp
)


target_include_directories(
    cache_server
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/header
)


target_link_libraries(
    cache_server
    PRIVATE
    Drogon::Drogon
)