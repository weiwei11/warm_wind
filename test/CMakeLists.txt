#################################################
# unit test
#################################################
set(UNIT_TEST unit_tests)
# enable CTest testing
enable_testing()

## enable c++ 11
#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD_REQUIRED True)
#
## take respectives flags for debug & release process
#set(CMAKE_CXX_FLAGS_DEBUG_INIT "-std=c++11 -g -fno-omit-frame-pointer -Wall")
#set(CMAKE_CXX_FLAGS_RELEASE_INIT "-std=c++11 -g -O2 -Wall")

aux_source_directory(. TEST_SRCS)

# Add a testing executable
add_executable(${UNIT_TEST} ${TEST_SRCS})
set_property(TARGET ${UNIT_TEST} PROPERTY CXX_STANDARD 14)

# Add google test lib
# set(GTest_DIR /home/ww/app/googletest-release-1.10.0/)
target_include_directories(${UNIT_TEST} PUBLIC
        ../include
#     ${GTest_DIR}/googletest/include
)
# target_link_directories(${UNIT_TEST} PUBLIC
#     ${GTest_DIR}/lib
# )
target_link_libraries(${UNIT_TEST} PUBLIC
#        ${LIB_NAME}
        gtest
        gtest_main
)

add_test(NAME ${UNIT_TEST} COMMAND ${UNIT_TEST})
add_custom_target(runtest COMMAND ${UNIT_TEST})

##################################################
# find package
##################################################
#set(CUDA_TOOLKIT_ROOT_DIR /usr/local/cuda)

###################################################
## opencv
###################################################
#if (USE_OPENCV)
#    set(OpenCV_DIR "/home/ww/app/opencv-3.4.5")
#    find_package(OpenCV REQUIRED)
#    if (OpenCV_FOUND)
#        message(STATUS "Found OpenCV ${OpenCV_DIR}")
#        target_compile_definitions(${UNIT_TEST} PUBLIC -DUSE_OPENCV)
#        target_include_directories(${UNIT_TEST} PUBLIC ${OpenCV_INCLUDE_DIRS})
#        target_link_libraries(${UNIT_TEST} PUBLIC ${OpenCV_LIBS})
#    endif ()
#endif ()
#
###################################################
## torch
###################################################
#message(${USE_TORCH})
#if (USE_TORCH)
#    set(Torch_DIR "/home/ww/lib/libtorch-1.5.0/share/cmake/Torch")
#    find_package(Torch)
#    if (Torch_FOUND)
#        message(STATUS "Found Torch ${Torch_DIR}")
#        target_compile_definitions(${UNIT_TEST} PUBLIC USE_TORCH)
#        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")
#        target_include_directories(${UNIT_TEST} PUBLIC ${TORCH_INCLUDE_DIRS})
#        target_link_libraries(${UNIT_TEST} PUBLIC ${TORCH_LIBRARIES})
#    endif ()
#endif ()

#message(${TORCH_LIBRARIES})
#message(${TORCH_INCLUDE_DIRS})

##################################################
# add definitions, include dirs, link libs
##################################################
target_compile_definitions(${UNIT_TEST} PUBLIC ${G_COMPILE_DEFINITIONS})
target_include_directories(${UNIT_TEST} PUBLIC ${G_INCLUDE_DIRS})
#target_link_directories(${PROJECT_NAME} PUBLIC)
target_link_libraries(${UNIT_TEST} PUBLIC ${G_LINK_LIBS})