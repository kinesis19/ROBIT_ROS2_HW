#ifndef TALKER_HPP
#define TALKER_HPP

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int64.hpp"

class Talker : public rclcpp::Node
{
public:
    Talker();
    void publishMessage(const std::string &message); // 메시지 퍼블리쉬
    int getMessageCount(); // 퍼블리쉬된 메시지 카운트 횟수 반환

private:
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_; // 문자열 담당 퍼블리셔
    rclcpp::Publisher<std_msgs::msg::Int64>::SharedPtr count_publisher_; // 카운트 담당 퍼블리셔
    int64_t message_count_ = 0; // 퍼블리시된 메시지 횟수
};

#endif // TALKER_HPP
