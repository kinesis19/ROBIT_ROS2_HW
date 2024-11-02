#include "qt_talker_and_listener/listener.hpp"

Listener::Listener() : Node("listener")
{
    // 문자열 메시지 서브스크라이버 초기화
    subscription_ = this->create_subscription<std_msgs::msg::String>("/chatter", 10, std::bind(&Listener::chatterCallback, this, std::placeholders::_1));
    
    // 카운트 메시지 서브스크라이버 초기화
    count_subscription_ = this->create_subscription<std_msgs::msg::Int64>("/chatter_count", 10, std::bind(&Listener::countCallback, this, std::placeholders::_1));
    
    RCLCPP_INFO(this->get_logger(), "Listener Node 초기화 완료");
}

void Listener::setChatterCallback(std::function<void(const std::string &)> callback)
{
    chatter_callback_ = callback;
}

// 서브스크라이브 받아 메시지를 콜백으로 전달함
void Listener::chatterCallback(const std_msgs::msg::String::SharedPtr msg)
{
    chatter_callback_(msg->data);
}

// 서브스크라이브 받아 퍼블리시된 횟수를 출력하는 메서드
void Listener::countCallback(const std_msgs::msg::Int64::SharedPtr msg)
{
    RCLCPP_INFO(this->get_logger(), "퍼블리시된 횟수: %ld", msg->data);
}