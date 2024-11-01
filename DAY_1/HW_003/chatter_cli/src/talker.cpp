/* 로직을 어떻게 구현할지 고민해 보자.
* ROS2의 Talker와 Listener를 직접 만드는 것이 이번 과제로 이해함.
* Talker와 Listener는 각각 터미널1과 터미널2에서 package를 run할 때 실행 됨.
* 그러면 main을 Talker에 하나, Listener에 하나 이렇게 총 두 개를 두어야 하지 않을까? 라고 생각함.
* 간단하게 구성하기 위해 main() 함수는 따로 분리하지 않고 구현함.
*/
#include "chatter_cli/talker.hpp"

Talker::Talker() : Node("talker")
{   
    // 퍼블리셔 초기화
    publisher_ = this->create_publisher<std_msgs::msg::String>("/chatter_cli", 10);
    count_publisher_ = this->create_publisher<std_msgs::msg::Int64>("/chatter_count", 10);
    RCLCPP_INFO(this->get_logger(), "Talker Node 초기화 완료");
}

void Talker::run()
{
    // rclcpp::Rate rate(1); // 1초에 한 번 루프 반복
    while (rclcpp::ok())
    {
        // 사용자로부터 문자열 입력 받기
        std::string input;
        std::cout << "메시지 입력: ";
        std::getline(std::cin, input); // getline(): C언의 gets() 같은 함수임

        // 문자열 메시지 퍼블리시
        auto string_message = std_msgs::msg::String();
        string_message.data = input;

        publisher_->publish(string_message);

        /* 퍼블리시 횟수 메시지 퍼블리시
        * ROS2의 demo_node_cpp의 talker를 레퍼런스로 구현하는 과제로 이해하여 진행함.
        * 과제에서도 입력 처리에 대해서는 메시지만을 요구했고, demo_node_cpp에서의 talker로 메시지만 입력을 받았기에, 카운트는 자동으로 1씩 증가하게 로직을 구성함.
        */
        message_count_++;
        auto count_message = std_msgs::msg::Int64();
        count_message.data = message_count_;

        count_publisher_->publish(count_message);

        // ROS 스핀 및 루프 속도 유지
        rclcpp::spin_some(this->get_node_base_interface());
    }
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Talker>();
    node->run(); // run 함수 호출
    rclcpp::shutdown();
    return 0;
}
