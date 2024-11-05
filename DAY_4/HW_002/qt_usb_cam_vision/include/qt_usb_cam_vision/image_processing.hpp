#ifndef QT_USB_CAM_VISION_IMAGE_PROCESSING_HPP
#define QT_USB_CAM_VISION_IMAGE_PROCESSING_HPP

#include <QThread>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>

class ImageProcessingNode : public QThread
{
    Q_OBJECT

public:
    ImageProcessingNode();
    ~ImageProcessingNode();

protected:
    void run() override;

private:
    rclcpp::Node::SharedPtr node;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_subscription_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr processed_image_publisher_;

    void imageCallback(const sensor_msgs::msg::Image::SharedPtr msg);
};

#endif // QT_USB_CAM_VISION_IMAGE_PROCESSING_HPP