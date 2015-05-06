#include "secondwindow.h"
#include "glwidget.h"

 SecondWindow::SecondWindow()
 {
     glWidget = new GLWidget;



     QHBoxLayout *mainLayout = new QHBoxLayout;
     mainLayout->addWidget(glWidget);

     setLayout(mainLayout);


     setWindowTitle(tr("Testing window"));
 }



 void SecondWindow::keyPressEvent(QKeyEvent *e)
 {
     if (e->key() == Qt::Key_Escape)
         close();
     else
         QWidget::keyPressEvent(e);
 }
