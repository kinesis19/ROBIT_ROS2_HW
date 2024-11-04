/**
 * @file /include/qt_usb_cam_vision/settings_window.hpp
 *
 * @brief Qt based gui for %(package)s.
 *
 * @date August 2024
 **/

#ifndef qt_usb_cam_vision_SETTINGS_WINDOW_H
#define qt_usb_cam_vision_SETTINGS_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QMainWindow>
#include "QIcon"
#include "qnode.hpp"
#include "ui_settingswindow.h"

/*****************************************************************************
** Interface [SettingsWindow]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */
// class SettingsWindow : public QMainWindow
// {
//   Q_OBJECT

// public:
//   SettingsWindow(QWidget* parent = nullptr);
//   ~SettingsWindow();
//   QNode* qnode;

// private:
//   Ui::SettingsWindow* ui;
//   void closeEvent(QCloseEvent* event);
// };
class SettingsWindow : public QMainWindow
{
  Q_OBJECT

public:
  SettingsWindow(QWidget* parent = nullptr, rclcpp::Node::SharedPtr node = nullptr);
  ~SettingsWindow();

private:
  Ui::SettingsWindow* ui;
  rclcpp::Node::SharedPtr node;  // 외부에서 받은 ROS2 노드 포인터
  void closeEvent(QCloseEvent* event);
};

#endif  // qt_usb_cam_vision_SETTINGS_WINDOW_H
