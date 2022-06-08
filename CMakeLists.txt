cmake_minimum_required(VERSION 3.22)
project(VisualizedBowtie2)

set(CMAKE_CXX_STANDARD 23)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(VisualizedBowtie2 src/main.cpp src/SamEntry.cpp include/SamEntry.h src/SamFileReader.cpp include/SamFileReader.h include/SamFileVisualizer.h src/SamFileVisualizer.cpp include/Helpers.h src/Helpers.cpp src/KeyboardEventHandler.cpp include/KeyboardEventHandler.h src/CigarStringParser.cpp include/CigarStringParser.h)
