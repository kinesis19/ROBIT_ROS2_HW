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

#include "../include/qt_usb_camera_viewer/qnode.hpp"

QNode::QNode()
{
  int argc = 0;
  char** argv = NULL;
  rclcpp::init(argc, argv);
  node = rclcpp::Node::make_shared("qt_usb_camera_viewer");

  /* 이미지 서브스크라이브 설정
  * 레퍼런스: https://github.com/mjlee111/image_recognition/blob/master/image_projection/usb_camera/src/usb_camera_viewer.cpp
  * 리뷰: 오픈소스를 보고 필요한 요소를 적재적소 가져와야 하는 능력이 중요하다는 것을 몸소 느낌 -> 제대로 분석하고 파악만 한다면 패키지 개발 단축 시간 감소
  * rqt로 리버싱 느낌 내면서 하는 것도 중요함. 물로 이 과정이 선행으로 진행 되어야 어떤 토픽이 패키지 내부에 있는지 알 수 있음
  * 그래도 못 찾겠다 싶으면 오픈소스 repo로 들어가서 토픽이랑 로직이 어떻게 구성 되어있는지 찾으면 됨
  */
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