#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QGLShaderProgram>
#include <QGLBuffer>

//#include <QtGui>
#include <iostream>
#include <fstream>
class GLWidget : public QGLWidget
{
  Q_OBJECT
public:
     GLWidget(QWidget *parent = 0);
     ~GLWidget();

        QSize minimumSizeHint() const;
        QSize sizeHint() const;

    public slots:
        void setXRotation(int angle);
        void setYRotation(int angle);
        void setZRotation(int angle);

    signals:
        void xRotationChanged(int angle);
        void yRotationChanged(int angle);
        void zRotationChanged(int angle);

    protected:
        void initializeGL();
        void paintGL();
        void resizeGL(int width, int height);
        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);

    private:
        //QtLogo *logo;
        int xRot;
        int yRot;
        int zRot;
        QPoint lastPos;
        QColor qtGreen;
        QColor qtPurple;

        QMatrix4x4 pMatrix;
        QGLShaderProgram shaderProgram;
        QVector<QVector3D> vertices;

        std::string readFile(const char *filePath);
    };

#endif // GLWIDGET_H
