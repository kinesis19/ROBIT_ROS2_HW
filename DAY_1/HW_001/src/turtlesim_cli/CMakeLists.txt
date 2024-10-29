# 과제의 상위 조건 중 하나가 .hpp와 .cpp 분리임
# .hpp와 .cpp 분리에 대해서는 로빛 패키지 중에 "Ground-Segmentation-Benchmark" 를 참고해서 작성함
# https://github.com/Team-ROBIT/Ground-Segmentation-Benchmark/blob/main/CMakeLists.txt
# 추가한 부분은 C++ 표준 버전 지정과 include_directories이고, add_executable()에 분리한 코드를 할당함
# Qt에서 사용한 CMakeLists.txt와 비슷하게 느껴졌으며, .hpp파일과 .cpp 파일을 분리하기 위한 CMakeLists 코드를 작성하기 위해 두 시간 정도 걸린 듯 -> 레퍼런스인 "Ground-Segmentation-Benchmark"를 보기 전까지는 너무 어렵게 느껴졌음
# Qt에서 .h파일과 .cpp 파일을 추가한 것처럼 ROS2 워크스페이스에서도 똑같이 추가해 나아가면 될 듯
# 자동으로 생성되는 CMakeLists.txt의 불필요한 주석도 제거함

cmake_minimum_required(VERSION 3.8)
project(turtlesim_cli)

# Setting Compile Option
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

# Add include directory (New)
include_directories(
  include
)

# Add executable file (Update)
add_executable(turtlesim_cli 
  src/main.cpp 
  src/turtle_sim_controller.cpp
)

# Add ament dependency
ament_target_dependencies(turtlesim_cli rclcpp)

# Setting Install target
install(TARGETS
  turtlesim_cli
  DESTINATION lib/${PROJECT_NAME}
)

# 테스트 관련 설정 (Optional)
# Setting About test
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
