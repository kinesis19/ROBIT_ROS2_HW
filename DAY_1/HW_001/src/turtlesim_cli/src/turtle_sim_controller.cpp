// turtle_sim_controller.cpp
#include "turtle_sim_controller.hpp"
#include <iostream>

TurtleSimController::TurtleSimController() : Node("turtle_sim_controller")
{
    /* 배운 내용: ROS2 매크로 중 RCLCPP_INFO가 있음 -> C++의 std::cout으로 이해함
    * 근데, [INFO] 관련 문구가 길게 나타나서 UI상 안 좋게 보임. 그래서 std::cout으로 출력 처리를 진행함
    * 그래도, ROS2 매크로로 어떻게 출력할 수 있는지 알아두면 좋을 듯
    * 구선생님께서 강의하셨던 내용 중에 있었던 것 같기도 함 */
    // RCLCPP_INFO("Hello, World!"); 이것도 되지 않나?
    // RCLCPP_INFO(this->get_logger(), "Mode Select: 1 - Control, 2 - Setting Bg, 3 - Setting shape of Turtle, 4 - Setting Pen size");

    std::cout << "Mode Select: 1 - Control, 2 - Setting Bg, 3 - Setting shape of Turtle, 4 - Setting Pen size" << std::endl;

    int mode;
    std::cin >> mode;

    switch (mode)
    {
    case 1:
        std::cout << "Selected Control Mode" << std::endl;
        break;
    case 2:
        std::cout << "Selected Setting Bg Mode" << std::endl;
        break;
    case 3:
        std::cout << "Selected Setting shape of Turtle Mode" << std::endl;
        break;
    case 4:
        std::cout << "Selected Setting size of Pen Mode" << std::endl;
        break;
    default:
        std::cout << "Invalid mode selection." << std::endl;
    }
}