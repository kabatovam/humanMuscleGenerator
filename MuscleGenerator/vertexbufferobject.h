#ifndef VERTEXBUFFEROBJECT_H
#define VERTEXBUFFEROBJECT_H

#include <QGLFunctions>
#include <QVector2D>
#include <QVector3D>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

struct data{
    QVector3D position;
    QVector2D texCoord;
};

class VertexBufferObject : protected QGLFunctions
{
public:
    VertexBufferObject();
    ~VertexBufferObject();
    void initGLFunc();
    void initializeBuffer();
    void draw(QOpenGLShaderProgram *program);
private:
    void createBuffers();
    void bindBuffers();
    void createData();
    void createGeometry();
    data *vertices;
    GLushort *indices;
    GLuint vboIds[2];
    QOpenGLBuffer vertexBuff;
    QOpenGLBuffer indexBuff;
};

#endif // VERTEXBUFFEROBJECT_H
