/**
 * @file /src/qnode.cpp
 *
 * @brief Ros communication central!
 *
 * @date August 2024
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include "../include/qt_usb_cam_vision/qnode.hpp"

QNode::QNode()
{
  int argc = 0;
  char** argv = NULL;
  rclcpp::init(argc, argv);
  node = rclcpp::Node::make_shared("qt_usb_cam_vision");

  image_subscription_ = node->create_subscription<sensor_msgs::msg::Image>("/camera1/camera/image_raw", 10, std::bind(&QNode::imageCallback, this, std::placeholders::_1));

  this->start();
}

QNode::~QNode()
{
  if (rclcpp::ok())
  {
    rclcpp::shutdown();
  }
}

void QNode::run()
{
  rclcpp::WallRate loop_rate(20);
  while (rclcpp::ok())
  {
    rclcpp::spin_some(node);
    loop_rate.sleep();
  }
  rclcpp::shutdown();
  Q_EMIT rosShutDown();
}


// 이미지 콜백 메서드
void QNode::imageCallback(const sensor_msgs::msg::Image::SharedPtr msg)
{
  // ROS2 이미지 메시지를 QImage로 변환
  QImage qImage(msg->data.data(), msg->width, msg->height, QImage::Format_RGB888);
  QPixmap pixmap = QPixmap::fromImage(qImage);

  emit imageReceived(pixmap);  // QLabel 표시 시그널
}