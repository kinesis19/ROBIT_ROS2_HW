/**
 * @file /include/qt_turtlesim_controller/main_window.hpp
 *
 * @brief Qt based gui for %(package)s.
 *
 * @date August 2024
 **/

#ifndef qt_turtlesim_controller_MAIN_WINDOW_H
#define qt_turtlesim_controller_MAIN_WINDOW_H

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

private:
  Ui::MainWindowDesign* ui;
  void closeEvent(QCloseEvent* event);
  
private slots:
  void onMoveFront();
  void onMoveBack();
  void onTurnLeft();
  void onTurnRight();

  void onDeployBackgroundColor();
  void onDeployPenColor();

  // 삼각형 그리기
  void onDrawTriangle();
  void onDrawQuadrilateral();
  void onDrawCircle();

  void updateCmdVel(double linear_x, double linear_y, double linear_z, double angular_x, double angular_y, double angular_z);
};



#endif  // qt_turtlesim_controller_MAIN_WINDOW_H
