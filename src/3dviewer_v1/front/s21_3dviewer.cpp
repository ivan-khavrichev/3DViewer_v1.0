#include "s21_3dviewer.h"

#include "./ui_s21_3dviewer.h"
#include "s21_glwidget.h"
#include "s21_sizes.h"
/*!
\file
\brief Исходный файл с реализацией функций визуализации.

Данный файл содержит в себе реализацию
функций, используемых в проекте s21_3DViewer.
*/
s21_3DViewer::s21_3DViewer(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::s21_3DViewer) {
  ui->setupUi(this);

  choise_size = new s21_sizes();

  connect(ui->lineEdit_scaling_x, SIGNAL(textChanged(QString)), this,
          SLOT(zoom_x()));
  connect(ui->lineEdit_scaling_y, SIGNAL(textChanged(QString)), this,
          SLOT(zoom_y()));
  connect(ui->lineEdit_scaling_z, SIGNAL(textChanged(QString)), this,
          SLOT(zoom_z()));
  connect(ui->lineEdit_scaling, SIGNAL(textChanged(QString)), this,
          SLOT(zoom_all()));

  connect(ui->lineEdit_rotating_x, SIGNAL(textChanged(QString)), this,
          SLOT(rotation_x()));
  connect(ui->lineEdit_rotating_y, SIGNAL(textChanged(QString)), this,
          SLOT(rotation_y()));
  connect(ui->lineEdit_rotating_z, SIGNAL(textChanged(QString)), this,
          SLOT(rotation_z()));

  connect(ui->lineEdit_translating_x, SIGNAL(textChanged(QString)), this,
          SLOT(move_x()));
  connect(ui->lineEdit_translating_y, SIGNAL(textChanged(QString)), this,
          SLOT(move_y()));
  connect(ui->lineEdit_translating_z, SIGNAL(textChanged(QString)), this,
          SLOT(move_z()));

  connect(ui->actionOpenFile, SIGNAL(triggered()), this,
          SLOT(actionOpenFile_triggered()));
  connect(ui->actionFormat_bmp, SIGNAL(triggered()), this, SLOT(save_bmp()));
  connect(ui->pushButton_save_bmp, SIGNAL(clicked()), this, SLOT(save_bmp()));
  connect(ui->actionFormat_jpeg, SIGNAL(triggered()), this, SLOT(save_jpeg()));
  connect(ui->pushButton_save_jpeg, SIGNAL(clicked()), this, SLOT(save_jpeg()));
  connect(ui->actionFormat_gif, SIGNAL(triggered()), this, SLOT(save_gif()));
  connect(ui->pushButton_save_gif, SIGNAL(clicked()), this, SLOT(save_gif()));

  connect(ui->actionEdgeTypeSolid, SIGNAL(triggered()), this,
          SLOT(actionEdgeTypeSolid_triggered()));
  connect(ui->actionEdgeTypeDashed, SIGNAL(triggered()), this,
          SLOT(actionEdgeTypeDashed_triggered()));
  connect(ui->actionEdgeThickness, SIGNAL(triggered()), this,
          SLOT(actionEdgeThickness_triggered()));
  connect(ui->actionEdgeColor, SIGNAL(triggered()), this,
          SLOT(actionEdgeColor_triggered()));

  connect(ui->actionVerticeTypeNone, SIGNAL(triggered()), this,
          SLOT(actionVerticeTypeNone_triggered()));
  connect(ui->actionVerticeTypeCircle, SIGNAL(triggered()), this,
          SLOT(actionVerticeTypeCircle_triggered()));
  connect(ui->actionVerticeTypeSquare, SIGNAL(triggered()), this,
          SLOT(actionVerticeTypeSquare_triggered()));
  connect(ui->actionVerticeSize, SIGNAL(triggered()), this,
          SLOT(actionVerticeSize_triggered()));
  connect(ui->actionVerticeColor, SIGNAL(triggered()), this,
          SLOT(actionVerticeColor_triggered()));

  connect(ui->actionBackground, SIGNAL(triggered()), this,
          SLOT(actionBackground_triggered()));

  read_settings();
}

s21_3DViewer::~s21_3DViewer() { delete ui; }

void s21_3DViewer::actionOpenFile_triggered() {
  file_name = QFileDialog::getOpenFileName(this, "Открыть файл",
                                           path_project.append("src/models/"),
                                           "Files (*.obj)");
  file_open();
}

void s21_3DViewer::actionEdgeTypeSolid_triggered() {
  ui->openGLWidget->line_dashed = false;
  ui->openGLWidget->update();
}

