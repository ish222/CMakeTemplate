set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../include)

# Include all .cpp files in this directory as sources
file(GLOB SOURCES ${SOURCE_DIR}/*.cpp)

# An example of an external header-only library inclusion
if(NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/external_includes)
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/external_includes)
    execute_process(
        COMMAND git clone --depth 1 "https://github.com/Tencent/rapidjson"
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/external_includes)
endif()
    
add_library(lib ${SOURCES})
set_property(TARGET lib PROPERTY CXX_STANDARD 23)

# Neat trick, system disables compiler warnings by treating the include as a system lib
target_include_directories( lib PUBLIC ${Boost_INCLUDE_DIRS} ${INCLUDE_DIR} )

# Link against boost
foreach(boost_component ${BOOST_COMPONENTS})
target_link_libraries(lib PRIVATE Boost::${boost_component})
endforeach()
target_include_directories(lib SYSTEM PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/external_includes/rapidjson/include/)

# Enable debug compiler flags 
if(CMAKE_BUILD_TYPE MATCHES DEBUG)
    target_compile_options(lib PRIVATE -g -O0)
endif()