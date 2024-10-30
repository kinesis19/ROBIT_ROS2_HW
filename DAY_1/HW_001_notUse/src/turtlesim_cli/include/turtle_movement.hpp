// turtle_movement.hpp
#ifndef TURTLE_MOVEMENT_HPP
#define TURTLE_MOVEMENT_HPP

#include <rclcpp/rclcpp.hpp>
/*Turtlesim Turtle을 움직이기 위한 Twist 메시지 사용 -> 거북이 움직임 제어를 위한 헤더파일
* linear(선속도)와 angular(각속도)로 구성됨.
* 각각 x, y, z축이 있음
*/ 

#include <geometry_msgs/msg/twist.hpp>

class TurtleMovement
{
public:
    // Node의 pointer를 인자로 받아 초기화 함 -> pointer는 퍼블리셔 생성하는 데 사용함
    TurtleMovement(std::shared_ptr<rclcpp::Node> node);
    void move();

private:
    // 퍼블리셔(velocity_publisher_)는 Twist 메시지를 퍼블리시하여 거북이의 속도를 제어함
    // 퍼블리셔 개념은 I ROBOT U님이 포스팅하신 글을 다시 봐야할 듯 -> ROS2에서 Node에 대한 개념은 OK, 퍼블리셔에 대한 개념은 아직 미완성
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr velocity_publisher_;
    // Node의 기능을 사용하기 위해 멤버 변수(private type)로 저장함
    std::shared_ptr<rclcpp::Node> node_;
};

#endif // TURTLE_MOVEMENT_HPP