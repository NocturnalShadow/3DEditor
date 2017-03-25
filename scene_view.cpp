#include "scene_view.h"


void SceneView::Initialize()
{
    program.InitShader();

    glFunctions->glEnable(GL_DEPTH_TEST);
    glFunctions->glEnable(GL_CULL_FACE);
    glFunctions->glCullFace(GL_BACK);

    glFunctions->glClearColor(0.15f, 0.145f, 0.15f, 1.0f);
}

void SceneView::AddItem(SceneItem *item)
{
    item->BindShaderProgram(&program);
    items.push_back(item);
}

void SceneView::Paint()
{
    program.Update(*camera);
    for(auto item : items) {
        item->Draw(glFunctions);
    }
}
