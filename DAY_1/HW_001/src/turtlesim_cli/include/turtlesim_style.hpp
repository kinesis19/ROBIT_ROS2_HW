#ifndef TURTLESIM_STYLE_HPP
#define TURTLESIM_STYLE_HPP

#include "rclcpp/rclcpp.hpp"
#include "turtlesim/srv/set_pen.hpp"
#include <string>

class TurtlesimStyle : public rclcpp::Node {
public:
    TurtlesimStyle();
    void setPenStyle();

private:
    rclcpp::Client<turtlesim::srv::SetPen>::SharedPtr set_pen_client_;
};

#endif // TURTLESIM_STYLE_HPP