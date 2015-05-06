#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QWidget>

 class QSlider;

 class GLWidget;

 class SecondWindow : public QWidget
 {
     Q_OBJECT

 public:
     SecondWindow();

 protected:
     void keyPressEvent(QKeyEvent *event);

 private:

     GLWidget *glWidget;
};

#endif // SECONDWINDOW_H
