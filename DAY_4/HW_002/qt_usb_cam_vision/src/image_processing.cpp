#include "../include/qt_usb_cam_vision/image_processing.hpp"

ImageProcessingNode::ImageProcessingNode()
{
    node = rclcpp::Node::make_shared("image_processing_node");

    // 이미지 서브스크라이버 설정
    image_subscription_ = node->create_subscription<sensor_msgs::msg::Image>("/camera1/camera/image_raw", 10, std::bind(&ImageProcessingNode::imageCallback, this, std::placeholders::_1));

    // 처리된 이미지 퍼블리셔 설정
    processed_image_publisher_ = node->create_publisher<sensor_msgs::msg::Image>("/processed_image", 10);
}

ImageProcessingNode::~ImageProcessingNode()
{
    if (rclcpp::ok())
    {
        rclcpp::shutdown();
    }
}

void ImageProcessingNode::run()
{
    rclcpp::WallRate loop_rate(20);
    while (rclcpp::ok())
    {
        rclcpp::spin_some(node);
        loop_rate.sleep();
    }
}

// 이미지 콜백 메서드
void ImageProcessingNode::imageCallback(const sensor_msgs::msg::Image::SharedPtr msg)
{
    
}