cmake_minimum_required(VERSION 3.5)

project(Yolov8CPPInference VERSION 0.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# CUDA
set(CUDA_TOOLKIT_ROOT_DIR "/usr/local/cuda-11.6")

set(CMAKE_CUDA_STANDARD 11)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)
# !CUDA

# OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
# !OpenCV

# CUDA
include_directories(${CUDA_INCLUDE_DIRS})
# !CUDA


set(PROJECT_SOURCES
    main.cpp

    src/inference.h
    src/inference.cpp
    
    src/region_counting.h
    src/region_counting.cpp

    src/channel.h
    src/channel.cpp

)

add_executable(Yolov8CPPInference ${PROJECT_SOURCES})
target_link_libraries(Yolov8CPPInference ${OpenCV_LIBS} ${CUDA_LIBRARIES})
