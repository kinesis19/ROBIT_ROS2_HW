/**
 * @file /include/qt_talker_and_listener/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef qt_talker_and_listener_QNODE_HPP_
#define qt_talker_and_listener_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/
#ifndef Q_MOC_RUN
#include <rclcpp/rclcpp.hpp>
#endif
#include <QThread>
#include "listener.hpp"
#include "talker.hpp"

/*****************************************************************************
** Class
*****************************************************************************/
class QNode : public QThread
{
  Q_OBJECT
public:
  QNode();
  ~QNode();
  void publishMessage(const std::string &message);

protected:
  void run();

private:
  std::shared_ptr<rclcpp::Node> node; // ROS2 노드
  std::shared_ptr<Talker> talker; // Talker 노드의 인스턴스
  std::shared_ptr<Listener> listener; // Listener 노드의 인스턴스

  void onChatterReceived(const std::string &message); // 콜백 함수

Q_SIGNALS:
  void rosShutDown();
  void newMessageReceived(const QString &message, int count);
};

#endif /* qt_talker_and_listener_QNODE_HPP_ */
