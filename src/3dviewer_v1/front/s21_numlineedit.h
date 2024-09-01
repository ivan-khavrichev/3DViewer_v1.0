#ifndef S21_NUMLINEEDIT_H
#define S21_NUMLINEEDIT_H

#include <QInputDialog>
#include <QKeyEvent>
#include <QLineEdit>
#include <QWidget>

class s21_numlineedit : public QLineEdit {
  Q_OBJECT
 public:
  s21_numlineedit(QWidget *parent = nullptr);

 protected:
  void keyPressEvent(QKeyEvent *event) override {
    int key = event->key();
    if ((key >= Qt::Key_0 && key <= Qt::Key_9) || key == Qt::Key_Period ||
        key == Qt::Key_Backspace || key == Qt::Key_Left ||
        key == Qt::Key_Right || key == Qt::Key_Enter || key == Qt::Key_Minus)
      QLineEdit::keyPressEvent(event);
  };

 signals:
};

#endif  // S21_NUMLINEEDIT_H
