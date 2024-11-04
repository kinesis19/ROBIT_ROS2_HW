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
  connect(qnode, &QNode::imageReceived, this, &MainWindow::updateImage);

  connect(qnode, SIGNAL(rosShutDown()), this, SLOT(close()));
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
void MainWindow::updateImage(const QPixmap& originalPixmap, const QPixmap& cannyPixmap)
{
  ui->labelDisplayUSBCamera_1->setPixmap(originalPixmap.scaled(ui->labelDisplayUSBCamera_1->size(), Qt::KeepAspectRatio)); // 원본 이미지
  // 2번부터는 Find Object, region of interest, Binary White ,BinaryOrange, Binary Lime 등으로 나눠서 적용해야 함.
  // 객체 인식 아직 구현 못 함.
  // 임시로 canny 이미지를 적용해 놓음.
  // Qt에서도 slider로 값 변경 구현을 하지 못 함. 객체 인식 이후 작업을 진행할 계획이였음
  ui->labelDisplayUSBCamera_2->setPixmap(cannyPixmap.scaled(ui->labelDisplayUSBCamera_2->size(), Qt::KeepAspectRatio)); // Canny 이미지
  ui->labelDisplayUSBCamera_3->setPixmap(cannyPixmap.scaled(ui->labelDisplayUSBCamera_3->size(), Qt::KeepAspectRatio)); // Canny 이미지
  ui->labelDisplayUSBCamera_4->setPixmap(cannyPixmap.scaled(ui->labelDisplayUSBCamera_4->size(), Qt::KeepAspectRatio)); // Canny 이미지
  ui->labelDisplayUSBCamera_5->setPixmap(cannyPixmap.scaled(ui->labelDisplayUSBCamera_5->size(), Qt::KeepAspectRatio)); // Canny 이미지
  ui->labelDisplayUSBCamera_6->setPixmap(cannyPixmap.scaled(ui->labelDisplayUSBCamera_6->size(), Qt::KeepAspectRatio)); // Canny 이미지
}
