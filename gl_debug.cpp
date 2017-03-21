
#include "gl_debug.h"

#include <QDebug>

void _check_gl_error(const char *file, int line, QOpenGLFunctions* funcs, const char* msg) {
        GLenum err (funcs->glGetError());
        qDebug() << msg;
        if(err!=GL_NO_ERROR) {
                QString error = "unknown";
                switch(err) {
                        case GL_INVALID_OPERATION:      error="INVALID_OPERATION";      break;
                        case GL_INVALID_ENUM:           error="INVALID_ENUM";           break;
                        case GL_INVALID_VALUE:          error="INVALID_VALUE";          break;
                        case GL_OUT_OF_MEMORY:          error="OUT_OF_MEMORY";          break;
                        case GL_INVALID_FRAMEBUFFER_OPERATION:  error="INVALID_FRAMEBUFFER_OPERATION";  break;
                }
                qDebug() << "GL_" << error <<" - "<< file << ":" << line << endl;
                // err = funcs->glGetError();
                exit(0);
        }
}
