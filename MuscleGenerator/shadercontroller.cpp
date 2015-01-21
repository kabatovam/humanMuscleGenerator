#include "shadercontroller.h"

ShaderController::ShaderController()
{
}

void ShaderController::setupShaders(QOpenGLShaderProgram *program){
    if(!program->addShaderFromSourceFile(QOpenGLShader::Vertex,"/home/whitelilit/HMGgit/MuscleGenerator-build/glsl/vertex.vs")){
    }
    if(!program->addShaderFromSourceFile(QOpenGLShader::Fragment,"/home/whitelilit/HMGgit/MuscleGenerator-build/glsl/fragment.fs")){
    }

    if(!program->link()){

    }

    if(!program->bind()){
    }
}
