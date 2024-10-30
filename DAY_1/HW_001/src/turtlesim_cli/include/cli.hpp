// turtle_sim_controller.hpp
#ifndef CLI_HPP
#define CLI_HPP

#include <rclcpp/rclcpp.hpp>
#include "turtle_movement.hpp"
#include <string>
#include <memory>

class TurtleSimCLI : public rclcpp::Node, public std::enable_shared_from_this<TurtleSimCLI>
{
public:
    TurtleSimCLI();
private:
    void controlMode();
    TurtleMovement turtle_movement_;
};

#endif // CLI_HPP