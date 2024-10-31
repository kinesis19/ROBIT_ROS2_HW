#include "rclcpp/rclcpp.hpp"
#include "turtlesim_draw.hpp"

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    
    auto node = std::make_shared<TurtleSimDraw>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}