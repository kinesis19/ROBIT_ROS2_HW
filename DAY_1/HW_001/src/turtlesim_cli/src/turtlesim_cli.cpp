#include "turtlesim_cli.hpp"

TurtleSimCLI::TurtleSimCLI() : Node("turtlesim_cli")
{
    RCLCPP_INFO(this->get_logger(), "TurtleSimCLI Node 초기화");

    // TurtleSim 실행
    std::system("ros2 run turtlesim turtlesim_node &");

    run();
}

// 프로세스 시작
void TurtleSimCLI::run()
{
    // 무한으로 입력 받음(escape: Ctrl + C)
    // rclcpp::ok() -> 노드가 실행가능하고 정상적일 때: true, 그렇지 않으면 false를 return함
    while (rclcpp::ok())
    {
        displayMenu(); // 메뉴 띄우기
        int mode = getUserInput(); // 입력 받기
        processInput(mode); // 입력에 따른 프로세스 진행하기
    }
}

void TurtleSimCLI::displayMenu()
{
    std::cout << "===== TurtleSim CLI Menu =====\n";
    std::cout << "1. 조종 모드\n";
    std::cout << "2. 배경색 설정 모드\n";
    std::cout << "3. 거북이 모양 설정 모드\n";
    std::cout << "4. pen 설정 모드\n";
    std::cout << "모드 선택하기 (1-4): ";
}

int TurtleSimCLI::getUserInput()
{
    int input;
    std::cin >> input;
    return input;
}

void TurtleSimCLI::processInput(int mode)
{
    switch (mode)
    {
    case 1:
        {
            std::cout << "조종 모드를 선택했음.\n";
            auto turtle_control = std::make_shared<TurtleSimControl>();
            turtle_control->controlLoop();
        }
        break;
    case 2:
        {
            
        }
        break;
    case 3:
        std::cout << "거북이 모양 설정 모드를 선택했음.\n";
        break;
    case 4:
        {
            std::cout << "pen 설정 모드를 선택했음.\n";
            auto turtle_style = std::make_shared<TurtlesimStyle>();
            turtle_style->setPenStyle();  // setPenStyle 호출
        }
        break;
    default:
        std::cout << "없는 모드다.\n";
        break;
    }
}
