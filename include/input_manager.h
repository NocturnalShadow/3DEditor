#pragma once

#include <memory>

#include <QOpenGLFramebufferObject>
#include <QOpenGLFunctions_4_3_Core>
#include <QOpenGLFramebufferObjectFormat>

class InputManager
{
private:
    std::unique_ptr<QOpenGLFramebufferObject>   stencil_buffer      = nullptr;
    QOpenGLFunctions_4_3_Core*                  glFunctions         = nullptr;
    QOpenGLContext*                             context             = nullptr;

    QOpenGLFramebufferObjectFormat              format;

    int width   = 1366;
    int height  = 768;

public:
    InputManager(QOpenGLFunctions_4_3_Core* _glFunctions, QOpenGLContext* _context, int width = 1366, int height = 768);

public:
    uint ItemID(QPoint position);

    void Resize(int _width, int _height);

    void Update();
};
