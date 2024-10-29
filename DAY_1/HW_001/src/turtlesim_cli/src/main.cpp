#include "turtle_sim_controller.hpp"

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TurtleSimController>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}