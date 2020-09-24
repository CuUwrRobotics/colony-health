cmake_minimum_required(VERSION 3.1)

project(colony)

set(OpenCV_DIR $ENV{OpenCV_DIR})
# set(OpenCV_DIR "P:\\Programs\\OpenCV\\opencv\\build\\x64\\vc15\\lib")
# message(${OpenCV_DIR})
find_package(OpenCV)

find_package(catkin REQUIRED COMPONENTS
             roscpp
             # std_msgs
             # message_generation
             cv_bridge
             image_transport)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES camera_controller
# CATKIN_DEPENDS roscpp std_msgs message_runtime cv_bridge image_transport
#  DEPENDS system_lib
)

include_directories(
                    include
                    ${OpenCV_INCLUDE_DIRS}
                    ${catkin_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} "src/main.cpp")

target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES} ${OpenCV_LIBS})
