/**
 * @file /include/qt_usb_cam_vision/main_window.hpp
 *
 * @brief Qt based gui for %(package)s.
 *
 * @date August 2024
 **/

#ifndef QT_USB_CAM_VISION_MAIN_WINDOW_H
#define QT_USB_CAM_VISION_MAIN_WINDOW_H

#include <QMainWindow>
#include <QIcon>
#include "ui_mainwindow.h"
#include "qnode.hpp"

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget* parent);
  ~MainWindow();

private:
  Ui::MainWindowDesign* ui;
  QNode* qnode;
  void closeEvent(QCloseEvent* event);
};

#endif  // QT_USB_CAM_VISION_MAIN_WINDOW_H
