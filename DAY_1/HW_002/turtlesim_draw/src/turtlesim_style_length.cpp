#include "turtlesim_style_length.hpp"
#include <iostream>
#include <algorithm>

TurtlesimStyleLength::TurtlesimStyleLength() : Node("turtlesim_style_length") {
    set_pen_client_ = this->create_client<turtlesim::srv::SetPen>("/turtle1/set_pen");
}

// 변의 지름
void TurtlesimStyleLength::setPenStyleSideLength() {
    auto request = std::make_shared<turtlesim::srv::SetPen::Request>();

    int len;

    std::cout << "변의 길이를 0부터-10 사이로 입력해라:";
    std::cin >> len;

    // 입력된 color 값이 정해진 범위 내에 있는지 검사하기
    request->len = len;

    // 비동기 서비스 요청 보내기
    auto future = set_pen_client_->async_send_request(request);
}



// 원의 지름
void TurtlesimStyleLength::setPenStyleDiameterLength() {
    auto request = std::make_shared<turtlesim::srv::SetPen::Request>();

    int len;

    std::cout << "원의 지름을 0부터-10 사이로 입력해라:";
    std::cin >> len;

    // 입력된 color 값이 정해진 범위 내에 있는지 검사하기
    request->len = len;

    // 비동기 서비스 요청 보내기
    auto future = set_pen_client_->async_send_request(request);
}