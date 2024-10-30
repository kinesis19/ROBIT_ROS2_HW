#include "turtlesim_style.hpp"

TurtleSimStyle::TurtleSimStyle(std::shared_ptr<rclcpp::Node> node, const std::string& turtle_name) : turtle_name_(turtle_name) {
    set_pen_client_ = node->create_client<turtlesim::srv::SetPen>("/" + turtle_name_ + "/set_pen");
}

void TurtleSimStyle::setPen(int r, int g, int b, int width, bool off) {
    auto request = std::make_shared<turtlesim::srv::SetPen::Request>();
    request->r = r;
    request->g = g;
    request->b = b;
    request->width = width;
    request->off = off;

    // while (!set_pen_client_->wait_for_service(std::chrono::seconds(1))) {
    //     if (!rclcpp::ok()) {
    //         return;
    //     }
    // }

    auto result = set_pen_client_->async_send_request(request);
}
