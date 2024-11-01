#ifndef TURTLESIM_STYLE_SHAPE_HPP
#define TURTLESIM_STYLE_SHAPE_HPP

#include "rclcpp/rclcpp.hpp"
#include "turtlesim/srv/spawn.hpp"
#include "turtlesim/srv/kill.hpp"
#include "rclcpp/parameter_client.hpp"
#include <iostream>

class TurtlesimStyleShape : public rclcpp::Node {
public:
    TurtlesimStyleShape();
    void setTurtleShape();

private:
    rclcpp::Client<turtlesim::srv::Spawn>::SharedPtr spawn_client_;
    rclcpp::Client<turtlesim::srv::Kill>::SharedPtr kill_client_;
    std::string current_turtle_name_;
};

#endif // TURTLESIM_STYLE_SHAPE_HPP

