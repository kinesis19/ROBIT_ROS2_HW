#ifndef TURTLESIM_STYLE_LENGTH_HPP
#define TURTLESIM_STYLE_LENGTH_HPP

#include "rclcpp/rclcpp.hpp"
#include "turtlesim/srv/set_pen.hpp"
#include <string>

class TurtlesimStyleLength : public rclcpp::Node {
public:
    TurtlesimStyleLength();

    void setPenStyleSideLength();
    void setPenStyleDiameterLength();

    double getSideLength() const;
    double getDiameterLength() const;

private:
    rclcpp::Client<turtlesim::srv::SetPen>::SharedPtr set_pen_client_;
    double side_length_ = 1.0; // 기본 변의 길이
    double diameter_length_ = 1.0; // 기본 원의 지름
};

#endif // TURTLESIM_STYLE_LENGTH_HPP