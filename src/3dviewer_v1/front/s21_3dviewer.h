#ifndef S21_3DVIEWER_H
#define S21_3DVIEWER_H
/*!
\file
\brief Заголовочный файл с описанием функций визуализации.

Данный файл содержит в себе определения
функций, используемых в проекте s21_3DViewer.
*/
#ifdef __cplusplus
extern "C" {
#endif

#include "../back/s21_3dviewer.h"
#ifdef __cplusplus
}
#endif

#include <QCloseEvent>
#include <QColorDialog>
#include <QCoreApplication>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include <QSettings>
#include <QTimer>
#include <QVariant>

#include "QtGifImage/qgifimage.h"
#include "s21_glwidget.h"
#include "s21_numlineedit.h"
#include "s21_sizes.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class s21_3DViewer;
}
QT_END_NAMESPACE

class s21_3DViewer : public QMainWindow {
  Q_OBJECT

 public:
  s21_3DViewer(QWidget *parent = nullptr);
  ~s21_3DViewer();
  s21_sizes *choise_size;

 protected:
  void closeEvent(QCloseEvent *event);

 private:
  Ui::s21_3DViewer *ui;
  QOpenGLWidget *s21_glwidget;

  QColor color_line = Qt::white, color_vertice = Qt::red,
         color_background = QColor(236, 236, 236, 0);
  QString file_name = "", path_project = "";

  char *str_file_name = (char *)"";

  int status = 0, gif_interval = 100;
  ;
  double translation_x = 0, translation_y = 0, translation_z = 0,
         rotating_x = 0, rotating_y = 0, rotating_z = 0, scaling_x = 100,
         scaling_y = 100, scaling_z = 100, scaling_all = 100;

  axis_values values = {0, 0, 0};
  vertexes vertex_arr = {0, 0};
  vertexes vertex_arr_start = {0, 0};
  polygons polygon_arr = {0, 0, 0};

  QGifImage *gif = NULL;
  QTimer *gif_timer = NULL;

 private slots:
  void actionOpenFile_triggered();

  void actionEdgeTypeSolid_triggered();
  void actionEdgeTypeDashed_triggered();
  void actionEdgeThickness_triggered();
  void actionEdgeColor_triggered();

  void actionVerticeTypeNone_triggered();
  void actionVerticeTypeCircle_triggered();
  void actionVerticeTypeSquare_triggered();
  void actionVerticeSize_triggered();
  void actionVerticeColor_triggered();

  void actionBackground_triggered();

  void on_radioButton_parallel_toggled(bool checked);
  void on_radioButton_central_toggled(bool checked);

  void move_x();
  void move_y();
  void move_z();

  void rotation_x();
  void rotation_y();
  void rotation_z();

  void zoom_x();
  void zoom_y();
  void zoom_z();
  void zoom_all();

  void location_change(double change_x, double change_y, double change_z,
                       axis_values *coordinate, transformation_t type);
  void model_transformation();

  void on_horizontalScrollBar_translation_x_valueChanged(int value);
  void on_horizontalScrollBar_translation_y_valueChanged(int value);
  void on_horizontalScrollBar_translation_z_valueChanged(int value);

  void on_dial_rotating_x_valueChanged(int value);
  void on_dial_rotating_z_valueChanged(int value);
  void on_dial_rotating_y_valueChanged(int value);

  void on_horizontalSlider_scaling_x_valueChanged(int value);
  void on_horizontalSlider_scaling_y_valueChanged(int value);
  void on_horizontalSlider_scaling_z_valueChanged(int value);
  void on_horizontalSlider_scaling_valueChanged(int value);

  void on_checkBox_translating_toggled(bool checked);
  void on_checkBox_rotating_toggled(bool checked);
  void on_checkBox_scaling_toggled(bool checked);

  void first_open();
  void file_open();
  void save_bmp();
  void save_jpeg();
  void save_gif();
  void recording_gif();
  void finish_recording();

  void set_all_default();
  void set_translation_default();
  void set_rotating_default();
  void set_scaling_default();

  void write_settings();
  void read_settings();
};

#endif  // S21_3DVIEWER_H
