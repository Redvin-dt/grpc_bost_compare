add_executable(register_server register_server.cpp ${PROTO_GENERATED_FILES_DIR}/server.pb.cc ${PROTO_GENERATED_FILES_DIR}/server.grpc.pb.cc)
target_link_libraries(register_server
    ${_GRPC_GRPCPP_UNSECURE}
    ${_PROTOBUF_LIBPROTOBUF})

add_executable(register_client register_client.cpp ${PROTO_GENERATED_FILES_DIR}/server.pb.cc ${PROTO_GENERATED_FILES_DIR}/server.grpc.pb.cc)
target_link_libraries(register_client
    ${_GRPC_GRPCPP_UNSECURE}
    ${_PROTOBUF_LIBPROTOBUF})
