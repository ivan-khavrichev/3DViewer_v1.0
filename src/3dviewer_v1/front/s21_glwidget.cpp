#include "s21_glwidget.h"
/*!
\file
\brief Исходный файл с реализацией функций отрисовки 3D-модели.

Данный файл содержит в себе реализацию
функций, используемых в проекте s21_3DViewer.
*/
s21_glwidget::s21_glwidget(QWidget *parent) : QOpenGLWidget(parent) {
  update();
}

void s21_glwidget::paintGL() {
  polygon *polyp = polygon_arr_paint.polygon;
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if (project_parallel == true) {
    glOrtho(-1, 1, -1, 1, -1, 1);
    glTranslatef(0, 0, 0);
  } else {
    glFrustum(-1, 1, -1, 1, 2, 6);
    glTranslatef(0, 0, -3);
  }

  glClearColor(back_color.redF(), back_color.greenF(), back_color.blueF(), 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (point_draw == true) {
    if (point_circle == true) {
      glEnable(GL_POINT_SMOOTH);
    } else {
      glDisable(GL_POINT_SMOOTH);
    }

    glPointSize(point_size);
    glColor3d(vertice_color.redF(), vertice_color.greenF(),
              vertice_color.blueF());

    for (int i = 0; i < polygon_arr_paint.amount_poly; i++, polyp++) {
      vertex_in_poly = 0;
      for (int j = 0; j < polygon_arr_paint.polygon->amount_points; j++) {
        vertex_in_poly = *(polyp->points + j);
        glBegin(GL_POINTS);
        vertex *pp = vertex_arr_paint.vert;
        pp += vertex_in_poly;
        glVertex3d(pp->x, pp->y, pp->z);
      }
      glEnd();
    }
  }

  polyp = polygon_arr_paint.polygon;

  if (line_dashed == true) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00ff);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }

  glLineWidth(line_size);
  glColor3d(line_color.redF(), line_color.greenF(), line_color.blueF());

  for (int i = 1; i <= polygon_arr_paint.amount_poly; i++, polyp++) {
    vertex_in_poly = 0;
    for (int j = 0; j < polygon_arr_paint.polygon->amount_points; j++) {
      vertex_in_poly = *(polyp->points + j);
      glBegin(GL_LINE_LOOP);
      vertex *pp = vertex_arr_paint.vert;
      pp += vertex_in_poly;
      glVertex3d(pp->x, pp->y, pp->z);
    }
    glEnd();
  }
}