void s21_3DViewer::actionEdgeTypeDashed_triggered() {
  ui->openGLWidget->line_dashed = true;
  ui->openGLWidget->update();
}

void s21_3DViewer::actionEdgeThickness_triggered() {
  choise_size->setModal(true);
  choise_size->setWindowTitle("Sizes");
  if (choise_size->exec() == QDialog::Accepted) {
    ui->openGLWidget->line_size = choise_size->size;
  }
}

void s21_3DViewer::actionEdgeColor_triggered() {
  color_line = QColorDialog::getColor();
  if (color_line.isValid()) {
    ui->openGLWidget->line_color = color_line;
  }
  ui->openGLWidget->update();
}

void s21_3DViewer::actionVerticeTypeNone_triggered() {
  ui->openGLWidget->point_draw = false;
  ui->openGLWidget->update();
}

void s21_3DViewer::actionVerticeTypeCircle_triggered() {
  ui->openGLWidget->point_draw = true;
  ui->openGLWidget->point_circle = true;
  ui->openGLWidget->update();
}

void s21_3DViewer::actionVerticeTypeSquare_triggered() {
  ui->openGLWidget->point_draw = true;
  ui->openGLWidget->point_circle = false;
  ui->openGLWidget->update();
}

void s21_3DViewer::actionVerticeSize_triggered() {
  choise_size->setModal(true);
  choise_size->setWindowTitle("Sizes");
  if (choise_size->exec() == QDialog::Accepted) {
    ui->openGLWidget->point_size = choise_size->size;
  }
}

void s21_3DViewer::actionVerticeColor_triggered() {
  color_vertice = QColorDialog::getColor();
  if (color_vertice.isValid()) {
    ui->openGLWidget->vertice_color = color_vertice;
  }
  ui->openGLWidget->update();
}

void s21_3DViewer::actionBackground_triggered() {
  color_background = QColorDialog::getColor();
  if (color_background.isValid()) {
    ui->openGLWidget->back_color = color_background;
  }
  ui->openGLWidget->update();
}

void s21_3DViewer::on_radioButton_parallel_toggled(bool checked) {
  ui->openGLWidget->project_parallel = checked;
  ui->openGLWidget->update();
}

void s21_3DViewer::on_radioButton_central_toggled(bool checked) {
  ui->openGLWidget->project_parallel = -1 * checked;
  ui->openGLWidget->update();
}

void s21_3DViewer::move_x() {
  translation_x = ui->lineEdit_translating_x->text().toDouble();
  model_transformation();
}

void s21_3DViewer::on_horizontalScrollBar_translation_x_valueChanged(
    int value) {
  translation_x = value;
  model_transformation();
}

void s21_3DViewer::move_y() {
  translation_y = ui->lineEdit_translating_y->text().toDouble();
  model_transformation();
}

void s21_3DViewer::on_horizontalScrollBar_translation_y_valueChanged(
    int value) {
  translation_y = value;
  model_transformation();
}

void s21_3DViewer::move_z() {
  translation_z = ui->lineEdit_translating_z->text().toDouble();
  model_transformation();
}

void s21_3DViewer::on_horizontalScrollBar_translation_z_valueChanged(
    int value) {
  translation_z = value;
  model_transformation();
}

void s21_3DViewer::rotation_x() {
  rotating_x = ui->lineEdit_rotating_x->text().toDouble() * 100;
  model_transformation();
}

void s21_3DViewer::on_dial_rotating_x_valueChanged(int value) {
  rotating_x = -100 * value;
  model_transformation();
}

void s21_3DViewer::rotation_y() {
  rotating_y = ui->lineEdit_rotating_y->text().toDouble() * 100;
  model_transformation();
}

void s21_3DViewer::on_dial_rotating_y_valueChanged(int value) {
  rotating_y = -100 * value;
  model_transformation();
}

void s21_3DViewer::rotation_z() {
  rotating_z = ui->lineEdit_rotating_z->text().toDouble() * 100;
  model_transformation();
}

void s21_3DViewer::on_dial_rotating_z_valueChanged(int value) {
  rotating_z = -100 * value;
  model_transformation();
}

void s21_3DViewer::zoom_x() {
  scaling_x = ui->lineEdit_scaling_x->text().toDouble() * 100;
  model_transformation();
}

void s21_3DViewer::on_horizontalSlider_scaling_x_valueChanged(int value) {
  scaling_x = value;
  model_transformation();
}

void s21_3DViewer::zoom_y() {
  scaling_y = ui->lineEdit_scaling_y->text().toDouble() * 100;
  model_transformation();
}

void s21_3DViewer::on_horizontalSlider_scaling_y_valueChanged(int value) {
  scaling_y = value;
  model_transformation();
}

