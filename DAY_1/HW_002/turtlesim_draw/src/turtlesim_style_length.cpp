#include "turtlesim_style_length.hpp"
#include <iostream>
#include <algorithm>

TurtlesimStyleLength::TurtlesimStyleLength() : Node("turtlesim_style_length") {
    set_pen_client_ = this->create_client<turtlesim::srv::SetPen>("/turtle1/set_pen");
}

// 변의 지름
void TurtlesimStyleLength::setPenStyleSideLength() {
    std::cout << "변의 길이를 0부터-10 사이로 입력해라:";
    std::cin >> side_length_;
}



// 원의 지름
void TurtlesimStyleLength::setPenStyleDiameterLength() {
    std::cout << "원의 지름을 0부터-10 사이로 입력해라:";
    std::cin >> diameter_length_;
}

// Getter 함수 구현 (변의 길이 반환 메서드)
double TurtlesimStyleLength::getSideLength() const {
    return side_length_;
}

double TurtlesimStyleLength::getDiameterLength() const {
    return diameter_length_;
}