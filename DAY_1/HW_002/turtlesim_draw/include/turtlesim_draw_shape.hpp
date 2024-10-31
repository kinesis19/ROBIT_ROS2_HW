#ifndef TURTLESIM_DRAW_SHAPE_HPP
#define TURTLESIM_DRAW_SHAPE_HPP

#include "rclcpp/rclcpp.hpp"
#include "turtlesim/srv/set_pen.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <string>

class TurtlesimDrawShape : public rclcpp::Node {
public:
    TurtlesimDrawShape();
    // 펜 설정 메서드
    void setPenStyle();

    // 도형 그리는 메서드들
    void drawTriangle(double sideLength);
    void drawQuadrilateral(double sideLength);
    void drawCircle(double diameterLength);

private:
    // Pen Style 설정
    rclcpp::Client<turtlesim::srv::SetPen>::SharedPtr set_pen_client_;
    // 거북이 이동을 위한 msgs 설정
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr velocity_publisher;
};

#endif // TURTLESIM_DRAW_SHAPE_HPP