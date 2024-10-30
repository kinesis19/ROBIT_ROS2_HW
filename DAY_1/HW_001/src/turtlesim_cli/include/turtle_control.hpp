#ifndef TURTLE_CONTROL_HPP
#define TURTLE_CONTROL_HPP

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <termios.h>
#include <unistd.h>

class TurtleSimControl
{
public:
    TurtleSimControl(std::shared_ptr<rclcpp::Node> node);
    void controlTurtle();
    
private:
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr vel_publisher_;
};

#endif // TURTLE_CONTROL_HPP