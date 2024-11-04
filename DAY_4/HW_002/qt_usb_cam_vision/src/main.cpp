// #include <QApplication>
// #include <iostream>

// #include "../include/qt_usb_cam_vision/main_window.hpp"

// int main(int argc, char* argv[])
// {
//   QApplication a(argc, argv);
//   MainWindow w;
//   w.show();
//   return a.exec();
// }

#include <QApplication>
#include <iostream>
#include "rclcpp/rclcpp.hpp"

#include "../include/qt_usb_cam_vision/main_window.hpp"
#include "../include/qt_usb_cam_vision/settings_window.hpp"

int main(int argc, char* argv[])
{
    // ROS2와 Qt의 초기화를 각각 설정
    rclcpp::init(argc, argv);  // ROS2 노드를 위한 초기화
    auto node = rclcpp::Node::make_shared("qt_usb_cam_vision");  // 단일 ROS2 노드 생성
    QApplication a(argc, argv);  // Qt 애플리케이션 초기화

    MainWindow w(nullptr, node);  // MainWindow에 노드 전달
    SettingsWindow s(nullptr, node);  // SettingsWindow에 노드 전달

    w.show();
    s.show();

    auto ros_thread = std::thread([node]() {
        rclcpp::spin(node);  // 별도 스레드에서 ROS2 노드 스핀
    });

    int result = a.exec();
    rclcpp::shutdown();  // 애플리케이션 종료 시 ROS2도 종료
    ros_thread.join();   // 스레드 종료 대기

    return result;
}
