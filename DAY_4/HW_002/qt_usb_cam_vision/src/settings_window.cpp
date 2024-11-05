#include "../include/qt_usb_cam_vision/settings_window.hpp"

SettingsWindow::SettingsWindow(QWidget* parent, rclcpp::Node::SharedPtr node)
    : QMainWindow(parent), ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);

    QIcon icon("://ros-icon.png");
    this->setWindowIcon(icon);
}

void SettingsWindow::closeEvent(QCloseEvent* event)
{
    QMainWindow::closeEvent(event);
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}
