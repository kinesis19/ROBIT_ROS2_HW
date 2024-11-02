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

#include "../include/qt_talker_and_listener/main_window.hpp"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindowDesign)
{
  ui->setupUi(this);

  QIcon icon("://ros-icon.png");
  this->setWindowIcon(icon);

  qnode = new QNode();

  // 버튼 클릭 시 메시지 퍼블리시
  connect(ui->btn_Publish, &QPushButton::clicked, this, &MainWindow::onPublishButtonClicked);
  
  // Listener의 새로운 메시지를 라벨에 업데이트
  connect(qnode, &QNode::newMessageReceived, this, &MainWindow::updateLabel);

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

// Publish 버튼 눌렀을 때 퍼블리쉬하는 메서드
void MainWindow::onPublishButtonClicked()
{
    // 입력된 텍스트를 QNode를 통해 퍼블리쉬
    QString text = ui->lineEdit_Text->text();
    qnode->publishMessage(text.toStdString());
}

// label 업데이트 메서드
void MainWindow::updateLabel(const QString &message, int count)
{
  ui->labelSubscribe->setText(QString("\"%1\", \"%2\"").arg(message).arg(count)); // 메시지와 카운트를 동시에 출력함
}
