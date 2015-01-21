#ifndef SCENECONTROLLER_H
#define SCENECONTROLLER_H

#include "vertexbufferobject.h"
#include "shadercontroller.h"
#include <QOpenGLTexture>


class SceneController
{
public:
    SceneController();
    void paintObject();
    void createTexture();
    void changeProjection(int w, int h);
    void init();
private:
    QOpenGLShaderProgram program;
    QOpenGLTexture *texture;
    VertexBufferObject vbo;
    ShaderController sc;
    QMatrix4x4 projection;
    QQuaternion rotation;
};

#endif // SCENECONTROLLER_H
