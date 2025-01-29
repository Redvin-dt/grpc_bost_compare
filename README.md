# grpc_boost_compare

Implement dump user registration server on grpc and boost

## Install prerequisite

- Grpc/Protobuf

    ```sh

    sudo apt-get install build-essential autoconf libtool pkg-config libgflags-dev libgtest-dev clang libc++-dev libssl-dev cmake
    git clone https://github.com/grpc/grpc
    cd grpc
    git checkout origin/v1.67.x
    git submodule update --init --recursive

    #in grpc/third_party/zlib
    mkdir build && cd build
    cmake ..
    make -j 4
    sudo make install

    # in grpc/third_party/cares/cares dir
    mkdir build && cd build
    cmake ..
    make -j 4
    sudo make install

    # in grpc/third_party/protobuf dir
    git submodule update --init --recursive
    mkdir build && cd build
    cmake -Dprotobuf_BUILD_TESTS=OFF ..
    make -j 4
    sudo make install

    # in grpc/root
    mkdir build && cd build
    sudo cmake -DgRPC_INSTALL=ON -DgRPC_ZLIB_PROVIDER=package -DgRPC_CARES_PROVIDER=package -DgRPC_PROTOBUF_PROVIDER=package -DgRPC_SSL_PROVIDER=package ..
    sudo make -j 4
    sudo make install

    ```

- Boost
    ``` 

    sudo apt-get install libboost-all-dev 
    git clone --recursive https://github.com/boostorg/boost.git
    cd boost
    ./bootstrap.sh
    ./b2
    
    ```



## GRPC

- Generate proto
    ```sh
    #in grpc/
    PROTO_SRC_DIR=./protos
    protoc -I $PROTO_SRC_DIR --grpc_out=./protos --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` $PROTO_SRC_DIR/server.proto  ## generate C++ server side code
    protoc -I $PROTO_SRC_DIR --cpp_out=./protos $PROTO_SRC_DIR/server.proto  ## generate C++ client side code
    ```
- Build targets
    ```sh
    mkdir build && cd build
    cmake ..
    cmake --build . --target register_server # build server target
    cmake --build . --target register_client # build client target 
    ```
- Run
    ```sh
    #in grpc/build/bin
    ./register_server # run server
    ./register_client # run client
    ```

## Boost

- Examples from boost founders
    https://www.boost.org/doc/libs/develop/libs/beast/doc/html/beast/examples.html

- Build
    ```sh
    mkdir build && cd build
    cmake ..
    cmake --build . --target rest-server
    ```

- Run
    ```sh
    ./rest-server
    ```

## Repos that i use as examples
- https://github.com/yeti01/rest-server/tree/main
- https://github.com/Peter-Chou/grpc_cpp_hello_world/tree/master/protos