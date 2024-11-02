#include "turtlesim_draw_shape.hpp"
#include <iostream>

TurtlesimDrawShape::TurtlesimDrawShape() : Node("turtlesim_draw_shape") {
    velocity_publisher = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
    // SetPen 서비스 클라이언트 초기화
    set_pen_client_ = this->create_client<turtlesim::srv::SetPen>("/turtle1/set_pen");
}

// Pen 설정 메서드 (1일차 과제1의 모드와 중복 되는 부분이므로 적용함)
void TurtlesimDrawShape::setPenStyle() {
    auto request = std::make_shared<turtlesim::srv::SetPen::Request>();

    int r, g, b;
    int width;

    std::cout << "Pen Color를 0부터-255 사이로 입력해라 (r g b):";
    std::cin >> r >> g >> b;

    // 입력된 color 값이 정해진 범위 내에 있는지 검사하기
    request->r = std::max(0, std::min(r, 255));
    request->g = std::max(0, std::min(g, 255));
    request->b = std::max(0, std::min(b, 255));

    std::cout << "Pen 두께를 입력해라 (0-10): ";
    std::cin >> width;
    // Pen의 width 제한
    request->width = std::max(0, std::min(width, 10));
    request->off = 0;

    // 비동기 서비스 요청 보내기
    auto future = set_pen_client_->async_send_request(request);
}


// 삼각형 그리는 신호 받았을 때 거북이가 삼각형을 그림
void TurtlesimDrawShape::drawTriangle(double sideLength) {
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
void TurtlesimDrawShape::drawQuadrilateral(double sideLength) {
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

// 원그리기
void TurtlesimDrawShape::drawCircle(double diameterLength) {
    auto twist_msg = geometry_msgs::msg::Twist();

    // 원을 그리기 위한 설정
    double radius = diameterLength / 2.0;              // 반지름 계산
    double linearVelocity = 1.0;                       // 선형 속도 설정
    double angularVelocity = linearVelocity / radius;  // 각속도 설정 (v = r * ω)

    // 원을 그리기 위해 직선으로 나눠서 이동 시킴
    // angular나 직선 카운트를 while로 처리해도 깔끔하게 될 듯
    int segments = 16 * diameterLength;
    
    for (int i = 0; i < segments; i++) {
        // 각 구간마다 직선 이동과 회전을 수행
        twist_msg.linear.x = linearVelocity;
        twist_msg.angular.z = angularVelocity;

        velocity_publisher->publish(twist_msg);
        rclcpp::sleep_for(std::chrono::milliseconds(200)); // 각 구간 이동을 위한 시간(딜레이 없으면 바로바로 처리 되서 의도한 대로 원이 안 그려지는 현상이 발생 됨)
    }

    // 멈춤
    twist_msg.linear.x = 0.0; // 다 그렸으면 멈추도록 처리
    twist_msg.angular.z = 0.0;
    velocity_publisher->publish(twist_msg);
}