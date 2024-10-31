#include "turtlesim_style_pen.hpp"
#include <iostream>
#include <algorithm>

TurtlesimStyle::TurtlesimStyle() : Node("turtlesim_style") {
    set_pen_client_ = this->create_client<turtlesim::srv::SetPen>("/turtle1/set_pen");
}

// Pen 설정 메서드 (1일차 과제1의 모드와 중복 되는 부분이므로 적용함)
void TurtlesimStyle::setPenStyle() {
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

    // 비동기 서비스 요청 보내기
    auto future = set_pen_client_->async_send_request(request);
}
