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

    int width   = 1366;
    int height  = 768;

public:
    InputManager(QOpenGLFunctions_4_3_Core* _glFunctions, QOpenGLContext* _context, int width = 1366, int height = 768)
        : glFunctions{ _glFunctions },
          context{ _context }
    {
        QOpenGLFramebufferObjectFormat format;
        format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
        format.setSamples(0);

        stencil_buffer = std::make_unique<QOpenGLFramebufferObject>(width, height, format);
    }

public:
    uint ItemID(QPoint position)
    {
        stencil_buffer->bind();

        GLuint index;
        glFunctions->glReadPixels(position.rx(), height - position.ry() - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

        QOpenGLFramebufferObject::bindDefault();
        qDebug() << index;
        return index;
    }

    void Resize(int _width, int _height)
    {
        width   = _width;
        height  = _height;
        // TODO fix resizing
    }

    void Update()
    {
        glFunctions->glBindFramebuffer(GL_READ_FRAMEBUFFER, context->defaultFramebufferObject());
        glFunctions->glBindFramebuffer(GL_DRAW_FRAMEBUFFER, stencil_buffer->handle());
        glFunctions->glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_STENCIL_BUFFER_BIT, GL_NEAREST);
        glFunctions->glBindFramebuffer(GL_FRAMEBUFFER, context->defaultFramebufferObject());
    }
};
