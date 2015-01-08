cmake_minimum_required(VERSION 2.8)

SET(CMAKE_CXX_FLAGS "-std=c++0x")

add_executable (examples examples.cpp LargeGapGrayCode.cpp)

find_package(OpenCV QUIET)
if(OpenCV_FOUND)
	add_executable(imagePatterns imagePatterns.cpp LargeGapGrayCode.cpp)
	target_link_libraries(imagePatterns ${OpenCV_LIBS})
endif()

