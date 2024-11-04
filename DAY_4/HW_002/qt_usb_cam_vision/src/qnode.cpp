/**
 * @file /src/qnode.cpp
 *
 * @brief Ros communication central!
 *
 * @date August 2024
 **/
// #include "../include/qt_usb_cam_vision/qnode.hpp"

// QNode::QNode()
// {
//   int argc = 0;
//   char** argv = NULL;
//   rclcpp::init(argc, argv);
//   node = rclcpp::Node::make_shared("qt_usb_camera_viewer");

//   // 이미지 구독 설정
//   image_subscription_ = node->create_subscription<sensor_msgs::msg::Image>(
//       "/camera1/camera/image_raw", 10, std::bind(&QNode::imageCallback, this, std::placeholders::_1));

//   this->start();
// }

// QNode::~QNode()
// {
//   if (rclcpp::ok())
//   {
//     rclcpp::shutdown();
//   }
// }

// void QNode::run()
// {
//   rclcpp::WallRate loop_rate(20);
//   while (rclcpp::ok())
//   {
//     rclcpp::spin_some(node);
//     loop_rate.sleep();
//   }
//   Q_EMIT rosShutDown();
// }

// // 이미지 콜백 함수
// void QNode::imageCallback(const sensor_msgs::msg::Image::SharedPtr msg)
// {
//   QImage qImage(msg->data.data(), msg->width, msg->height, QImage::Format_RGB888);
//   QPixmap pixmap = QPixmap::fromImage(qImage);

//   emit imageReceived(pixmap);
// }
#include "../include/qt_usb_cam_vision/qnode.hpp"
#include <QImage>
#include <QPixmap>

QNode::QNode()
{
  node = rclcpp::Node::make_shared("qt_usb_camera_viewer");

  // 이미지 구독 설정
  image_subscription_ = node->create_subscription<sensor_msgs::msg::Image>(
      "/camera1/camera/image_raw", 10, std::bind(&QNode::imageCallback, this, std::placeholders::_1));

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
  Q_EMIT rosShutDown();
}

// 이미지 콜백 함수
void QNode::imageCallback(const sensor_msgs::msg::Image::SharedPtr msg)
{
  QImage qImage(msg->data.data(), msg->width, msg->height, QImage::Format_RGB888);
  QPixmap pixmap = QPixmap::fromImage(qImage);

  emit imageReceived(pixmap);
}
