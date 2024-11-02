#include "turtlesim_draw.hpp"

TurtleSimDraw::TurtleSimDraw() : Node("turtlesim_draw")
{
    RCLCPP_INFO(this->get_logger(), "TurtleSimDraw Node 초기화");

    // TurtleSim 실행
    std::system("ros2 run turtlesim turtlesim_node &");

    sideLength = 1.0;
    diameterLength = 1.0;

    run();
}

// 프로세스 시작
void TurtleSimDraw::run()
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

void TurtleSimDraw::displayMenu()
{
    std::cout << "===== TurtleSim CLI Menu =====\n";
    std::cout << "1. 도형 선택(삼각형, 원, 사각형)\n";
    std::cout << "2. 크기 설정(변 길이, 지름 등)\n";
    std::cout << "3. Pen 설정(색상, 두께)\n";
    std::cout << "모드 선택하기 (1-3): ";
}

int TurtleSimDraw::getUserInput()
{
    int input;
    std::cin >> input;
    return input;
}

void TurtleSimDraw::processInput(int mode)
{
    switch (mode)
    {
    case 1:
        {
            std::cout << "도형 선택 모드를 선택했음." << std::endl;
            std::cout << "어떤 도형? <1. 삼각형 | 2. 원 | 3. 사각형>" << std::endl;
            int input;
            std::cin >> input;
            
            auto turtle_draw_shape = std::make_shared<TurtlesimDrawShape>();

            if(input == 1){
                turtle_draw_shape->drawTriangle(side_length_);
            }else if(input == 2){
                turtle_draw_shape->drawCircle(diameter_length_);
            }else if(input == 3){
                turtle_draw_shape->drawQuadrilateral(side_length_);
            }
        }
        break;
    case 2:
        {
            std::cout << "크기 설정 모드를 선택했음.\n";

            std::cout << "어떤 크기 설정? <1. 변의 길이 | 2. 원의 지름 >" << std::endl;
            int inputOption;
            std::cin >> inputOption;
            
            auto turtle_style_length = std::make_shared<TurtlesimStyleLength>();

            if(inputOption == 1){
                turtle_style_length->setPenStyleSideLength();
                side_length_ = turtle_style_length->getSideLength();
            } else if(inputOption == 2) {
                turtle_style_length->setPenStyleDiameterLength();
                diameter_length_ = turtle_style_length->getDiameterLength();
            } 
            
        }
        break;
    case 3:
        {
            std::cout << "Pen 설정 모드를 선택했음.\n";
            auto turtle_style = std::make_shared<TurtlesimStyle>();
            turtle_style->setPenStyle();  // setPenStyle 호출
        }
        
        break;
    default:
        std::cout << "없는 모드다.\n";
        break;
    }
}
