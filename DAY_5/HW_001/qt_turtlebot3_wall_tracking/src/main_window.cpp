#include "../include/qt_turtlebot3_wall_tracking/main_window.hpp"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindowDesign)
{
  ui->setupUi(this);

  QIcon icon("://ros-icon.png");
  this->setWindowIcon(icon);

  qnode = new QNode();

  connect(qnode, &QNode::updateDistanceLabel, this, &MainWindow::setDistanceLabel);

  connect(ui->bntStart, &QPushButton::clicked, this, &MainWindow::onStartBtnClicked);
  connect(ui->bntStop, &QPushButton::clicked, this, &MainWindow::onStopBtnClicked);

  connect(ui->btnUpdateDist, &QPushButton::clicked, this, &MainWindow::onUpdateDistBtnClicked);
  connect(ui->btnUpdateCmdVel, &QPushButton::clicked, this, &MainWindow::onUpdateCmdVelBtnClicked);

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

// Start 버튼 눌렀을 때
void MainWindow::onStartBtnClicked()
{
  // distance = ui->spinBoxDistSet->value();
  linear_x = ui->spinBoxLinearX->value();
  angular_z = ui->spinBoxAngularZ->value();

  qnode->startAutoTrackingforWall(linear_x, angular_z);
}

// Stop 버튼 눌렀을 때
void MainWindow::onStopBtnClicked()
{
  qnode->stopAutoTracking();
}

// Dist Update 버튼 눌렀을 때
void MainWindow::onUpdateDistBtnClicked()
{
  // 디버깅용이기에 주석처리함
  // // spinBoxDistSet에서 값을 읽어와서 distance 변수에 저장
  distance = ui->spinBoxDistSet->value();
  
  // // QNode에 distance 값을 전달하여 파라미터로 설정
  qnode->setDistanceParameter(distance);
}

// Turtlebot3 Update 버튼 눌렀을 때
void MainWindow::onUpdateCmdVelBtnClicked()
{
  // 디버깅용이기에 주석처리함
  // // spinBoxLinearX와 spinBoxAngularZ의 값을 읽어온다
  // linear_x = ui->spinBoxLinearX->value();
  // angular_z = ui->spinBoxAngularZ->value();

  // // QNode에 linear.x와 angular.z 값을 전달하여 퍼블리시
  // qnode->setCmdVelParameter(linear_x, angular_z);

}

void MainWindow::setDistanceLabel(float distFront, float distBack, float distLeft, float distRight)
{
  ui->labelDistFrontNow->setText(QString::number(distFront, 'f', 2)); // 소수점 2자리로 표시
  ui->labelDistBackNow->setText(QString::number(distBack, 'f', 2)); 
  ui->labelDistLeftNow->setText(QString::number(distLeft, 'f', 2)); 
  ui->labelDistRightNow->setText(QString::number(distRight, 'f', 2)); 
}