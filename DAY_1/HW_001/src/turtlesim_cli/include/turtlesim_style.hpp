#ifndef TURTLESIM_STYLE_HPP
#define TURTLESIM_STYLE_HPP

#include <rclcpp/rclcpp.hpp>
#include <turtlesim/srv/set_pen.hpp>
#include <iostream>

class TurtleSimStyle {
public:
    TurtleSimStyle(std::shared_ptr<rclcpp::Node> node, const std::string& turtle_name);
    void setPen(int r, int g, int b, int width, bool off);

private:
    rclcpp::Client<turtlesim::srv::SetPen>::SharedPtr set_pen_client_;
    std::string turtle_name_;
};

#endif // TURTLESIM_STYLE_HPP
