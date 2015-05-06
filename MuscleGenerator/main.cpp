#include <iostream>
#include <QApplication>
#include "mainwindow.h"

using namespace std;

int main(int argv, char **args)
{
    QApplication app(argv, args);
    MainWindow w;
    w.resize(200,300);
    w.show();


    return app.exec();

}

