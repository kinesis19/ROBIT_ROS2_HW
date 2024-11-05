#include "../include/qt_usb_cam_vision/parameter_setting.hpp"

ParameterSettingNode::ParameterSettingNode()
{
    node = rclcpp::Node::make_shared("parameter_setting_node");

    // 파라미터 퍼블리셔 설정
    parameter_publisher_ = node->create_publisher<std_msgs::msg::Int32>("/parameter_value", 10);
}

ParameterSettingNode::~ParameterSettingNode()
{
    if (rclcpp::ok())
    {
        rclcpp::shutdown();
    }
}

void ParameterSettingNode::run()
{
    rclcpp::WallRate loop_rate(20);
    while (rclcpp::ok())
    {
        rclcpp::spin_some(node);
        loop_rate.sleep();
    }
}

// 파라미터 설정 메서드
void ParameterSettingNode::setParameter(int value)
{
    
}
