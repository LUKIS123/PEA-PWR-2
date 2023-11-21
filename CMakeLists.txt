cmake_minimum_required(VERSION 3.26)
project(PEA_PWR_2)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -fno-rtti")

set(SOURCE_FILES main.cpp)

add_executable(PEA_PWR_2 main.cpp
        Matrix/ATSPMatrix.cpp
        Matrix/ATSPMatrix.h
        FileUtils/DataFileUtility.cpp
        FileUtils/DataFileUtility.h
        MeasureTime/Timer.cpp
        MeasureTime/Timer.h
        Flow/ActionResult.h
        Flow/AppController.cpp
        Flow/AppController.h
        Flow/ConsoleView.cpp
        Flow/ConsoleView.h
        Flow/LatestAlgorithmRan.h
        Solutions/SimulatedAnnealing.cpp
        Solutions/SimulatedAnnealing.h
        Solutions/Utils/GreedyAlgorithm.cpp
        Solutions/Utils/GreedyAlgorithm.h)
