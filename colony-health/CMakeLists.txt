cmake_minimum_required(VERSION 3.1)

project(colony)

set(OpenCV_DIR $ENV{OpenCV_DIR})
find_package(OpenCV)

find_package(catkin REQUIRED COMPONENTS
             roscpp
             cv_bridge
             image_transport)

catkin_package()

include_directories(include
                    ${OpenCV_INCLUDE_DIRS}
                    ${catkin_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} "src/main.cpp")
target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES} ${OpenCV_LIBS})
