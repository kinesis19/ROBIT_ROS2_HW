#include "turtle_control.hpp"

TurtleSimControl::TurtleSimControl(std::shared_ptr<rclcpp::Node> node)
{
    vel_publisher_ = node->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", 10);
}

void TurtleSimControl::controlTurtle()
{
    RCLCPP_INFO(rclcpp::get_logger("TurtleSimControl"), "Control mode activated. Use WASD to move the turtle. Press Q to quit.");
    geometry_msgs::msg::Twist twist;

    char key;
    struct termios oldt, newt;

    // 터미널 설정을 변경하여 즉시 키 입력을 받도록 설정
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    while (rclcpp::ok())
    {
        key = getchar();  // 키 입력 받기

        // 방향에 따라 twist 메시지 설정
        switch (key)
        {
        case 'w':
            twist.linear.x = 2.0;
            twist.angular.z = 0.0;
            break;
        case 's':
            twist.linear.x = -2.0;
            twist.angular.z = 0.0;
            break;
        case 'a':
            twist.linear.x = 0.0;
            twist.angular.z = 2.0;
            break;
        case 'd':
            twist.linear.x = 0.0;
            twist.angular.z = -2.0;
            break;
        case 'q':
            RCLCPP_INFO(rclcpp::get_logger("TurtleSimControl"), "Exiting control mode.");
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  // 터미널 설정 복구
            return;
        default:
            twist.linear.x = 0.0;
            twist.angular.z = 0.0;
            break;
        }

        // 퍼블리셔로 메시지 보냄
        vel_publisher_->publish(twist);
    }

    // 터미널 설정 복구
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}
