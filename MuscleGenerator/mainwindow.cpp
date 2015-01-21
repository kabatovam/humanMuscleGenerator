#include "mainwindow.h"
#include <QGLFormat>

 MainWindow::MainWindow()
 {
     QGLFormat glFormat;
     glFormat.setVersion( 3, 3 );
     glFormat.setProfile( QGLFormat::CoreProfile ); // Requires >=Qt-4.8.0
     glFormat.setSampleBuffers( true );

     glWidget = new GLWidget(glFormat);



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
