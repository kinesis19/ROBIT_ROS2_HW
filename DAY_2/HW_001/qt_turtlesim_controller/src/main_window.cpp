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

/* 2일차 과제1 리뷰
* Node 개념, 퍼블리셔, 리시버 개념은 어떤 느낌인지 이해가 된다고 판단됨
* 그러나, 다른 동기들에 비해 ROS2를 많이 다뤄보지 않았기에 사용방법과 서비스 부분에 대해서 더 자세하게 이해하고, "Node" 관련 구현 방식과 처리 방식을 세부적으로 더 공부해야할 필요성을 느낌
* TODO:
* 주말에 과제를 하면서 남은 시간에 ROS2 관련 개념을 Obsidian에 정리하거나 별도로 메모해서 공부하기
* ROS2 관련 자료는 ROS2 전도사님의 최신 자료와 velog에 포스팅 된 I ROBOT U, 구선생님의 자료를 보고 공부하기
*/

#include "../include/qt_turtlesim_controller/main_window.hpp"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindowDesign)
{
  ui->setupUi(this);

  QIcon icon("://ros-icon.png");
  this->setWindowIcon(icon);

  qnode = new QNode();

  QObject::connect(qnode, SIGNAL(rosShutDown()), this, SLOT(close()));

  // 버튼 클릭 시 거북이 제어를 위한 연결 (QPushButton 사용)
  connect(ui->btnMoveFront, &QPushButton::clicked, this, &MainWindow::onMoveFront);
  connect(ui->btnMoveBack, &QPushButton::clicked, this, &MainWindow::onMoveBack);
  connect(ui->btnTurnLeft, &QPushButton::clicked, this, &MainWindow::onTurnLeft);
  connect(ui->btnTurnRight, &QPushButton::clicked, this, &MainWindow::onTurnRight);

  // 배경색 제어를 위한 연결
  connect(ui->btnDeploy, &QPushButton::clicked, this, &MainWindow::onDeployBackgroundColor);

  // cmd_vel 업데이트를 위한 연결
  connect(qnode, SIGNAL(rosShutDown()), this, SLOT(close()));
  connect(qnode, SIGNAL(cmdVelUpdated(double, double, double, double, double, double)), this, SLOT(updateCmdVel(double, double, double, double, double, double)));

  // Pen 제어를 위한 연결
  connect(ui->btnDeploy_Pen, &QPushButton::clicked, this, &MainWindow::onDeployPenColor);

}

void MainWindow::closeEvent(QCloseEvent* event)
{
  QMainWindow::closeEvent(event);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::onMoveFront()
{
  qnode->moveTurtle(1.0, 0.0); // 직진 처리
}

void MainWindow::onMoveBack()
{
  qnode->moveTurtle(-1.0, 0.0); // 후진 처리
}

void MainWindow::onTurnLeft()
{
  qnode->moveTurtle(0.0, 1.0); // 좌회전 처리
}

void MainWindow::onTurnRight()
{
  qnode->moveTurtle(0.0, -1.0); // 우회전 처리
}

// 배경 제어 메서드
void MainWindow::onDeployBackgroundColor()
{
  int r = ui->lineEditBgR->text().toInt();
  int g = ui->lineEditBgG->text().toInt();
  int b = ui->lineEditBgB->text().toInt();
  qnode->setBackgroundColor(r, g, b);
}

// Pen 제어 메서드
void MainWindow::onDeployPenColor()
{
  int r = ui->lineEditBgR_Pen->text().toInt();
  int g = ui->lineEditBgG_Pen->text().toInt();
  int b = ui->lineEditBgB_Pen->text().toInt();
  int width = ui->lineEditWidth_Pen->text().toInt();
  qnode->setPenStyle(r, g, b, width);
}



// cmd_vel를 라벨에 업데이트 하는 메서드
void MainWindow::updateCmdVel(double linear_x, double linear_y, double linear_z, double angular_x, double angular_y, double angular_z)
{
    // "Linear X: 0.0 | Angular X: 0.0" 형식으로 업데이트
    ui->label_Linear_and_Angular_X->setText(QString("Linear X: %1 | Angular X: %2").arg(linear_x).arg(angular_x));
    ui->label_Linear_and_Angular_Y->setText(QString("Linear Y: %1 | Angular Y: %2").arg(linear_y).arg(angular_y));
    ui->label_Linear_and_Angular_Z->setText(QString("Linear Z: %1 | Angular Z: %2").arg(linear_z).arg(angular_z));
}
