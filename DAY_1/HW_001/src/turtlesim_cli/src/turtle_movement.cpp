#include "turtle_movement.hpp"
#include <iostream>
#include <termios.h>
#include <unistd.h>

TurtleMovement::TurtleMovement(std::shared_ptr<rclcpp::Node> node) : node_(node)
{
    /* 퍼블리셔 생성
    * Twist 메시지를 퍼블리셔함
    * 버퍼 크기는 10으로 지정함 -> 퍼블리셔된 메시지들이 최대 10개까지 저장될 수 있음
    */
    velocity_publisher_ = node_->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
}

// Turtlesim 거북이 이동 메서드
void TurtleMovement::move()
{
    std::cout << "WASD Key: Turtle Move. Q Key: quit." << std::endl;

    geometry_msgs::msg::Twist twist;
    char c;

    // Terminal 입력 모드로 사용하기 위해 termios 구조체를 사용함
    // oldt: 백업, newt: 새로운 설정을 담당함
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    // ICANON을 비활성화 하면 문자단위로 입력 받음
    // ECHO를 비활성화해서 사용자의 input value가 terminal에 나타나지 않음
    newt.c_lflag &= ~(ICANON | ECHO);
    // tcsetattr: 새 터미널 생성해서 사용자의 입력을 처리하고 input value가 화면에 표시되지 않게 함
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    while (rclcpp::ok())
    {
        c = getchar();
        twist.linear.x = 0.0;
        twist.angular.z = 0.0;

        if (c == 'w')
        {
            twist.linear.x = 2.0;
        }
        else if (c == 's')
        {
            twist.linear.x = -2.0;
        }
        else if (c == 'a')
        {
            twist.angular.z = 2.0;
        }
        else if (c == 'd')
        {
            twist.angular.z = -2.0;
        }
        else if (c == 'q')
        {
            break;
        }

        // 퍼블리셔: input에 따라 업데이트된 twist 메시지를 퍼블리시해서 거북이의 움직임을 제어함
        velocity_publisher_->publish(twist);
    }

    // q가 눌려서 빠져 나온 상태에서도 입력 방식이 제대로 되도록 터미널을 복원함
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}