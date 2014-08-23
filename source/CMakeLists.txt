cmake_minimum_required(VERSION 2.8)

project(benchmark)

set(Boost_USE_STATIC_LIBS ON) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
set(Boost_DEBUG ON)

find_package(Boost COMPONENTS program_options REQUIRED) 

include_directories(${Boost_INCLUDE_DIRS}) 
include_directories(sorting)

set(SOURCE 	main.cpp
			array_prepare.cpp
			benchmark.cpp
			options.cpp
			output.cpp
			statistics.cpp
			test.cpp
			time_helper.cpp)
			
set(LIBS 	sorting ${Boost_LIBRARIES})


add_subdirectory(sorting)
	
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -O0 -ggdb3")

add_executable(benchmark ${SOURCE})

target_link_libraries(benchmark ${LIBS})