# CMake template for a protobuf library
add_library(proto)  # CHANGEME

# An example of a custom command during generation
option(REGENERATE_PROTOS "Regenerate all protos from script" OFF)
if (REGENERATE_PROTOS)
    set(GENERATE_CMD "${CMAKE_CURRENT_SOURCE_DIR}/generate.sh")
    message(STATUS "Running command ${GENERATE_CMD}")
    execute_process(
        COMMAND ${GENERATE_CMD}
        COMMAND_ECHO STDOUT    
    )
endif()

# Globs all .proto files in current directory
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB SOURCES ${SOURCE_DIR}/*.proto)

# Protobuf generated files will be in build directory, so that must be included
target_include_directories(proto
    PUBLIC
    .
    ${CMAKE_CURRENT_BINARY_DIR}
    ${Protobuf_INCLUDE_DIRS}
)

# Looks for installed protobuf package
find_package(Protobuf REQUIRED)
set(PROTO_SOURCES ${SOURCES} )

# Link the generated files into this proto lib so they can be included and used
target_link_libraries(proto PUBLIC ${Protobuf_LIBRARIES})
target_link_libraries(proto PUBLIC protobuf::libprotobuf)
# target_link_libraries(proto PUBLIC grpc++)  # If grpc is enabled
target_compile_options(proto PRIVATE -Wno-misleading-indentation)

# Runs protoc compiler on .proto files to generate C++ code
protobuf_generate(LANGUAGE cpp TARGET proto PROTOS ${PROTO_SOURCES} )
target_sources(proto
    PRIVATE
    ${LIB_HEADERS}
    ${LIB_SOURCES}
)