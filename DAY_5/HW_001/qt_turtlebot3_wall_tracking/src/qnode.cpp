#include "../include/qt_turtlebot3_wall_tracking/qnode.hpp"

// 생성자에서 초기화함
QNode::QNode() : target_distance_(0.55), current_distance_front_(0.0), current_distance_back_(0.0), current_distance_left_(0.0), current_distance_right_(0.0), is_tracking_(false)
{
  int argc = 0;
  char** argv = NULL;
  rclcpp::init(argc, argv);
  node = rclcpp::Node::make_shared("qt_turtlebot3_wall_tracking");

  // distance 파라미터 설정
  node->declare_parameter("wall_distance", target_distance_);

  // /scan 토픽 서브스크라이버 초기화
  scan_subscriber_ = node->create_subscription<sensor_msgs::msg::LaserScan>("/scan", 10, std::bind(&QNode::scanCallback, this, std::placeholders::_1));

  cmd_vel_publisher_ = node->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);

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


// /scan 토픽 콜백 메서드
void QNode::scanCallback(const sensor_msgs::msg::LaserScan::SharedPtr msg)
{
  // 정면 방향의 거리 데이터 가져오기
  /* msg->ranges: 라이다가 감지한 거리 값의 저장된 값들
  * 정면: msg->ranges[0]
  * 오른쪽: msg->ranges[msg->ranges.size() * 3 / 4]
  * 왼쪽: msg->ranges[msg->ranges.size() / 4]
  * 뒤쪽: msg->ranges[msg->ranges.size() / 2]
  * 근데, 라이다로 감지할 수 있는 범위에 따라서 값이 바뀐다고 함. 그래서 감지하기 위해서는 인덱스에 상수를 참조하는 것이 아니라, 전체 사이즈에서 절반의 값을 가져오는 것으로 이해함.
  */
  // int centerIndex = msg->ranges.size() / 2; // 뒤쪽
  // int centerIndex = msg->ranges.size() / 4; // 왼쪽
  current_distance_front_ = msg->ranges[0];
  current_distance_back_ = msg->ranges[msg->ranges.size() / 2];
  current_distance_left_ = msg->ranges[msg->ranges.size() / 4];
  current_distance_right_ = msg->ranges[msg->ranges.size() * 3 / 4];

  emit updateDistanceLabel(current_distance_front_, current_distance_back_, current_distance_left_, current_distance_right_);
}

// Distance Parameter 설정 메서드
void QNode::setDistanceParameter(float distance)
{
  node->set_parameter(rclcpp::Parameter("wall_distance", distance));

  target_distance_ = distance; // 목표 거리
}

void QNode::setCmdVelParameter(float linear_x, float angular_z)
{
    // Twist 메시지 생성 및 값 설정
    geometry_msgs::msg::Twist cmd_vel_msg;
    cmd_vel_msg.linear.x = linear_x;
    cmd_vel_msg.angular.z = angular_z;

    // /cmd_vel 토픽으로 메시지 퍼블리시
    cmd_vel_publisher_->publish(cmd_vel_msg);
}

void QNode::startAutoTrackingforWall(float linear_x, float angular_z)
{
  
  // 파라미터에서에서 값이 있으면 가져와서 target_distance_에 할당하기
  // 없다면 생성자에서 초기화 한 값으로 사용됨
  rclcpp::Parameter distance;
  if (node->get_parameter("wall_distance", distance)) {
    target_distance_ = distance.as_double();
  }

  linear_velocity_ = linear_x;
  angular_velocity_ = angular_z;
  is_tracking_ = true;

  // 타이머 부분은 레퍼런스와 GPT를 참고함.
  // 버튼 한 번 클릭 했을 때, 그 이후로 계속 반복 시켜야 하는데, while() 문 사용하면 프로세스 관련 중단 -> 주도권 문제로 이해함 
  // 타이머 사용하거나 쓰레드 사용하거나. -> 타이머 사용 선택
  // 타이머 초기화 및 시작 (100ms 간격으로 콜백 실행)
  wall_tracking_timer_ = node->create_wall_timer(
    std::chrono::milliseconds(100),
    std::bind(&QNode::autoTrackingCallback, this)
  );
}

// Auto Wall Tracking 중지 메서드
void QNode::stopAutoTracking()
{
    is_tracking_ = false;
    if (wall_tracking_timer_) {
      geometry_msgs::msg::Twist cmd_vel_msg;
      cmd_vel_msg.linear.x = 0;
      cmd_vel_msg.angular.z = 0;

      // /cmd_vel 토픽으로 메시지 퍼블리시
      cmd_vel_publisher_->publish(cmd_vel_msg);
      wall_tracking_timer_->cancel();  // 타이머 중지
    }
}

// 자율 주행 타이머 콜백 함수 (오른쪽 벽타기)
void QNode::autoTrackingCallback()
{
  if (!is_tracking_) return;  // 타이머가 중지되었으면 실행 중지

  float tolerance = target_distance_ * 0.1;  // 오차범위

  geometry_msgs::msg::Twist cmd_vel_msg;

  if (current_distance_right_ > target_distance_ + tolerance) {
    cmd_vel_msg.angular.z = -std::abs(angular_velocity_); // 우회전
    cmd_vel_msg.linear.x = 0.0;
    if(current_distance_front_ < 2.0){
      cmd_vel_msg.angular.z = std::abs(angular_velocity_); // 좌회전
      cmd_vel_msg.linear.x = linear_velocity_; // 직진
    }
  } else if (current_distance_right_ < target_distance_ - tolerance) {
    cmd_vel_msg.angular.z = std::abs(angular_velocity_); // 좌회전
    cmd_vel_msg.linear.x = 0.0;
  } else {
    cmd_vel_msg.linear.x = linear_velocity_; // 직진
    cmd_vel_msg.angular.z = 0.0; // 회전X
  }

  // 코너 감지
  if (current_distance_front_ < target_distance_) { // 코너 거리 기준 조정
    cmd_vel_msg.angular.z = std::abs(angular_velocity_); // 좌회전
    cmd_vel_msg.linear.x = 0.0;
  }

  cmd_vel_publisher_->publish(cmd_vel_msg);
}