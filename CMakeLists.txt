cmake_minimum_required(VERSION 3.15)
project(common_utils)

# enable c++ 11
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# take respectives flags for debug & release process
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-std=c++14 -g -fno-omit-frame-pointer -Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-std=c++14 -g -O2 -Wall")

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif ()

add_executable(common_utils main.cpp)
#target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/include)
#target_link_directories(${PROJECT_NAME} PUBLIC)
#target_link_libraries(${PROJECT_NAME} PUBLIC )

##################################################
# add option
##################################################
option(USE_OPENCV "Use OpenCV" ON)
option(USE_TORCH "Use torch" ON)

##################################################
# find package
##################################################
set(CUDA_TOOLKIT_ROOT_DIR /usr/local/cuda)

##################################################
# opencv
##################################################
if (USE_OPENCV)
#    set(OpenCV_DIR "/home/ww/app/opencv-3.4.5")
    find_package(OpenCV REQUIRED)
    if (OpenCV_FOUND)
        message(STATUS "Found OpenCV ${OpenCV_DIR}")
#        target_compile_definitions(${PROJECT_NAME} PUBLIC -DUSE_OPENCV)
#        target_include_directories(${PROJECT_NAME} PUBLIC ${OpenCV_INCLUDE_DIRS})
#        target_link_libraries(${PROJECT_NAME} PUBLIC ${OpenCV_LIBS})
        set(G_COMPILE_DEFINITIONS ${G_COMPILE_DEFINITIONS} -DUSE_OPENCV)
        set(G_INCLUDE_DIRS ${G_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})
        set(G_LINK_LIBS ${G_LINK_LIBS} ${OpenCV_LIBS})
    endif ()
endif ()

##################################################
# torch
##################################################
#message(${USE_TORCH})
if (USE_TORCH)
    set(Torch_DIR "/home/ww/lib/libtorch-1.5.0/share/cmake/Torch")
    find_package(Torch)
    if (Torch_FOUND)
        message(STATUS "Found Torch ${Torch_DIR}")
#        target_compile_definitions(${PROJECT_NAME} PUBLIC -DUSE_TORCH)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")
#        target_include_directories(${PROJECT_NAME} PUBLIC ${TORCH_INCLUDE_DIRS})
#        target_link_libraries(${PROJECT_NAME} PUBLIC ${TORCH_LIBRARIES})
        set(G_COMPILE_DEFINITIONS ${G_COMPILE_DEFINITIONS} -DUSE_TORCH)
        set(G_INCLUDE_DIRS ${G_INCLUDE_DIRS} ${TORCH_INCLUDE_DIRS})
        set(G_LINK_LIBS ${G_LINK_LIBS} ${TORCH_LIBRARIES})
    endif ()
endif ()

##################################################
# add definitions, include dirs, link libs
##################################################
target_compile_definitions(${PROJECT_NAME} PUBLIC ${G_COMPILE_DEFINITIONS})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/include ${G_INCLUDE_DIRS})
#target_link_directories(${PROJECT_NAME} PUBLIC)
target_link_libraries(${PROJECT_NAME} PUBLIC ${G_LINK_LIBS})

##################################################
# add subdirectory
##################################################
add_subdirectory(test)
add_subdirectory(doc)