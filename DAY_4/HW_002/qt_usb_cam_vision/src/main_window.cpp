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

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindowDesign)
{
  ui->setupUi(this);

  QIcon icon("://ros-icon.png");
  this->setWindowIcon(icon);

  qnode = new QNode();

  // QNode의 시그널과 MainWindow 슬롯 연결
  QObject::connect(qnode, &QNode::imageReceived, this, &MainWindow::updateImage);

  QObject::connect(qnode, SIGNAL(rosShutDown()), this, SLOT(close()));
}

void MainWindow::closeEvent(QCloseEvent* event)
{
  QMainWindow::closeEvent(event);
}

MainWindow::~MainWindow()
{
  delete ui;
}


// 이미지 업데이트 메서드
void MainWindow::updateImage(const QPixmap& pixmap)
{
  /* KeepAspectRatio: 이미지 원본 비율 유지
  */
  ui->labelDisplayUSBCamera_1->setPixmap(pixmap.scaled(ui->labelDisplayUSBCamera_1->size(), Qt::KeepAspectRatio)); // QLabel에 QPixmap을 설정
  ui->labelDisplayUSBCamera_2->setPixmap(pixmap.scaled(ui->labelDisplayUSBCamera_2->size(), Qt::KeepAspectRatio)); // QLabel에 QPixmap을 설정
  ui->labelDisplayUSBCamera_3->setPixmap(pixmap.scaled(ui->labelDisplayUSBCamera_3->size(), Qt::KeepAspectRatio)); // QLabel에 QPixmap을 설정
  ui->labelDisplayUSBCamera_4->setPixmap(pixmap.scaled(ui->labelDisplayUSBCamera_4->size(), Qt::KeepAspectRatio)); // QLabel에 QPixmap을 설정
  ui->labelDisplayUSBCamera_5->setPixmap(pixmap.scaled(ui->labelDisplayUSBCamera_5->size(), Qt::KeepAspectRatio)); // QLabel에 QPixmap을 설정
  ui->labelDisplayUSBCamera_6->setPixmap(pixmap.scaled(ui->labelDisplayUSBCamera_6->size(), Qt::KeepAspectRatio)); // QLabel에 QPixmap을 설정
}