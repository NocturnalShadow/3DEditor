#include "scene_view.h"


void SceneView::Initialize()
{
    program.InitShader();

    glFunctions->glEnable(GL_STENCIL_TEST);
    glFunctions->glEnable(GL_DEPTH_TEST);
    glFunctions->glEnable(GL_CULL_FACE);
    glFunctions->glCullFace(GL_BACK);

    glFunctions->glClearColor(0.15f, 0.145f, 0.15f, 1.0f);
}

void SceneView::AddItem(IDrawable* item)
{
    item->BindShaderProgram(&program);
    scene_items.push_back(item);
}

void SceneView::AddUserInterfaceItem(IDrawable* item)
{
    item->BindShaderProgram(&program);
    ui_items.push_back(item);
}

void SceneView::Resize(int width, int height)
{
    glFunctions->glViewport(0, 0, width, height);
    camera->ChangeAspect(width, height);
}

void SceneView::Paint()
{
    glFunctions->glClearStencil(0);
    glFunctions->glClear(GL_STENCIL_BUFFER_BIT);

    program.Update(*camera);
    for(auto item : scene_items) {
        item->Draw(glFunctions);
    }

    glFunctions->glClear(GL_DEPTH_BUFFER_BIT);

    for(auto item : ui_items) {
        item->Draw(glFunctions);
    }
}

