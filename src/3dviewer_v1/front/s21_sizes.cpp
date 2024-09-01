#include "s21_sizes.h"

#include "ui_s21_sizes.h"

s21_sizes::s21_sizes(QWidget *parent) : QDialog(parent), ui(new Ui::s21_sizes) {
  ui->setupUi(this);
}

s21_sizes::~s21_sizes() { delete ui; }

void s21_sizes::on_horizontalSlider_size_valueChanged(int value) {
  size = value;
  ui->label_size_value->setText("Величина: " + QString::number(value));
}
