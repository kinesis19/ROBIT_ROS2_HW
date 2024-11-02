#ifndef LISTENER_HPP
#define LISTENER_HPP

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int64.hpp"

class Listener : public rclcpp::Node
{
public:
    Listener(); // 생성자
    void setChatterCallback(std::function<void(const std::string &)> callback); // 콜백 설정
private:
    void chatterCallback(const std_msgs::msg::String::SharedPtr msg); // 문자열 콜백 메서드
    void countCallback(const std_msgs::msg::Int64::SharedPtr msg); // 카운트 콜백 메서드

    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_; // 문자열 메시지 구독자
    rclcpp::Subscription<std_msgs::msg::Int64>::SharedPtr count_subscription_; // 카운트 메시지 구독자
    std::function<void(const std::string &)> chatter_callback_; // 콜백 함수
};

#endif // LISTENER_HPP