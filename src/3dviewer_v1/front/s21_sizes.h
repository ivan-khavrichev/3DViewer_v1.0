#ifndef S21_SIZES_H
#define S21_SIZES_H

#include <QAbstractButton>
#include <QDialog>

namespace Ui {
class s21_sizes;
}

class s21_sizes : public QDialog {
  Q_OBJECT

 public:
  explicit s21_sizes(QWidget *parent = nullptr);
  ~s21_sizes();
  Ui::s21_sizes *ui;
  int size;

 private slots:

  void on_horizontalSlider_size_valueChanged(int value);
};

#endif  // S21_SIZES_H
