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

#include "../include/qt_turtlesim_controller/qnode.hpp"


QNode::QNode()
{
  int argc = 0;
  char** argv = NULL;
  rclcpp::init(argc, argv);
  node = rclcpp::Node::make_shared("qt_turtlesim_controller");

  // cmd_vel 퍼블리셔 생성
  velocity_publisher = node->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);

  // 배경색 변경을 위한 파라미터 클라이언트 초기화
  parameter_client_ = std::make_shared<rclcpp::AsyncParametersClient>(node, "turtlesim");
  // 배경 초기화를 위해 clear_client_ 생성
  clear_client_ = node->create_client<std_srvs::srv::Empty>("/clear");

  // cmd_vel 구독 관련 설정 -> 이 부분은 아직 어려워서 이해가 잘 안 됨. -> 구현 부분이. 이 부분을 다시 공부하고 이해할 필요가 있음.
  cmd_vel_subscription = node->create_subscription<geometry_msgs::msg::Twist>(
      "/turtle1/cmd_vel",
      10,
      [this](geometry_msgs::msg::Twist::SharedPtr msg) {
          emit cmdVelUpdated(msg->linear.x, msg->linear.y, msg->linear.z, msg->angular.x, msg->angular.y, msg->angular.z);
      }
  );

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

// 거북이 이동 제어 메서드
void QNode::moveTurtle(double linear_x, double angular_z)
{
  auto twist_msg = geometry_msgs::msg::Twist();
  twist_msg.linear.x = linear_x;
  twist_msg.angular.z = angular_z;
  velocity_publisher->publish(twist_msg);
}

// 배경색 제어 메서드
void QNode::setBackgroundColor(int r, int g, int b) {
  if (parameter_client_->wait_for_service(std::chrono::seconds(5))) {
    parameter_client_->set_parameters({
      rclcpp::Parameter("background_r", std::clamp(r, 0, 255)),
      rclcpp::Parameter("background_g", std::clamp(g, 0, 255)),
      rclcpp::Parameter("background_b", std::clamp(b, 0, 255))
    });

    // 배경색 변경 후 화면 클리어를 위해 서비스 호출
    auto request = std::make_shared<std_srvs::srv::Empty::Request>();
    clear_client_->async_send_request(request);
  }
}