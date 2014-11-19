#ifndef APP_ROTATINGCUBE_H
#define APP_ROTATINGCUBE_H

#include <vlGraphics/Applet.hpp>
#include <vlCore/VisualizationLibrary.hpp>
#include <vlGraphics/Geometry.hpp>
#include <vlGraphics/GeometryPrimitives.hpp>
#include <vlGraphics/SceneManagerActorTree.hpp>
#include <vlGraphics/Rendering.hpp>
#include <vlGraphics/Actor.hpp>
#include <vlGraphics/Effect.hpp>
#include <vlCore/Time.hpp>
#include <vlGraphics/Light.hpp>
#include <vlGraphics/GLSL.hpp>
#include <vlCore/ResourceDatabase.hpp>
#include <vlCore/FileSystem.hpp>

class App_RotatingCube: public vl::Applet
{
public:
  // called once after the OpenGL window has been opened


    void initEvent()
  {
      //vl::ref<vl::GLSLVertexShader>   noise_vs   = new vl::GLSLVertexShader("C:/Users/whitelilit/DP_examples/build/glsl/examples/noise.vs");
       //   vl::ref<vl::GLSLFragmentShader> noise3D_fs = new vl::GLSLFragmentShader("C:/Users/whitelilit/DP_examples/build/glsl/noise3D.glsl");


        vl::ref<vl::Geometry> model = vl::loadResource("C:/Users/whitelilit/Documents/3dsMax/export/plane2.3ds")->get<vl::Geometry>(0);
        model->computeNormals();
        vl::ref<vl::PatchParameter> patch_param = new vl::PatchParameter;
        patch_param->setPatchVertices(3);
        model->drawCalls()->at(0)->setPatchParameter(patch_param.get());
        model->drawCalls()->at(0)->setPrimitiveType(vl::PT_PATCHES);




    vl::ref<vl::Texture> tex_human = new vl::Texture("C:/Users/whitelilit/Documents/Mudbox/test.tif",vl::TF_UNKNOWN);
    vl::ref<vl::Texture> hmap = new vl::Texture("C:/Users/whitelilit/DP_examples/build/images/ps_height_4k.jpg", vl::TF_RED, false, false);
    vl::ref<vl::Texture> tmap = new vl::Texture("C:/Users/whitelilit/DP_examples/build/images/ps_texture_4k.jpg", vl::TF_RGBA, true, false);
    hmap->getTexParameter()->setMinFilter(vl::TPF_LINEAR);
    hmap->getTexParameter()->setMagFilter(vl::TPF_LINEAR);

    // setup the effect to be used to render the cube
    vl::ref<vl::Effect> effect = new vl::Effect;


    // enable depth test and lighting
    effect->shader()->enable(vl::EN_DEPTH_TEST);
    effect->shader()->gocTextureSampler(0)->setTexture(tex_human.get());
    //effect->shader()->gocTextureSampler(0)->setTexture(hmap.get());
    //effect->shader()->gocTextureSampler(0)->setTexture(tmap.get());
    // add a Light to the scene, since no Transform is associated to the Light it will follow the camera
    effect->shader()->setRenderState( new vl::Light, 0 );
    // enable the standard OpenGL lighting
    effect->shader()->enable(vl::EN_LIGHTING);

/*
    mGLSL = effect->shader()->gocGLSLProgram();
    mGLSL->attachShader( new vl::GLSLVertexShader("C:/Users/whitelilit/DP_examples/build/glsl/tess_grid.vs") );
    mGLSL->attachShader( new vl::GLSLTessControlShader("C:/Users/whitelilit/DP_examples/build/glsl/tess_grid.tcs") );
    mGLSL->attachShader( new vl::GLSLTessEvaluationShader("C:/Users/whitelilit/DP_examples/build/glsl/tess_grid.tes") );
    mGLSL->attachShader( new vl::GLSLFragmentShader("C:/Users/whitelilit/DP_examples/build/glsl/tess_grid.fs") );
    mGLSL->gocUniform("pixel_per_edge")->setUniformF(pixel_per_edge);
    mGLSL->gocUniform("max_tessellation")->setUniformF(max_tessellation);
    mGLSL->gocUniform("screen_size")->setUniform(vl::fvec2(512,512));
    mGLSL->gocUniform("world_size")->setUniformF(world_size);
    mGLSL->gocUniform("height_scale")->setUniformF(height_scale);
    mGLSL->gocUniform("tex_heghtmap")->setUniformI(0);
    mGLSL->gocUniform("tex_diffuse")->setUniformI(1);

    mGLSL->addAutoAttribLocation( 0, "vl_Position" );
*/




    glsl = effect->shader()->gocGLSLProgram();
    glsl->attachShader( new vl::GLSLVertexShader("C:/Users/whitelilit/DP_examples/build/glsl/vertex_shader.vs") );
    glsl->attachShader(new vl::GLSLTessControlShader("C:/Users/whitelilit/DP_examples/build/glsl/tesselation_shader.tcs"));
    glsl->attachShader(new vl::GLSLTessEvaluationShader("C:/Users/whitelilit/DP_examples/build/glsl/tesselation_shader.tes"));
    glsl->attachShader( new vl::GLSLFragmentShader("C:/Users/whitelilit/DP_examples/build/glsl/fragment_shader.fs") );

   // glsl->gocUniform("tex_hm")->setUniformI(0);
    glsl->addAutoAttribLocation(0,"pos");



    // install our scene manager, we use the SceneManagerActorTree which is the most generic
    vl::ref<vl::SceneManagerActorTree> scene_manager = new vl::SceneManagerActorTree;
    rendering()->as<vl::Rendering>()->sceneManagers()->push_back(scene_manager.get());
    // add the cube to the scene using the previously defined effect and transform


    scene_manager->tree()->addActor( model.get(), effect.get(), NULL );


  }



  // called every frame
  virtual void updateScene()
  {
    // rotates the cube around the Y axis 45 degrees per second
    vl::real degrees = vl::Time::currentTime() * 45.0f;
    vl::mat4 matrix = vl::mat4::getRotation( degrees, 0,1,0 );
  }

protected:
  vl::ref<vl::GLSLProgram> glsl;
  vl::ref<vl::GLSLProgram> mGLSL;
};
// Have fun!
#endif // APP_ROTATINGCUBE_H
