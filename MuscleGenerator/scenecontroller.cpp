#include "scenecontroller.h"
#include <QOpenGLFunctions>
#include <iostream>
SceneController::SceneController()
{


}

void SceneController::init(){
    vbo.initGLFunc();
    sc.setupShaders(&program);
    vbo.initializeBuffer();
}

void SceneController::createTexture(){

    glEnable(GL_TEXTURE_2D);

    texture = new QOpenGLTexture(QImage(":/test.tif").mirrored());

    if(texture->isCreated()){
        std::cout<<"Texture was succesfully created! \n";
    }
       // Set nearest filtering mode for texture minification
       texture->setMinificationFilter(QOpenGLTexture::Nearest);

       // Set bilinear filtering mode for texture magnification
       texture->setMagnificationFilter(QOpenGLTexture::Linear);

       // Wrap texture coordinates by repeating
       // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
       texture->setWrapMode(QOpenGLTexture::Repeat);

}

void SceneController::paintObject(){
    // Clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        texture->bind();

        // Calculate model view transformation
        QMatrix4x4 matrix;
        matrix.translate(0.0, 0.0, -5.0);
        matrix.rotate(rotation);

        // Set modelview-projection matrix
        program.setUniformValue("mvp_matrix", projection * matrix);

        // Use texture unit 0 which contains cube.png
        program.setUniformValue("texture", 0);

        // Draw cube geometry
        vbo.draw(&program);
}

void SceneController::changeProjection(int w, int h){

    // Calculate aspect ratio
       qreal aspect = qreal(w) / qreal(h ? h : 1);

       // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
       const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;

       // Reset projection
       projection.setToIdentity();

       // Set perspective projection
       projection.perspective(fov, aspect, zNear, zFar);
}
