#ifndef SHADERCONTROLLER_H
#define SHADERCONTROLLER_H

#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>

class ShaderController
{
public:
    ShaderController();
    void setupShaders(QOpenGLShaderProgram *program);
private:

};

#endif // SHADERCONTROLLER_H
