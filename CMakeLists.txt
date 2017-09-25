CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#binary name
project(cpp_draughts)


#grab every h and cpp file located in source folder
FILE(GLOB ALL_FILES "*.h" "*.cpp")

#force compiler to use c++14 if command line arg doesn't work
SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

#command line args
SET(CMAKE_CXX_FLAGS "-Wall -pedantic -std=c++14 -lboost_system")


#nominating directories
SET(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

 #git hellow world
#everything below is related to boost library. 
SET(Boost_USE_STATIC_LIBS       OFF)
SET(Boost_USE_MULTITHREADED     ON)
SET(Boost_USE_STATIC_RUNTIME    OFF)

find_package(Boost 1.36.0 COMPONENTS system program_options)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})

    #this line creates the binary
    add_executable(cpp_data_structures ${ALL_FILES})

    #link the boost libraries to the binary
    target_link_libraries(cpp_draughts ${Boost_LIBRARIES})
    MESSAGE(Boost found\n)
else()
	#don't compile
    MESSAGE(Boost not found\n)
endif()
