#ifndef TURTLESIM_STYLE_BG_HPP
#define TURTLESIM_STYLE_BG_HPP

#include "rclcpp/rclcpp.hpp"
#include <std_srvs/srv/empty.hpp>
#include "rclcpp/parameter_client.hpp"
#include <string>

class TurtlesimStyleBg : public rclcpp::Node {
public:
    TurtlesimStyleBg();
    void setBackgroundColor();

private:
    rclcpp::Client<std_srvs::srv::Empty>::SharedPtr clear_client_;
};

#endif // TURTLESIM_STYLE_BG_HPP