void s21_3DViewer::zoom_z() {
  scaling_z = ui->lineEdit_scaling_z->text().toDouble() * 100;
  model_transformation();
}

void s21_3DViewer::on_horizontalSlider_scaling_z_valueChanged(int value) {
  scaling_z = value;
  model_transformation();
}

void s21_3DViewer::zoom_all() {
  scaling_x = scaling_y = scaling_z =
      ui->lineEdit_scaling->text().toDouble() * 100;
  model_transformation();
}

void s21_3DViewer::on_horizontalSlider_scaling_valueChanged(int value) {
  scaling_x = scaling_y = scaling_z = scaling_all = value;
  model_transformation();
}

void s21_3DViewer::location_change(double change_x, double change_y,
                                   double change_z, axis_values *coordinate,
                                   transformation_t type) {
  coordinate->x_axis = change_x / 100;
  coordinate->y_axis = change_y / 100;
  coordinate->z_axis = change_z / 100;
  transformation(&vertex_arr, type, coordinate);
  ui->openGLWidget->vertex_arr_paint = vertex_arr;
}

void s21_3DViewer::model_transformation() {
  vertexcopy(&vertex_arr_start, &vertex_arr);
  location_change(scaling_x, scaling_y, scaling_z, &values, scaling);
  location_change(rotating_x, rotating_y, rotating_z, &values, rotation);
  location_change(translation_x, translation_y, translation_z, &values,
                  translation);
  ui->openGLWidget->update();
}

void s21_3DViewer::on_checkBox_translating_toggled(bool checked) {
  if (checked == true) {
    translation_x = translation_y = translation_z = 0;
    set_translation_default();
    model_transformation();
  }
}

void s21_3DViewer::on_checkBox_rotating_toggled(bool checked) {
  if (checked == true) {
    rotating_x = rotating_y = rotating_z = 0;
    set_rotating_default();
    model_transformation();
  }
}

void s21_3DViewer::on_checkBox_scaling_toggled(bool checked) {
  if (checked == true) {
    scaling_x = scaling_y = scaling_z = 100;
    set_scaling_default();
    model_transformation();
  }
}

void s21_3DViewer::set_all_default() {
  set_translation_default();
  set_rotating_default();
  set_scaling_default();

  ui->checkBox_translating->setChecked(false);
  ui->checkBox_rotating->setChecked(false);
  ui->checkBox_scaling->setChecked(false);
}

void s21_3DViewer::set_translation_default() {
  ui->lineEdit_translating_x->setText("");
  ui->lineEdit_translating_y->setText("");
  ui->lineEdit_translating_z->setText("");

  ui->horizontalScrollBar_translation_x->setValue(0);
  ui->horizontalScrollBar_translation_y->setValue(0);
  ui->horizontalScrollBar_translation_z->setValue(0);
}

void s21_3DViewer::set_rotating_default() {
  ui->lineEdit_rotating_x->setText("");
  ui->lineEdit_rotating_y->setText("");
  ui->lineEdit_rotating_z->setText("");

  ui->dial_rotating_x->setValue(0);
  ui->dial_rotating_y->setValue(0);
  ui->dial_rotating_z->setValue(0);
}

void s21_3DViewer::set_scaling_default() {
  ui->lineEdit_scaling_x->setText("");
  ui->lineEdit_scaling_y->setText("");
  ui->lineEdit_scaling_z->setText("");
  ui->lineEdit_scaling->setText("");

  ui->horizontalSlider_scaling_x->setValue(100);
  ui->horizontalSlider_scaling_y->setValue(100);
  ui->horizontalSlider_scaling_z->setValue(100);
  ui->horizontalSlider_scaling->setValue(100);
}

