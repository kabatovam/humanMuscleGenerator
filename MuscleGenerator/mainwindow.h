#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QHBoxLayout>
#include <QMainWindow>
#include <QWidget>

#include "glwidget.h"


class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(void);

protected:
   // void keyPressEvent(QKeyEvent *event);

private:

    GLWidget *glWidget;

signals:

public slots:

};

#endif // MAINWINDOW_H


