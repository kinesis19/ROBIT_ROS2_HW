#include "turtlesim_control.hpp"

TurtleSimControl::TurtleSimControl() : Node("turtle_sim_control")
{
    // Publisher 생성 - turtle1/cmd_vel Topic으로 Twist 메시지를 퍼블리싱함
    velocity_publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
    std::cout << "TurtleSimControl Node 초기화" << std::endl;
}
    
void TurtleSimControl::controlLoop()
{
    std::cout << "<조종 모드 시작> - WASD 키를 사용하여 거북이를 제어하자 (종료: Q 입력)" << std::endl;
    char key;
    // rclcpp::ok() -> Node가 정상적으로 실행되고 있으면 true를 반환함
    while (rclcpp::ok())
    {
        std::cin >> key;
        // 입려된 키가 'q' 또는 'Q'라면 조종 모드 종료하기
        if (key == 'q' || key == 'Q')
        {
            RCLCPP_INFO(this->get_logger(), "조종 모드 종료");
            std::cout << "조종 모드 종료" << std::endl;
            break;
        }
        processKeyInput(key);
    }
}

void TurtleSimControl::processKeyInput(char key)
{
    auto twist_msg = geometry_msgs::msg::Twist();

    // 대소문자 관계 없이 이동키 입력 받아 처리함
    switch (key)
    {
    case 'w':
    case 'W':
        twist_msg.linear.x = 1.0;
        twist_msg.angular.z = 0.0;
        break;
    case 's':
    case 'S':
        twist_msg.linear.x = -1.0;
        twist_msg.angular.z = 0.0;
        break;
    case 'a':
    case 'A':
        twist_msg.linear.x = 0.0;
        twist_msg.angular.z = 1.0;
        break;
    case 'd':
    case 'D':
        twist_msg.linear.x = 0.0;
        twist_msg.angular.z = -1.0;
        break;
    default:
        std::cout << "알 수 없는 키 입력: " << key << std::endl;
        return;
    }

    // 메시지 퍼블리시
    velocity_publisher_->publish(twist_msg);
}