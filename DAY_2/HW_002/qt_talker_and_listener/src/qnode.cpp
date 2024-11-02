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

#include "../include/qt_talker_and_listener/qnode.hpp"

QNode::QNode()
{
  int argc = 0;
  char** argv = NULL;
  rclcpp::init(argc, argv);
  node = rclcpp::Node::make_shared("qt_talker_and_listener");

  // Talker와 Listener 초기화
  talker = std::make_shared<Talker>();
  listener = std::make_shared<Listener>();
  
  // Listener에 메시지 처리 콜백 설정
  listener->setChatterCallback(std::bind(&QNode::onChatterReceived, this, std::placeholders::_1));

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
    /* listener 노드에 큐에 쌓여 있는 콜백 처리를 위해 추가해야 함*/
    rclcpp::spin_some(listener);
    loop_rate.sleep();
  }
  rclcpp::shutdown();
  Q_EMIT rosShutDown();
}

void QNode::publishMessage(const std::string &message)
{
  talker->publishMessage(message);
}

void QNode::onChatterReceived(const std::string &message)
{
    int message_count = talker->getMessageCount(); // Talker의 message_count_ 값 가져오기
    emit newMessageReceived(QString::fromStdString(message), message_count); // 메시지랑 카운트 보내기
}
