cmake_minimum_required(VERSION 3.22)

project(rest-server)

set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)

find_package(Boost CONFIG COMPONENTS system json)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(rest-server 
    main.cpp
    ${PROJECT_SOURCE_DIR}/request_handler/authorize_handler.cpp
    ${PROJECT_SOURCE_DIR}/request_handler/register_handler.cpp
    ${PROJECT_SOURCE_DIR}/request_factory/request_factory.cpp
    ${PROJECT_SOURCE_DIR}/exceptions/http_exceptions.cpp
        request_handler/user_data.h
        request_handler/profile_handler.h
        request_handler/profile_handler.cpp
)
target_include_directories(rest-server PUBLIC ${PROJECT_SOURCE_DIR}/request_factory PUBLIC ${PROJECT_SOURCE_DIR}/request_handler PUBLIC ${PROJECT_SOURCE_DIR}/exceptions)

target_link_libraries(rest-server Threads::Threads ${Boost_LIBRARIES})
