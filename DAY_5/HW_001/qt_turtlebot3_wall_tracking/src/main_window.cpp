#include "../include/qt_turtlebot3_wall_tracking/main_window.hpp"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindowDesign)
{
  ui->setupUi(this);

  QIcon icon("://ros-icon.png");
  this->setWindowIcon(icon);

  qnode = new QNode();

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
  
}

// Stop 버튼 눌렀을 때
void MainWindow::onStopBtnClicked()
{
  
}

// Dist Update 버튼 눌렀을 때
void MainWindow::onUpdateDistBtnClicked()
{

}

// Turtlebot3 Update 버튼 눌렀을 때
void MainWindow::onUpdateCmdVelBtnClicked()
{

}