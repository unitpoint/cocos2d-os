#ifndef __OPENGL_OS_H__
#define __OPENGL_OS_H__

#include "objectscript.h"
#include "IwGL.h"

using namespace ObjectScript;

void initOpenGL(OS * os);
void initOpenGL2(OS * os);
void initOpenGLExt(OS * os);

void gluPerspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar);
void gluLookAt(float fEyeX, float fEyeY, float fEyeZ,
	float fCenterX, float fCenterY, float fCenterZ,
	float fUpX, float fUpY, float fUpZ);

#endif // __OPENGL_OS_H__
