#include "qt_talker_and_listener/talker.hpp"

Talker::Talker() : Node("talker")
{
    publisher_ = this->create_publisher<std_msgs::msg::String>("/chatter", 10);
    count_publisher_ = this->create_publisher<std_msgs::msg::Int64>("/chatter_count", 10);
    RCLCPP_INFO(this->get_logger(), "Talker Node 초기화 완료");
}

void Talker::publishMessage(const std::string &message)
{
    // 문자열 메시지 생성 퍼블리쉬
    auto msg = std_msgs::msg::String();
    msg.data = message;
    publisher_->publish(msg);

    // 퍼블리쉬 횟수 증가하고 그 카운트를 퍼블리쉬함
    message_count_++;
    auto count_message = std_msgs::msg::Int64();
    count_message.data = message_count_;

    count_publisher_->publish(count_message);
}

// 퍼블리쉬한 카운트 반환하는 메서드
int Talker::getMessageCount()
{
    return message_count_;
}