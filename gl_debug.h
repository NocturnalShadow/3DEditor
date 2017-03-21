#ifndef GL_DEBUG_H
#define GL_DEBUG_H

#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_3_Core>

void _check_gl_error(const char *file, int line, QOpenGLFunctions_4_3_Core* funcs, const char* msg);

///
/// Usage
/// [... some opengl calls]
/// glDebug(gl_funcs, msg);
///
#define glDebug(funcs, msg) _check_gl_error(__FILE__,__LINE__, funcs, msg)


#endif // GL_DEBUG_H
