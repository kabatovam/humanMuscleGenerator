#ifndef VERTEXBUFFEROBJECT_H
#define VERTEXBUFFEROBJECT_H

#include <QVector2D>
#include <QVector3D>
#include <QGL>
#include <QGLFunctionsPrivate>

struct data{
    QVector3D position;
    QVector2D texCoord;
};

class VertexBufferObject
{
public:
    VertexBufferObject();
    ~VertexBufferObject();
    void initializeBuffer();
private:
    void createBuffers();
    void bindBuffers();
    void createData();
    void createGeometry();
    data *vertices;
    GLushort *indices;
    GLuint vboIds[2];
};

#endif // VERTEXBUFFEROBJECT_H
