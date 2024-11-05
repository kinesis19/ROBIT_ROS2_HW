#ifndef QT_USB_CAM_VISION_SETTINGS_WINDOW_H
#define QT_USB_CAM_VISION_SETTINGS_WINDOW_H

#include <QMainWindow>
#include <QIcon>
#include "ui_settingswindow.h"
#include "qnode.hpp"

class SettingsWindow : public QMainWindow
{
  Q_OBJECT

public:
  SettingsWindow(QWidget* parent = nullptr, rclcpp::Node::SharedPtr node = nullptr);
  ~SettingsWindow();

private:
  Ui::SettingsWindow* ui;
  void closeEvent(QCloseEvent* event);
};

#endif  // QT_USB_CAM_VISION_SETTINGS_WINDOW_H

