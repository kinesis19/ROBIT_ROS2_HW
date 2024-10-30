#include "turtlesim_style.hpp"
#include <iostream>
#include <algorithm>

TurtlesimStyle::TurtlesimStyle() : Node("turtlesim_style") {
    // Service Client 생성:
    //set_pen_client_: /turtle1/set_pen 서비스와 통신하기 위한 클라이언트 객체임 -> turtle 제어 가능 
    //turtlesim::srv::SetPen -> Pen Color, width 등을 제어할 수 있는 서비스 타입임
    set_pen_client_ = this->create_client<turtlesim::srv::SetPen>("/turtle1/set_pen");
}

// Pen의 Color와 width를 설정하는 메서드
void TurtlesimStyle::setPenStyle() {
    // 요청 객체 생성 -> Pen 설정을 위한 서비스 요청 객체를 생성함
    auto request = std::make_shared<turtlesim::srv::SetPen::Request>();

    int r, g, b;
    int width;

    std::cout << "Pen Color를 0부터-255 사이로 입력해라 (r g b):";
    std::cin >> r >> g >> b;

    // 입력된 color 값이 정해진 범위 내에 있는지 검사하기
    request->r = std::max(0, std::min(r, 255));
    request->g = std::max(0, std::min(g, 255));
    request->b = std::max(0, std::min(b, 255));

    std::cout << "Pen 두께를 입력해라 (0-10): ";
    std::cin >> width;
    // Pen의 width 제한
    request->width = std::max(0, std::min(width, 10));
    request->off = 0;

    while (!set_pen_client_->wait_for_service(std::chrono::seconds(5))) {
        RCLCPP_WARN(this->get_logger(), "Waiting for the /turtle1/set_pen service to be available...");
    }

    // 비동기 서비스 요청 보내기
    auto future = set_pen_client_->async_send_request(request);
}
