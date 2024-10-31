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

  // pen 설정을 위한 set_pen_client_ 생성
  set_pen_client_ = node->create_client<turtlesim::srv::SetPen>("/turtle1/set_pen");

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
  
    parameter_client_->set_parameters({
      rclcpp::Parameter("background_r", std::clamp(r, 0, 255)),
      rclcpp::Parameter("background_g", std::clamp(g, 0, 255)),
      rclcpp::Parameter("background_b", std::clamp(b, 0, 255))
    });

    // 배경색 변경 후 화면 클리어를 위해 서비스 호출
    auto request = std::make_shared<std_srvs::srv::Empty::Request>();
    clear_client_->async_send_request(request);
}

// Pen 제어 메서드
void QNode::setPenStyle(int r, int g, int b, int width) {


  // 요청 객체 생성 -> Pen 설정을 위한 서비스 요청 객체를 생성함
  auto request = std::make_shared<turtlesim::srv::SetPen::Request>();

  request->r = std::max(0, std::min(r, 255));
  request->g = std::max(0, std::min(g, 255));
  request->b = std::max(0, std::min(b, 255));
  request->width = std::max(0, std::min(width, 10));

  auto future = set_pen_client_->async_send_request(request);
}


// 삼각형 그리는 신호 받았을 때 거북이가 삼각형을 그림
void QNode::drawTriangle(double sideLength) {
  auto twist_msg = geometry_msgs::msg::Twist();

  // 삼각형 그리기: 총 세 번 이동 및 회전
  for (int i = 0; i < 3; ++i) {
    // 직선 이동
    twist_msg.linear.x = sideLength;  // 앞으로 이동할 길이 설정 (사용자로부터 입력 받은 값, 없다면 1이 됨)
    twist_msg.angular.z = 0.0;        // 회전 없이 직진(이동중에 고개 틀면 그건 삼각형이 아님 모서리에서 고개를 틀어야 함)
    velocity_publisher->publish(twist_msg);
    rclcpp::sleep_for(std::chrono::milliseconds(1000)); // 딜레이

    // 회전 (120도 회전)
    twist_msg.linear.x = 0.0;          // 이동 멈춤 -> 꼭짓점에서 각도 틀어야 하니까 멈춤 처리
    twist_msg.angular.z = M_PI / 1.5;  // 반시계 방향으로 120도 회전 -> M_PI가 math.h에서 지원하는 3.14 ~~~ 상수임. 이거를 1.5로 나누면 120이 된다고 함
    velocity_publisher->publish(twist_msg);
    rclcpp::sleep_for(std::chrono::milliseconds(1000)); // 딜레이
  }

  // 멈춤 
  twist_msg.linear.x = 0.0; // 다 그렸으면 멈추도록 처리함
  twist_msg.angular.z = 0.0;
  velocity_publisher->publish(twist_msg);
}

// 네모 그리는 신호 받았을 때 거북이가 네모를 그림
void QNode::drawQuadrilateral(double sideLength) {
  auto twist_msg = geometry_msgs::msg::Twist();

  // 네모 그리기: 총 네 번 이동 및 회전
  for (int i = 0; i < 4; ++i) {
    // 직선 이동
    twist_msg.linear.x = sideLength;  // 앞으로 이동할 길이 설정
    twist_msg.angular.z = 0.0;        // 회전 없이 직진
    velocity_publisher->publish(twist_msg);
    rclcpp::sleep_for(std::chrono::milliseconds(1000)); // 딜레이

    // 회전 (90도 회전)
    twist_msg.linear.x = 0.0;         // 이동 멈춤 -> 꼭짓점에서 각도 틀기 위해 멈춤
    twist_msg.angular.z = M_PI / 2;   // 반시계 방향으로 90도 회전 -> M_PI/2가 90도가 된다고 함
    velocity_publisher->publish(twist_msg);
    rclcpp::sleep_for(std::chrono::milliseconds(1000)); // 딜레이
  }

  // 멈춤
  twist_msg.linear.x = 0.0;  // 도형을 다 그린 후 멈추기
  twist_msg.angular.z = 0.0;
  velocity_publisher->publish(twist_msg);
}

// 원 그리는 신호 받았을 때 거북이가 원을 그림 (미완성)
// 원 그리는 건 공식 이해가 안 되어서 레퍼런스와 인공지능을 응용함
// 공식 이해가 안 되고, 적용해도 의도한 바와 같이 그림이 안 그려짐
void QNode::drawCircle(double diameterLength) {
  // 새로운 스레드를 생성하여 원 그리기 동작 수행
  std::thread drawThread([this, diameterLength]() {
      auto twist_msg = geometry_msgs::msg::Twist();

      // 원을 그리기 위한 설정
      double radius = diameterLength / 2.0;              // 반지름 계산
      double linearVelocity = 0.5;                       // 선형 속도 설정
      double angularVelocity = linearVelocity / radius;  // 각속도 설정 (v = r * ω)

      int segments = 36; // 원을 그리기 위한 분할 수 (10도씩 36번 이동)
      for (int i = 0; i < segments; ++i) {
          // 직선 이동 및 각속도 적용
          twist_msg.linear.x = linearVelocity;
          twist_msg.angular.z = angularVelocity;
          velocity_publisher->publish(twist_msg);

          // 이동 후 짧은 지연 시간 추가 (비동기 실행 중 다른 작업에 영향이 없도록)
          rclcpp::sleep_for(std::chrono::milliseconds(200)); // 지연 추가
      }

      // 멈춤
      twist_msg.linear.x = 0.0; // 다 그렸으면 멈추도록 처리
      twist_msg.angular.z = 0.0;
      velocity_publisher->publish(twist_msg);
  });

  // 스레드를 detach하여 메인 스레드와 독립적으로 동작하도록 설정
  drawThread.detach();
}