void s21_3DViewer::write_settings() {
  QSettings settings("MySoft", "3DViewer_v1");

  settings.beginGroup("s21_3DViewer");

  settings.setValue("file_name", file_name);
  settings.setValue("path_project", path_project);

  settings.setValue("start_scaling", ui->checkBox_scaling->isChecked());
  settings.setValue("start_rotating", ui->checkBox_rotating->isChecked());
  settings.setValue("start_translating", ui->checkBox_translating->isChecked());

  settings.setValue("lineEdit_scaling", ui->lineEdit_scaling->text());
  settings.setValue("scaling_all", scaling_all);

  settings.setValue("lineEdit_scaling_x", ui->lineEdit_scaling_x->text());
  settings.setValue("scaling_x", scaling_x);
  settings.setValue("lineEdit_scaling_y", ui->lineEdit_scaling_y->text());
  settings.setValue("scaling_y", scaling_y);
  settings.setValue("lineEdit_scaling_z", ui->lineEdit_scaling_z->text());
  settings.setValue("scaling_z", scaling_z);

  settings.setValue("lineEdit_rotating_x", ui->lineEdit_rotating_x->text());
  settings.setValue("rotating_x", rotating_x);
  settings.setValue("lineEdit_rotating_y", ui->lineEdit_rotating_y->text());
  settings.setValue("rotating_y", rotating_y);
  settings.setValue("lineEdit_rotating_z", ui->lineEdit_rotating_z->text());
  settings.setValue("rotating_z", rotating_z);

  settings.setValue("lineEdit_translation_x",
                    ui->lineEdit_translating_x->text());
  settings.setValue("translation_x", translation_x);
  settings.setValue("lineEdit_translation_y",
                    ui->lineEdit_translating_y->text());
  settings.setValue("translation_y", translation_y);
  settings.setValue("lineEdit_translation_z",
                    ui->lineEdit_translating_z->text());
  settings.setValue("translation_z", translation_z);

  settings.endGroup();

  settings.beginGroup("s21_qlwidget");

  settings.setValue("line_dashed", ui->openGLWidget->line_dashed);
  settings.setValue("line_size", ui->openGLWidget->line_size);
  settings.setValue("line_color", ui->openGLWidget->line_color);

  settings.setValue("point_draw", ui->openGLWidget->point_draw);
  settings.setValue("point_circle", ui->openGLWidget->point_circle);
  settings.setValue("point_size", ui->openGLWidget->point_size);
  settings.setValue("vertice_color", ui->openGLWidget->vertice_color);

  settings.setValue("back_color", ui->openGLWidget->back_color);

  settings.setValue("project_parallel", ui->openGLWidget->project_parallel);

  settings.endGroup();
}

void s21_3DViewer::read_settings() {
  QSettings settings("MySoft", "3DViewer_v1");

  settings.beginGroup("s21_qlwidget");

  ui->openGLWidget->line_dashed = settings.value("line_dashed").toInt();
  ui->openGLWidget->line_size = settings.value("line_size").toInt();
  ui->openGLWidget->line_color = settings.value("line_color").value<QColor>();

  ui->openGLWidget->point_draw = settings.value("point_draw").toInt();
  ui->openGLWidget->point_circle = settings.value("point_circle").toInt();
  ui->openGLWidget->point_size = settings.value("point_size").toInt();
  ui->openGLWidget->vertice_color =
      settings.value("vertice_color").value<QColor>();

  ui->openGLWidget->back_color = settings.value("back_color").value<QColor>();

  ui->openGLWidget->project_parallel =
      settings.value("project_parallel").toInt();

  settings.endGroup();

  settings.beginGroup("s21_3DViewer");

  file_name = settings.value("file_name").value<QString>();
  path_project = settings.value("path_project").value<QString>();
  if (file_name.isEmpty()) {
    first_open();
  } else {
    file_open();
  }

  ui->checkBox_scaling->setChecked(settings.value("start_scaling").toBool());
  ui->checkBox_rotating->setChecked(settings.value("start_rotating").toBool());
  ui->checkBox_translating->setChecked(
      settings.value("start_translating").toBool());

  scaling_all = settings.value("scaling_all").toDouble();

  if (scaling_all != 0) {
    ui->lineEdit_scaling->setText(
        settings.value("lineEdit_scaling").toString());
    ui->horizontalSlider_scaling->setValue(
        settings.value("scaling_all").toInt());

    ui->lineEdit_scaling_x->setText(
        settings.value("lineEdit_scaling_x").toString());
    ui->horizontalSlider_scaling_x->setValue(
        settings.value("scaling_x").toInt());
    ui->lineEdit_scaling_y->setText(
        settings.value("lineEdit_scaling_y").toString());
    ui->horizontalSlider_scaling_y->setValue(
        settings.value("scaling_y").toInt());
    ui->lineEdit_scaling_z->setText(
        settings.value("lineEdit_scaling_z").toString());
    ui->horizontalSlider_scaling_z->setValue(
        settings.value("scaling_z").toInt());
  } else {
    ui->horizontalSlider_scaling->setValue(100);

    ui->horizontalSlider_scaling_x->setValue(100);
    ui->horizontalSlider_scaling_y->setValue(100);
    ui->horizontalSlider_scaling_z->setValue(100);
  }

  ui->lineEdit_rotating_x->setText(
      settings.value("lineEdit_rotating_x").toString());
  ui->dial_rotating_x->setValue(settings.value("rotating_x").toInt() / -100);
  ui->lineEdit_rotating_y->setText(
      settings.value("lineEdit_rotating_y").toString());
  ui->dial_rotating_y->setValue(settings.value("rotating_y").toInt() / -100);
  ui->lineEdit_rotating_z->setText(
      settings.value("lineEdit_rotating_z").toString());
  ui->dial_rotating_z->setValue(settings.value("rotating_z").toInt() / -100);

  ui->lineEdit_translating_x->setText(
      settings.value("lineEdit_translation_x").toString());
  ui->horizontalScrollBar_translation_x->setValue(
      settings.value("translation_x").toInt());
  ui->lineEdit_translating_y->setText(
      settings.value("lineEdit_translation_y").toString());
  ui->horizontalScrollBar_translation_y->setValue(
      settings.value("translation_y").toInt());
  ui->lineEdit_translating_z->setText(
      settings.value("lineEdit_translation_z").toString());
  ui->horizontalScrollBar_translation_z->setValue(
      settings.value("translation_z").toInt());

  settings.endGroup();
}

