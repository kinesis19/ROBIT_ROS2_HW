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

private:

    rclcpp::Client<turtlesim::srv::SetPen>::SharedPtr set_pen_client_;
};

#endif // TURTLESIM_STYLE_LENGTH_HPP