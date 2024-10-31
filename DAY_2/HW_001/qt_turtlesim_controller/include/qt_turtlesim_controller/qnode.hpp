/**
 * @file /include/qt_turtlesim_controller/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef qt_turtlesim_controller_QNODE_HPP_
#define qt_turtlesim_controller_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/
#ifndef Q_MOC_RUN
#include <rclcpp/rclcpp.hpp>
#endif
#include <QThread>
#include "geometry_msgs/msg/twist.hpp"
#include "std_srvs/srv/empty.hpp"

/*****************************************************************************
** Class
*****************************************************************************/
class QNode : public QThread
{
  Q_OBJECT
public:
  QNode();
  ~QNode();
  // 거북이 제어를 위한 메서드
  void moveTurtle(double linear_x, double angular_z);
  // 거북이 배경색 제어를 위한 메서드
  void setBackgroundColor(int r, int g, int b);

protected:
  void run();

private:
  std::shared_ptr<rclcpp::Node> node;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr velocity_publisher;

  // 배경색 변경은 1일차 과제를 참고해서 응용함
  // 배경색 변경 후 클리어를 위해 사용
  rclcpp::Client<std_srvs::srv::Empty>::SharedPtr clear_client_;  
  // 파라미터 클라이언트
  std::shared_ptr<rclcpp::AsyncParametersClient> parameter_client_;  

  // cmd_vel 구독
  rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_subscription;


Q_SIGNALS:
  void rosShutDown();
  void cmdVelUpdated(double linear_x, double linear_y, double linear_z, double angular_x, double angular_y, double angular_z);
};

#endif /* qt_turtlesim_controller_QNODE_HPP_ */
