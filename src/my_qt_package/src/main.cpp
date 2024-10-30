#include <QApplication>
#include <iostream>

#include "../include/my_qt_package/main_window.hpp"

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}
