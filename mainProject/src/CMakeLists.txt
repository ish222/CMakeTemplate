set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/mainProject/include)

# Include all .cpp files in this directory as sources
file(GLOB SOURCES ${SOURCE_DIR}/*.cpp)


# lib to be used by gtest
get_filename_component(MAIN_CPP ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp ABSOLUTE)
list(REMOVE_ITEM SOURCES "${MAIN_CPP}")
add_library(mainProject_lib ${SOURCES})
add_executable(mainProject ${MAIN_CPP})

set_property(TARGET mainProject PROPERTY CXX_STANDARD 23)
set_property(TARGET mainProject_lib PROPERTY CXX_STANDARD 23)

# Link boost required components
target_include_directories( mainProject_lib PUBLIC ${Boost_INCLUDE_DIRS} ${INCLUDE_DIR} )
foreach(boost_component ${BOOST_COMPONENTS})
    target_link_libraries(mainProject_lib PRIVATE Boost::${boost_component})
endforeach()
    
# Lib version for consumers like gtest
target_link_libraries(mainProject_lib PUBLIC proto)
target_link_libraries(mainProject_lib PUBLIC lib)

target_link_libraries(mainProject PUBLIC mainProject_lib)


# Generate a file to contain version details
add_definitions( -DmainProject_VERSION=${CMAKE_PROJECT_VERSION} )
configure_file( version_config.h.in ${CMAKE_BINARY_DIR}/generated/version_config.h )
include_directories( ${CMAKE_BINARY_DIR}/generated/ ${PROTOBUF_INCLUDE_DIR} ) # Make sure it can be included...

if(CMAKE_BUILD_TYPE MATCHES DEBUG)
    target_compile_options(mainProject PRIVATE -g -O0)
endif()