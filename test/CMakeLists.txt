# Pull gtest from github
message(STATUS "Pulling and building googletest v1.14.0 from Github")
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG        v1.14.0
)
FetchContent_MakeAvailable(googletest)

# Include rest of project
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(LIB_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/lib/include)
set(MAINLIB_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/mainProject/include)

# Include all .cpp files in this directory as sources
file(GLOB SOURCES ${SOURCE_DIR}/*.cpp)

add_executable(test ${SOURCES})
set_property(TARGET test PROPERTY CXX_STANDARD 23)
target_link_libraries(test PUBLIC lib)
target_link_libraries(test PUBLIC mainProject_lib)
target_link_libraries(test PUBLIC proto)
target_link_libraries(test PUBLIC gtest gtest_main)  # Link against gtest lib

target_include_directories( test PUBLIC ${Boost_INCLUDE_DIRS} ${MAINLIB_INCLUDE_DIR} )