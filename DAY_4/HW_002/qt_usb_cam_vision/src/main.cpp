#include <QApplication>
#include <iostream>
#include "rclcpp/rclcpp.hpp"

#include "../include/qt_usb_cam_vision/main_window.hpp"
#include "../include/qt_usb_cam_vision/settings_window.hpp"

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    QApplication a(argc, argv);

    MainWindow w(nullptr);
    SettingsWindow s;

    w.show();
    s.show();

    int result = a.exec();

    rclcpp::shutdown();
    return result;
}
