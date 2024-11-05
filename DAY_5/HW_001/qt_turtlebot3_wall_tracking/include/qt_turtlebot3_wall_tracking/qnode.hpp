#ifndef qt_turtlebot3_wall_tracking_QNODE_HPP_
#define qt_turtlebot3_wall_tracking_QNODE_HPP_

#ifndef Q_MOC_RUN
#include <rclcpp/rclcpp.hpp>
#endif
#include <QThread>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <geometry_msgs/msg/twist.hpp>

class QNode : public QThread
{
  Q_OBJECT
public:
  QNode();
  ~QNode();

  void setDistanceParameter(float distance);  // distance 파라미터 설정 메서드
  void setCmdVelParameter(float linear_x, float angular_z);  // cmd_vel 설정 메서드
  void startAutoTrackingforWall(float linear_x, float angular_z); // 벽 따라가기
  void stopAutoTracking(); // Auto Tracking 중지 메서드

protected:
  void run();

private:
  std::shared_ptr<rclcpp::Node> node;
  rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr scan_subscriber_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_publisher_;

  float target_distance_;   // 사용자가 설정한 목표 거리

  float current_distance_front_;
  float current_distance_back_;
  float current_distance_left_;
  float current_distance_right_;
  float linear_velocity_;
  float angular_velocity_;

  bool is_tracking_; // true: Start Btn, false: Stop Btn

  rclcpp::TimerBase::SharedPtr wall_tracking_timer_;
  rclcpp::Parameter wall_distance_param_;

  void scanCallback(const sensor_msgs::msg::LaserScan::SharedPtr msg);  // 콜백 메서드
  void autoTrackingCallback(); // 타이머 콜백 함수

Q_SIGNALS:
  void rosShutDown();
  void updateDistanceLabel(float distFront, float distBack, float distLeft, float distRight);
};

#endif /* qt_turtlebot3_wall_tracking_QNODE_HPP_ */
