#include <QApplication>

#include "myopenglwidget.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QApplication::setStyle("Fusion");  //Стиль отрисовки форм
  MainWindow w;
  w.show();
  return a.exec();
}
