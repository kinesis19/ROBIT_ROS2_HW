cmake_minimum_required(VERSION 3.8)
project(chatter_cli)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 필요한 패키지 찾기
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

# include directory 추가하기
include_directories(
  include
  ${rclcpp_INCLUDE_DIRS}
)


# executable 파일 추가
add_executable(chatter_cli 
  src/my_cpp_node.cpp
)

# Ament dependency 추가
ament_target_dependencies(chatter_cli 
  rclcpp
)

# Install target 설정
install(TARGETS
  chatter_cli
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
