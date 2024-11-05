#ifndef QT_USB_CAM_VISION_PARAMETER_SETTING_HPP
#define QT_USB_CAM_VISION_PARAMETER_SETTING_HPP

#include <QThread>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int32.hpp>

class ParameterSettingNode : public QThread
{
    Q_OBJECT

public:
    ParameterSettingNode();
    ~ParameterSettingNode();

    void setParameter(int value);  // 파라미터 설정 매서드

protected:
    void run() override;

private:
    rclcpp::Node::SharedPtr node;
    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr parameter_publisher_;
};

#endif // QT_USB_CAM_VISION_PARAMETER_SETTING_HPP