void s21_3DViewer::closeEvent(QCloseEvent *event) {
  QMessageBox save_settings;
  QAbstractButton *yes = save_settings.addButton("Да", QMessageBox::YesRole);
  QAbstractButton *no = save_settings.addButton("Нет", QMessageBox::NoRole);
  save_settings.setText("Сохранить настройки?");
  save_settings.exec();
  if (save_settings.clickedButton() == yes) {
    write_settings();
    event->accept();
  } else if (save_settings.clickedButton() == no) {
    set_all_default();
    event->accept();
  }
}

void s21_3DViewer::first_open() {
  std::string absolute_path = QDir::currentPath().toStdString();

  int index_find = absolute_path.find("src", 0);

  path_project = QString::fromStdString(absolute_path.erase(index_find));

  absolute_path.append("src/models/cube.obj");

  file_name = QString::fromStdString(absolute_path);
  ui->openGLWidget->back_color = QColor(236, 236, 236, 0);

  if (file_name.isNull() == false) {
    file_open();
  }
}

void s21_3DViewer::file_open() {
  QByteArray ba = file_name.toLocal8Bit();
  str_file_name = ba.data();

  status = obj_file_full(str_file_name, &vertex_arr_start, &polygon_arr);
  if (status == SUCCESS) {
    vertexcopy(&vertex_arr_start, &vertex_arr);

    ui->openGLWidget->vertex_arr_paint = vertex_arr;
    ui->openGLWidget->polygon_arr_paint = polygon_arr;
    ui->openGLWidget->update();

    ui->label_file->setText(QFileInfo(file_name).fileName());
    ui->label_number_vertices->setText(QString::number(vertex_arr.p_amount));
    ui->label_number_edges->setText(QString::number(polygon_arr.amount_edges));

    set_all_default();
  }
}

void s21_3DViewer::save_bmp() {
  QPixmap screen_bmp = ui->openGLWidget->grab();
  QImage bmp = screen_bmp.toImage();
  QPainter painter(&bmp);
  ui->openGLWidget->render(&painter);
  painter.end();
  QString path_bmp = QFileDialog::getSaveFileName(
      this, "Save screen", path_project.append("src/"), "Images (*.bmp)");
  if (path_bmp.isNull() == false) {
    bmp.save(path_bmp, "BMP");
  }
}

void s21_3DViewer::save_jpeg() {
  QPixmap screen_jpeg = ui->openGLWidget->grab();
  QImage jpeg = screen_jpeg.toImage();
  QPainter painter(&jpeg);
  ui->openGLWidget->render(&painter);
  painter.end();
  QString path_jpeg = QFileDialog::getSaveFileName(
      this, "Save screen", path_project.append("src/"), "Images (*.jpeg)");
  if (path_jpeg.isNull() == false) {
    jpeg.save(path_jpeg, "JPEG");
  }
}

void s21_3DViewer::save_gif() {
  gif = new QGifImage();
  gif_timer = new QTimer(this);
  gif->setDefaultDelay(gif_interval);
  connect(gif_timer, SIGNAL(timeout()), this, SLOT(recording_gif()));
  gif_timer->start(gif_interval);
  QTimer::singleShot(5000, this, SLOT(finish_recording()));
}

void s21_3DViewer::recording_gif() {
  QImage frame = ui->openGLWidget->grab().toImage();
  gif->addFrame(frame, gif_interval);
}

void s21_3DViewer::finish_recording() {
  gif_timer->stop();
  QString path_gif = QFileDialog::getSaveFileName(
      this, "Save screen", path_project.append("src/"), "Images (*.gif)");
  if (path_gif.isNull() == false) {
    gif->save(path_gif);
  }
}
