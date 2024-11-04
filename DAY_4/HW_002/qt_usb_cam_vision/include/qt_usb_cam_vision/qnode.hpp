#ifndef qt_usb_cam_vision_QNODE_HPP_
#define qt_usb_cam_vision_QNODE_HPP_

#include <rclcpp/rclcpp.hpp>
#include <QThread>
#include <QImage>
#include <QPixmap>
#include <sensor_msgs/msg/image.hpp>

class QNode : public QThread
{
  Q_OBJECT
public:
  QNode();  // 기본 생성자
  ~QNode();

protected:
  void run() override;

private:
  rclcpp::Node::SharedPtr node;
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_subscription_;

  void imageCallback(const sensor_msgs::msg::Image::SharedPtr msg);

Q_SIGNALS:
  void imageReceived(const QPixmap& pixmap);
  void rosShutDown();
};

#endif /* qt_usb_cam_vision_QNODE_HPP_ */
