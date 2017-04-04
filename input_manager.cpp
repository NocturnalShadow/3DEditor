#include "input_manager.h"

#include <QDebug>

InputManager::InputManager(QOpenGLFunctions_4_3_Core* _glFunctions, QOpenGLContext* _context, int width, int height)
    : glFunctions{ _glFunctions },
      context{ _context }
{
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    format.setSamples(0);

    stencil_buffer = std::make_unique<QOpenGLFramebufferObject>(width, height, format);
}

uint InputManager::ItemID(QPoint position)
{
    stencil_buffer->bind();

    GLuint index;
    glFunctions->glReadPixels(position.rx(), height - position.ry() - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

    QOpenGLFramebufferObject::bindDefault();
    qDebug() << index;
    return index;
}

void InputManager::Resize(int _width, int _height)
{
    if(_width != width || _height != height)
    {
        width   = _width;
        height  = _height;

        stencil_buffer = std::make_unique<QOpenGLFramebufferObject>(width, height, format);
    }
}

void InputManager::Update()
{
    glFunctions->glBindFramebuffer(GL_READ_FRAMEBUFFER, context->defaultFramebufferObject());
    glFunctions->glBindFramebuffer(GL_DRAW_FRAMEBUFFER, stencil_buffer->handle());
    glFunctions->glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_STENCIL_BUFFER_BIT, GL_NEAREST);
    glFunctions->glBindFramebuffer(GL_FRAMEBUFFER, context->defaultFramebufferObject());
}
