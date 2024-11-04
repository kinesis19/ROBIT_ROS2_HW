/**
 * @file /src/main_window.cpp
 *
 * @brief Implementation for the qt gui.
 *
 * @date August 2024
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include "../include/qt_usb_cam_vision/main_window.hpp"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindowDesign), qnode(new QNode())
{
  ui->setupUi(this);

  QIcon icon("://ros-icon.png");
  this->setWindowIcon(icon);

  // QNode의 시그널과 MainWindow의 슬롯 연결
  connect(qnode, &QNode::imageReceived, this, [this](const QPixmap& pixmap) {
      ui->labelDisplayImg_1->setPixmap(pixmap.scaled(ui->labelDisplayImg_1->size(), Qt::KeepAspectRatio));
  });
  connect(qnode, &QNode::rosShutDown, this, &MainWindow::close);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
  QMainWindow::closeEvent(event);
}

MainWindow::~MainWindow()
{
  delete ui;
  delete qnode;
}
