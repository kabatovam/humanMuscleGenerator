#include "mainwindow.h"

 MainWindow::MainWindow()
 {
     glWidget = new GLWidget;



     QHBoxLayout *mainLayout = new QHBoxLayout;
     mainLayout->addWidget(glWidget);

     setLayout(mainLayout);


     setWindowTitle(tr("Testing window"));
 }



 /*void MainWindow::keyPressEvent(QKeyEvent *e)
 {
     if (e->key() == Qt::Key_Escape)
         close();
     else
         QWidget::keyPressEvent(e);
 }*/
