#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSlider>
#include "glapllet.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(void);
private:
    QSlider *createSlider();
    vl::OpenGLContextFormat format;
    QSlider *innerTessSlider;
    QSlider *outerTessSlider;
    QSlider *displacementSlider;
    vl::ref<GLApllet> glapp;

signals:

public slots:
private slots:
    void changeInnerTesselation(int change);
    void changeOuterTesselation(int change);
    void changeDisplacement(int change);

};

#endif // MAINWINDOW_H
