#include "turtlesim_style_bg.hpp"
#include <iostream>
#include <algorithm>

TurtlesimStyleBg::TurtlesimStyleBg() : Node("turtlesim_style_bg") {
    // 배경 초기화를 위해 clear_client_를 생성
    clear_client_ = this->create_client<std_srvs::srv::Empty>("/clear");
}

void TurtlesimStyleBg::setBackgroundColor() {
    // 사용자로부터 RGB 값 입력 받기
    int r, g, b;

    std::cout << "배경색을 0부터-255 사이로 입력해라 (r g b): ";
    std::cin >> r >> g >> b;

    // 색상 값 유효성 확인 후 rclcpp 파라미터 설정
    auto parameter_client = std::make_shared<rclcpp::AsyncParametersClient>(this->shared_from_this(), "turtlesim");

    if (parameter_client->wait_for_service(std::chrono::seconds(5))) {
        parameter_client->set_parameters({
            rclcpp::Parameter("background_r", std::max(0, std::min(r, 255))),
            rclcpp::Parameter("background_g", std::max(0, std::min(g, 255))),
            rclcpp::Parameter("background_b", std::max(0, std::min(b, 255)))
        });

        // 배경색 변경 후 화면 클리어를 위해 서비스 호출
        auto request = std::make_shared<std_srvs::srv::Empty::Request>();
        auto result = clear_client_->async_send_request(request);
    }
}
