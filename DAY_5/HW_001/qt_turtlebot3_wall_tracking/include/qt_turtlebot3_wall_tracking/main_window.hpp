#ifndef qt_turtlebot3_wall_tracking_MAIN_WINDOW_H
#define qt_turtlebot3_wall_tracking_MAIN_WINDOW_H

#include <QMainWindow>
#include "QIcon"
#include "qnode.hpp"
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();
  QNode* qnode;

private slots:
    void onStartBtnClicked();
    void onStopBtnClicked();
    void onUpdateDistBtnClicked();
    void onUpdateCmdVelBtnClicked();

private:
  Ui::MainWindowDesign* ui;
  void closeEvent(QCloseEvent* event);
};

#endif  // qt_turtlebot3_wall_tracking_MAIN_WINDOW_H
