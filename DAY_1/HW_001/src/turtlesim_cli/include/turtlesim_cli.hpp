#ifndef TURTLESIM_CLI_HPP
#define TURTLESIM_CLI_HPP

#include "rclcpp/rclcpp.hpp"
#include "turtlesim_control.hpp"
#include "turtlesim_style.hpp"
#include <string>
#include <iostream>
#include <cstdlib>
#include <memory>

class TurtleSimCLI : public rclcpp::Node
{
public:
    TurtleSimCLI(); // 생성자
    void run(); // 프로세스 시작
private:
    // 메뉴 띄우기(모드1부터 ~ 4까지)
    void displayMenu();
    // 사용자 입력 받기(숫자1부터 ~ 4까지)
    int getUserInput();
    // 사용자 입력에 따른 처리하기
    void processInput(int mode);
    // turtlesim 실행을 위한 함수
    void startTurtleSim();
};

#endif // TURTLESIM_CLI_HPP