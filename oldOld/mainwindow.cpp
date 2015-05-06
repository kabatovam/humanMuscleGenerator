#include "mainwindow.h"
#include <vlCore/VisualizationLibrary.hpp>
#include <iostream>
#include <vlQt4/Qt4Widget.hpp>
#include <vlGraphics/GLSL.hpp>
#include <QVBoxLayout>
#include <QLabel>


using namespace vl;
using namespace vlQt4;
MainWindow::MainWindow(void)
{

    format.setDoubleBuffer(true);
    format.setRGBABits( 8,8,8,8 );
    format.setDepthBufferBits(24);
    format.setStencilBufferBits(8);
    format.setFullscreen(false);
    //format.setMultisampleSamples(16);
    //format.setMultisample(true);
    glapp = new GLApllet();
    glapp->initialize();
    ref<vlQt4::Qt4Widget> qt4_window = new vlQt4::Qt4Widget;
      /* bind the applet so it receives all the GUI events related to the OpenGLContext */
      qt4_window->addEventListener(glapp.get());
      /* target the window so we can render on it */
      glapp->rendering()->as<Rendering>()->renderer()->setFramebuffer( qt4_window->framebuffer() );
      /* black background */
      glapp->rendering()->as<Rendering>()->camera()->viewport()->setClearColor( black );
      /* define the camera position and orientation */
      vec3 eye    = vec3(0,10,35); // camera position
      vec3 center = vec3(0,0,0);   // point the camera is looking at
      vec3 up     = vec3(0,1,0);   // up direction
      mat4 view_mat = mat4::getLookAt(eye, center, up);
      glapp->rendering()->as<Rendering>()->camera()->setViewMatrix( view_mat );
      /* Initialize the OpenGL context and window properties */
      int x = 10;
      int y = 10;
      int width = 512;
      int height= 512;
      qt4_window->initQt4Widget( "", format, NULL, x, y, width, height );
      qt4_window->show();

      innerTessSlider = createSlider();
      connect(innerTessSlider,SIGNAL(valueChanged(int)),this,SLOT(changeInnerTesselation(int)));
      outerTessSlider = createSlider();
      connect(outerTessSlider,SIGNAL(valueChanged(int)),this,SLOT(changeOuterTesselation(int)));
      displacementSlider = createSlider();
      connect(displacementSlider,SIGNAL(valueChanged(int)),this,SLOT(changeDisplacement(int)));

      QLabel *otLabel = new QLabel("Outer tesselation level");
      QLabel *itLabel = new QLabel("Inner tesselation level");
      QLabel *disLabel = new QLabel("Displacement level");
      QWidget *window = new QWidget;
      QVBoxLayout *layout = new QVBoxLayout;
      layout->addWidget(itLabel);
      layout->addWidget(innerTessSlider);
      layout->addWidget(otLabel);
      layout->addWidget(outerTessSlider);
      layout->addWidget(disLabel);
      layout->addWidget(displacementSlider);
      window->setLayout(layout);
      setCentralWidget(window);


}

QSlider* MainWindow::createSlider()
{
    QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setRange(1, 10);
    slider->setSingleStep(1);
    slider->setPageStep(5);
    slider->setTickInterval(1);
    slider->setTickPosition(QSlider::TicksRight);
    return slider;
}

void MainWindow::changeInnerTesselation(int change)
{
    std::cout<<"Inner tesselation change: "<<change<<std::endl;
    glapp->changeInnerTesselation(change);
    glapp->updateScene();
}

void MainWindow::changeOuterTesselation(int change)
{
    std::cout<<"Outer tesselation change: "<<change<<std::endl;
    glapp->changeOuterTesselation(change);
    glapp->updateScene();
}

void MainWindow::changeDisplacement(int change)
{
    std::cout<<"Displacement change: "<<change<<std::endl;
    glapp->changeDisplacement(change);
    glapp->updateScene();
}
