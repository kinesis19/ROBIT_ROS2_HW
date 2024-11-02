#ifndef TURTLESIM_DRAW_HPP
#define TURTLESIM_DRAW_HPP

#include "rclcpp/rclcpp.hpp"
#include "turtlesim_style_pen.hpp"
#include "turtlesim_draw_shape.hpp"
#include "turtlesim_style_length.hpp"
#include <string>
#include <iostream>
#include <cstdlib>
#include <memory>

class TurtleSimDraw : public rclcpp::Node
{
public:
    TurtleSimDraw(); // 생성자
    void run(); // 프로세스 시작
private:
    // 메뉴 띄우기(모드1부터 ~ 4까지)
    void displayMenu();
    // 사용자 입력 받기(숫자1부터 ~ 4까지)
    int getUserInput();
    // 사용자 입력에 따른 처리하기efe
    void processInput(int mode);


    // 도형에 대한 변수
    double sideLength, diameterLength;
    std::shared_ptr<TurtlesimDrawShape> turtle_draw_shape;

    double side_length_ = 1.0;       // 변의 길이 (기본값)
    double diameter_length_ = 1.0;   // 원의 지름 (기본값)

};

#endif // TURTLESIM_DRAW_HPP