#ifndef S21_GLWIDJET_H
#define S21_GLWIDJET_H
/*!
\file
\brief Исходный файл с объявлением функций отрисовки 3D-модели.

Данный файл содержит в себе объявление
функций, используемых в проекте s21_3DViewer.
*/
#define GL_SILENCE_DEPRECATION

#include <QOpenGLWidget>

#include "s21_3dviewer.h"

class s21_glwidget : public QOpenGLWidget {
  Q_OBJECT

 public:
  s21_glwidget(QWidget *parent = nullptr);

  int vertex_in_poly = 0, line_dashed = false, point_draw = false,
      point_circle = true, point_size = 2, line_size = 3,
      project_parallel = false;

  QColor back_color = QColor(236, 236, 236, 0), line_color = Qt::black,
         vertice_color = Qt::red;

  vertexes vertex_arr_paint;
  polygons polygon_arr_paint;

  void paintGL();

 private:
};

#endif  // S21_GLWIDJET_H
