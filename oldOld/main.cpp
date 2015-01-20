#include <iostream>
#include <QApplication>
#include <vlCore/VisualizationLibrary.hpp>
#include "mainwindow.h"
#include "secondwindow.h"
using namespace std;

int main(int argv, char **args)
{
    QApplication app(argv, args);
    vl::VisualizationLibrary::init();
    MainWindow w;
    w.resize(200,300);

    w.show();

    SecondWindow sw;
    sw.resize(200,300);
    sw.show();

    return app.exec();
}

