/**
 * @file /include/qt_usb_camera_viewer/main_window.hpp
 *
 * @brief Qt based gui for %(package)s.
 *
 * @date August 2024
 **/

#ifndef qt_usb_camera_viewer_MAIN_WINDOW_H
#define qt_usb_camera_viewer_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QMainWindow>
#include "QIcon"
#include "qnode.hpp"
#include "ui_mainwindow.h"

/*****************************************************************************
** Interface [MainWindow]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */
class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();
  QNode* qnode;

private slots:
  void updateImage(const QPixmap& pixmap);  // 이미지 업데이트 메서드

private:
  Ui::MainWindowDesign* ui;
  void closeEvent(QCloseEvent* event);
};

#endif  // qt_usb_camera_viewer_MAIN_WINDOW_H
