#ifndef TALKER_HPP
#define TALKER_HPP

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int64.hpp"
#include <iostream>

class Talker : public rclcpp::Node
{
public:
    Talker(); // 생성자

    void run(); // 실행 담당하는 메서드

private:
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;     // 문자열 담당 퍼블리셔
    rclcpp::Publisher<std_msgs::msg::Int64>::SharedPtr count_publisher_; // 카운트 담당 퍼블리셔
    int64_t message_count_; // 퍼블리시된 메시지 횟수
};

#endif // TALKER_HPP