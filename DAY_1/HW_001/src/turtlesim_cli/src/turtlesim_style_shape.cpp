#include "turtlesim_style_shape.hpp"

TurtlesimStyleShape::TurtlesimStyleShape() : Node("turtle_style_shape") {
    // Kill과 Spawn을 위한 클라이언트 초기화
    kill_client_ = this->create_client<turtlesim::srv::Kill>("/kill");
    spawn_client_ = this->create_client<turtlesim::srv::Spawn>("/spawn");

    current_turtle_name_ = "turtle1"; // 최초 거북이 이름
}


void TurtlesimStyleShape::setTurtleShape() {
    RCLCPP_INFO(this->get_logger(), "현재 거북이 이름: %s", current_turtle_name_.c_str());
    std::cout << "\n거북이 모양을 선택해라:\n1: leonardo\n2: raffaello\n3: michelangelo\n4: donatello\n";
    int choice;
    std::cin >> choice;

    std::string turtle_name;
    switch (choice) {
        case 1: turtle_name = "leonardo"; break;
        case 2: turtle_name = "raffaello"; break;
        case 3: turtle_name = "michelangelo"; break;
        case 4: turtle_name = "donatello"; break;
        default: 
            std::cout << "올바르지 않은 선택이다.\n";
            return;
    }
    
    auto kill_request = std::make_shared<turtlesim::srv::Kill::Request>();
    kill_request->name = current_turtle_name_;

    if (kill_client_->wait_for_service(std::chrono::seconds(1))) {
        auto kill_result = kill_client_->async_send_request(kill_request);
        if (rclcpp::spin_until_future_complete(this->shared_from_this(), kill_result) == rclcpp::FutureReturnCode::SUCCESS) {
            std::cout << "기존 거북이가 제거되었다.\n";
            current_turtle_name_.clear();
        } else {
            std::cout << "기존 거북이 제거 실패 또는 존재하지 않음.\n";
        }
    }

    rclcpp::sleep_for(std::chrono::milliseconds(500));

    // 새로운 거북이 생성
    auto spawn_request = std::make_shared<turtlesim::srv::Spawn::Request>();
    spawn_request->x = 5.5;        // 화면 중앙 X 좌표
    spawn_request->y = 5.5;        // 화면 중앙 Y 좌표
    spawn_request->theta = 0.0;    // 초기 방향
    spawn_request->name = turtle_name;

    if (spawn_client_->wait_for_service(std::chrono::seconds(5))) {
        auto future_spawn = spawn_client_->async_send_request(spawn_request);

        if (rclcpp::spin_until_future_complete(this->shared_from_this(), future_spawn) == rclcpp::FutureReturnCode::SUCCESS) {
            std::cout << turtle_name << " 모양의 거북이 생성 완료.\n";
            current_turtle_name_ = turtle_name;
        } else {
            std::cout << "거북이 생성 실패.\n";
        }
    }
}
