#ifndef qt_turtlebot3_wall_tracking_QNODE_HPP_
#define qt_turtlebot3_wall_tracking_QNODE_HPP_

#ifndef Q_MOC_RUN
#include <rclcpp/rclcpp.hpp>
#endif
#include <QThread>

class QNode : public QThread
{
  Q_OBJECT
public:
  QNode();
  ~QNode();

protected:
  void run();

private:
  std::shared_ptr<rclcpp::Node> node;

Q_SIGNALS:
  void rosShutDown();
};

#endif /* qt_turtlebot3_wall_tracking_QNODE_HPP_ */
