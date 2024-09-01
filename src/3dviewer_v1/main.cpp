#include <QApplication>

#include "front/s21_3dviewer.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QLocale::setDefault(QLocale::c());

  s21_3DViewer w;
  w.show();
  return a.exec();
}
