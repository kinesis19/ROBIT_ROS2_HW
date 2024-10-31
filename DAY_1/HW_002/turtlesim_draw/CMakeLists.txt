cmake_minimum_required(VERSION 3.8)
project(turtlesim_draw)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Setting Standard C++ (New)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find ROS2 and need package
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(turtlesim REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_srvs REQUIRED)


# Add include directory (New)
include_directories(
  include
  ${rclcpp_INCLUDE_DIRS}
  ${turtlesim_INCLUDE_DIRS} 
)

# Add executable file (Update)
add_executable(turtlesim_draw 
  src/main.cpp
  src/turtlesim_draw.cpp
  src/turtlesim_style_pen.cpp
  src/turtlesim_draw_shape.cpp
  src/turtlesim_style_length.cpp
)

# Add ament dependency
ament_target_dependencies(turtlesim_draw 
  rclcpp
  turtlesim
  geometry_msgs
  std_srvs
)

# Setting Install target
install(TARGETS
  turtlesim_draw
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
