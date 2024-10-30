#include "rclcpp/rclcpp.hpp"
#include "turtlesim_cli.hpp"

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TurtleSimCLI>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}