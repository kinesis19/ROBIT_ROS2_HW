#ifndef TURTLESIM_CONTROL_HPP
#define TURTLESIM_CONTROL_HPP

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <iostream>

class TurtleSimControl : public rclcpp::Node
{
public:
    TurtleSimControl();
    void controlLoop();

private:
    // 콜백 메서드로 사용자의 키 입력에 따른 행동 제어
    void processKeyInput(char key);

    // 퍼블리셔: 가속도
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr velocity_publisher_;
};

#endif // TURTLESIM_CONTROL_HPP