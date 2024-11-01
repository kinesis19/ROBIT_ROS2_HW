#include "chatter_cli/listener.hpp"

Listener::Listener() : Node("listener")
{
    // 문자열 메시지 서브스크라이버 초기화
    subscription_ = this->create_subscription<std_msgs::msg::String>("/chatter_cli", 10, std::bind(&Listener::chatterCallback, this, std::placeholders::_1));
    // 카운트 메시지 서브스크라이버 초기화
    count_subscription_ = this->create_subscription<std_msgs::msg::Int64>("/chatter_count", 10, std::bind(&Listener::countCallback, this, std::placeholders::_1));
    RCLCPP_INFO(this->get_logger(), "Listener Node 초기화 완료");
}


void Listener::chatterCallback(const std_msgs::msg::String::SharedPtr msg)
{
    RCLCPP_INFO(this->get_logger(), "퍼블리시된 메시지: '%s'", msg->data.c_str());
}

void Listener::countCallback(const std_msgs::msg::Int64::SharedPtr msg)
{
    RCLCPP_INFO(this->get_logger(), "퍼블리시된 횟수: %ld", msg->data);
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Listener>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}