#include "OpenGLOS.h"
#include "CCGL.h"

void initOpenGL(OS * os)
{
	struct OpenGL
	{
		/* Available only in Common profile */    static int glAlphaFunc(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glAlphaFunc (GLenum func, GLclampf ref); */
			::glAlphaFunc((GLenum)os->toNumber(-params+0), (GLclampf)os->toNumber(-params+1));
			return 0;
		}

		static int glClearColor(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glClearColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha); */
			::glClearColor((GLclampf)os->toNumber(-params+0), (GLclampf)os->toNumber(-params+1), (GLclampf)os->toNumber(-params+2), (GLclampf)os->toNumber(-params+3));
			return 0;
		}

		static int glClearDepthf(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glClearDepthf (GLclampf depth); */
			::glClearDepthf((GLclampf)os->toNumber(-params+0));
			return 0;
		}

		/* skip: GL_API void GL_APIENTRY glClipPlanef (GLenum plane, const GLfloat *equation); */

		static int glColor4f(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glColor4f (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha); */
			::glColor4f((GLfloat)os->toNumber(-params+0), (GLfloat)os->toNumber(-params+1), (GLfloat)os->toNumber(-params+2), (GLfloat)os->toNumber(-params+3));
			return 0;
		}

		static int glDepthRangef(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glDepthRangef (GLclampf zNear, GLclampf zFar); */
			::glDepthRangef((GLclampf)os->toNumber(-params+0), (GLclampf)os->toNumber(-params+1));
			return 0;
		}

		static int glFogf(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glFogf (GLenum pname, GLfloat param); */
			::glFogf((GLenum)os->toNumber(-params+0), (GLfloat)os->toNumber(-params+1));
			return 0;
		}

		/* skip: GL_API void GL_APIENTRY glFogfv (GLenum pname, const GLfloat *params); */

		static int glFrustumf(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glFrustumf (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar); */
			::glFrustumf((GLfloat)os->toNumber(-params+0), (GLfloat)os->toNumber(-params+1), (GLfloat)os->toNumber(-params+2), (GLfloat)os->toNumber(-params+3), (GLfloat)os->toNumber(-params+4), (GLfloat)os->toNumber(-params+5));
			return 0;
		}

		/* skip: GL_API void GL_APIENTRY glGetClipPlanef (GLenum pname, GLfloat eqn[4]); */

		/* skip: GL_API void GL_APIENTRY glGetFloatv (GLenum pname, GLfloat *params); */

		/* skip: GL_API void GL_APIENTRY glGetLightfv (GLenum light, GLenum pname, GLfloat *params); */

		/* skip: GL_API void GL_APIENTRY glGetMaterialfv (GLenum face, GLenum pname, GLfloat *params); */

		/* skip: GL_API void GL_APIENTRY glGetTexEnvfv (GLenum env, GLenum pname, GLfloat *params); */

		/* skip: GL_API void GL_APIENTRY glGetTexParameterfv (GLenum target, GLenum pname, GLfloat *params); */

		static int glLightModelf(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glLightModelf (GLenum pname, GLfloat param); */
			::glLightModelf((GLenum)os->toNumber(-params+0), (GLfloat)os->toNumber(-params+1));
			return 0;
		}

		/* skip: GL_API void GL_APIENTRY glLightModelfv (GLenum pname, const GLfloat *params); */

		static int glLightf(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glLightf (GLenum light, GLenum pname, GLfloat param); */
			::glLightf((GLenum)os->toNumber(-params+0), (GLenum)os->toNumber(-params+1), (GLfloat)os->toNumber(-params+2));
			return 0;
		}

		/* skip: GL_API void GL_APIENTRY glLightfv (GLenum light, GLenum pname, const GLfloat *params); */

		static int glLineWidth(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glLineWidth (GLfloat width); */
			::glLineWidth((GLfloat)os->toNumber(-params+0));
			return 0;
		}

		/* skip: GL_API void GL_APIENTRY glLoadMatrixf (const GLfloat *m); */

		static int glMaterialf(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glMaterialf (GLenum face, GLenum pname, GLfloat param); */
			::glMaterialf((GLenum)os->toNumber(-params+0), (GLenum)os->toNumber(-params+1), (GLfloat)os->toNumber(-params+2));
			return 0;
		}

		/* skip: GL_API void GL_APIENTRY glMaterialfv (GLenum face, GLenum pname, const GLfloat *params); */

		/* skip: GL_API void GL_APIENTRY glMultMatrixf (const GLfloat *m); */

		static int glMultiTexCoord4f(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glMultiTexCoord4f (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q); */
			::glMultiTexCoord4f((GLenum)os->toNumber(-params+0), (GLfloat)os->toNumber(-params+1), (GLfloat)os->toNumber(-params+2), (GLfloat)os->toNumber(-params+3), (GLfloat)os->toNumber(-params+4));
			return 0;
		}

		static int glNormal3f(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glNormal3f (GLfloat nx, GLfloat ny, GLfloat nz); */
			::glNormal3f((GLfloat)os->toNumber(-params+0), (GLfloat)os->toNumber(-params+1), (GLfloat)os->toNumber(-params+2));
			return 0;
		}

		static int glOrthof(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glOrthof (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar); */
			::glOrthof((GLfloat)os->toNumber(-params+0), (GLfloat)os->toNumber(-params+1), (GLfloat)os->toNumber(-params+2), (GLfloat)os->toNumber(-params+3), (GLfloat)os->toNumber(-params+4), (GLfloat)os->toNumber(-params+5));
			return 0;
		}

		static int glPointParameterf(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glPointParameterf (GLenum pname, GLfloat param); */
			::glPointParameterf((GLenum)os->toNumber(-params+0), (GLfloat)os->toNumber(-params+1));
			return 0;
		}

		/* skip: GL_API void GL_APIENTRY glPointParameterfv (GLenum pname, const GLfloat *params); */

		static int glPointSize(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glPointSize (GLfloat size); */
			::glPointSize((GLfloat)os->toNumber(-params+0));
			return 0;
		}

		static int glPolygonOffset(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glPolygonOffset (GLfloat factor, GLfloat units); */
			::glPolygonOffset((GLfloat)os->toNumber(-params+0), (GLfloat)os->toNumber(-params+1));
			return 0;
		}

		static int glRotatef(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glRotatef (GLfloat angle, GLfloat x, GLfloat y, GLfloat z); */
			::glRotatef((GLfloat)os->toNumber(-params+0), (GLfloat)os->toNumber(-params+1), (GLfloat)os->toNumber(-params+2), (GLfloat)os->toNumber(-params+3));
			return 0;
		}

		static int glScalef(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glScalef (GLfloat x, GLfloat y, GLfloat z); */
			::glScalef((GLfloat)os->toNumber(-params+0), (GLfloat)os->toNumber(-params+1), (GLfloat)os->toNumber(-params+2));
			return 0;
		}

		static int glTexEnvf(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glTexEnvf (GLenum target, GLenum pname, GLfloat param); */
			::glTexEnvf((GLenum)os->toNumber(-params+0), (GLenum)os->toNumber(-params+1), (GLfloat)os->toNumber(-params+2));
			return 0;
		}

		/* skip: GL_API void GL_APIENTRY glTexEnvfv (GLenum target, GLenum pname, const GLfloat *params); */

		static int glTexParameterf(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glTexParameterf (GLenum target, GLenum pname, GLfloat param); */
			::glTexParameterf((GLenum)os->toNumber(-params+0), (GLenum)os->toNumber(-params+1), (GLfloat)os->toNumber(-params+2));
			return 0;
		}

		/* skip: GL_API void GL_APIENTRY glTexParameterfv (GLenum target, GLenum pname, const GLfloat *params); */

		static int glTranslatef(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glTranslatef (GLfloat x, GLfloat y, GLfloat z); */
			::glTranslatef((GLfloat)os->toNumber(-params+0), (GLfloat)os->toNumber(-params+1), (GLfloat)os->toNumber(-params+2));
			return 0;
		}

		/* Available in both Common and Common-Lite profiles */    static int glActiveTexture(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glActiveTexture (GLenum texture); */
			::glActiveTexture((GLenum)os->toNumber(-params+0));
			return 0;
		}

		static int glAlphaFuncx(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glAlphaFuncx (GLenum func, GLclampx ref); */
			::glAlphaFuncx((GLenum)os->toNumber(-params+0), (GLclampx)os->toNumber(-params+1));
			return 0;
		}

		static int glBindBuffer(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glBindBuffer (GLenum target, GLuint buffer); */
			::glBindBuffer((GLenum)os->toNumber(-params+0), (GLuint)os->toNumber(-params+1));
			return 0;
		}

		static int glBindTexture(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glBindTexture (GLenum target, GLuint texture); */
			::glBindTexture((GLenum)os->toNumber(-params+0), (GLuint)os->toNumber(-params+1));
			return 0;
		}

		static int glBlendFunc(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glBlendFunc (GLenum sfactor, GLenum dfactor); */
			::glBlendFunc((GLenum)os->toNumber(-params+0), (GLenum)os->toNumber(-params+1));
			return 0;
		}

		/* skip: GL_API void GL_APIENTRY glBufferData (GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage); */

		/* skip: GL_API void GL_APIENTRY glBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data); */

		static int glClear(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glClear (GLbitfield mask); */
			::glClear((GLbitfield)os->toNumber(-params+0));
			return 0;
		}

		static int glClearColorx(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glClearColorx (GLclampx red, GLclampx green, GLclampx blue, GLclampx alpha); */
			::glClearColorx((GLclampx)os->toNumber(-params+0), (GLclampx)os->toNumber(-params+1), (GLclampx)os->toNumber(-params+2), (GLclampx)os->toNumber(-params+3));
			return 0;
		}

		static int glClearDepthx(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glClearDepthx (GLclampx depth); */
			::glClearDepthx((GLclampx)os->toNumber(-params+0));
			return 0;
		}

		static int glClearStencil(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glClearStencil (GLint s); */
			::glClearStencil((GLint)os->toNumber(-params+0));
			return 0;
		}

		static int glClientActiveTexture(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glClientActiveTexture (GLenum texture); */
			::glClientActiveTexture((GLenum)os->toNumber(-params+0));
			return 0;
		}

		/* skip: GL_API void GL_APIENTRY glClipPlanex (GLenum plane, const GLfixed *equation); */

		static int glColor4ub(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glColor4ub (GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha); */
			::glColor4ub((GLubyte)os->toNumber(-params+0), (GLubyte)os->toNumber(-params+1), (GLubyte)os->toNumber(-params+2), (GLubyte)os->toNumber(-params+3));
			return 0;
		}

		static int glColor4x(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glColor4x (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha); */
			::glColor4x((GLfixed)os->toNumber(-params+0), (GLfixed)os->toNumber(-params+1), (GLfixed)os->toNumber(-params+2), (GLfixed)os->toNumber(-params+3));
			return 0;
		}

		static int glColorMask(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha); */
			::glColorMask((GLboolean)os->toNumber(-params+0), (GLboolean)os->toNumber(-params+1), (GLboolean)os->toNumber(-params+2), (GLboolean)os->toNumber(-params+3));
			return 0;
		}

		/* skip: GL_API void GL_APIENTRY glColorPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer); */

		/* skip: GL_API void GL_APIENTRY glCompressedTexImage2D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data); */

		/* skip: GL_API void GL_APIENTRY glCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data); */

		static int glCopyTexImage2D(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glCopyTexImage2D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border); */
			::glCopyTexImage2D((GLenum)os->toNumber(-params+0), (GLint)os->toNumber(-params+1), (GLenum)os->toNumber(-params+2), (GLint)os->toNumber(-params+3), (GLint)os->toNumber(-params+4), (GLsizei)os->toNumber(-params+5), (GLsizei)os->toNumber(-params+6), (GLint)os->toNumber(-params+7));
			return 0;
		}

		static int glCopyTexSubImage2D(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glCopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height); */
			::glCopyTexSubImage2D((GLenum)os->toNumber(-params+0), (GLint)os->toNumber(-params+1), (GLint)os->toNumber(-params+2), (GLint)os->toNumber(-params+3), (GLint)os->toNumber(-params+4), (GLint)os->toNumber(-params+5), (GLsizei)os->toNumber(-params+6), (GLsizei)os->toNumber(-params+7));
			return 0;
		}

		static int glCullFace(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glCullFace (GLenum mode); */
			::glCullFace((GLenum)os->toNumber(-params+0));
			return 0;
		}

		/* skip: GL_API void GL_APIENTRY glDeleteBuffers (GLsizei n, const GLuint *buffers); */

		/* skip: GL_API void GL_APIENTRY glDeleteTextures (GLsizei n, const GLuint *textures); */

		static int glDepthFunc(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glDepthFunc (GLenum func); */
			::glDepthFunc((GLenum)os->toNumber(-params+0));
			return 0;
		}

		static int glDepthMask(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glDepthMask (GLboolean flag); */
			::glDepthMask((GLboolean)os->toNumber(-params+0));
			return 0;
		}

		static int glDepthRangex(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glDepthRangex (GLclampx zNear, GLclampx zFar); */
			::glDepthRangex((GLclampx)os->toNumber(-params+0), (GLclampx)os->toNumber(-params+1));
			return 0;
		}

		static int glDisable(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glDisable (GLenum cap); */
			::glDisable((GLenum)os->toNumber(-params+0));
			return 0;
		}

		static int glDisableClientState(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glDisableClientState (GLenum array); */
			::glDisableClientState((GLenum)os->toNumber(-params+0));
			return 0;
		}

		static int glDrawArrays(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glDrawArrays (GLenum mode, GLint first, GLsizei count); */
			::glDrawArrays((GLenum)os->toNumber(-params+0), (GLint)os->toNumber(-params+1), (GLsizei)os->toNumber(-params+2));
			return 0;
		}

		/* skip: GL_API void GL_APIENTRY glDrawElements (GLenum mode, GLsizei count, GLenum type, const GLvoid *indices); */

		static int glEnable(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glEnable (GLenum cap); */
			::glEnable((GLenum)os->toNumber(-params+0));
			return 0;
		}

		static int glEnableClientState(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glEnableClientState (GLenum array); */
			::glEnableClientState((GLenum)os->toNumber(-params+0));
			return 0;
		}

		static int glFinish(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glFinish (void); */
			::glFinish();
			return 0;
		}

		static int glFlush(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glFlush (void); */
			::glFlush();
			return 0;
		}

		static int glFogx(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glFogx (GLenum pname, GLfixed param); */
			::glFogx((GLenum)os->toNumber(-params+0), (GLfixed)os->toNumber(-params+1));
			return 0;
		}

		/* skip: GL_API void GL_APIENTRY glFogxv (GLenum pname, const GLfixed *params); */

		static int glFrontFace(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glFrontFace (GLenum mode); */
			::glFrontFace((GLenum)os->toNumber(-params+0));
			return 0;
		}

		static int glFrustumx(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glFrustumx (GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar); */
			::glFrustumx((GLfixed)os->toNumber(-params+0), (GLfixed)os->toNumber(-params+1), (GLfixed)os->toNumber(-params+2), (GLfixed)os->toNumber(-params+3), (GLfixed)os->toNumber(-params+4), (GLfixed)os->toNumber(-params+5));
			return 0;
		}

		/* skip: GL_API void GL_APIENTRY glGetBooleanv (GLenum pname, GLboolean *params); */

		/* skip: GL_API void GL_APIENTRY glGetBufferParameteriv (GLenum target, GLenum pname, GLint *params); */

		/* skip: GL_API void GL_APIENTRY glGetClipPlanex (GLenum pname, GLfixed eqn[4]); */

		/* skip: GL_API void GL_APIENTRY glGenBuffers (GLsizei n, GLuint *buffers); */

		/* skip: GL_API void GL_APIENTRY glGenTextures (GLsizei n, GLuint *textures); */

		static int glGetError(OS * os, int params, int, int, void*)
		{
			/* GL_API GLenum GL_APIENTRY glGetError (void); */
			os->pushNumber((OS_NUMBER)::glGetError());
			return 1;
		}

		/* skip: GL_API void GL_APIENTRY glGetFixedv (GLenum pname, GLfixed *params); */

		/* skip: GL_API void GL_APIENTRY glGetIntegerv (GLenum pname, GLint *params); */

		/* skip: GL_API void GL_APIENTRY glGetLightxv (GLenum light, GLenum pname, GLfixed *params); */

		/* skip: GL_API void GL_APIENTRY glGetMaterialxv (GLenum face, GLenum pname, GLfixed *params); */

		/* skip: GL_API void GL_APIENTRY glGetPointerv (GLenum pname, GLvoid **params); */

		/* GL_API const GLubyte * GL_APIENTRY glGetString (GLenum name); */    /* skip: GL_API void GL_APIENTRY glGetTexEnviv (GLenum env, GLenum pname, GLint *params); */

		/* skip: GL_API void GL_APIENTRY glGetTexEnvxv (GLenum env, GLenum pname, GLfixed *params); */

		/* skip: GL_API void GL_APIENTRY glGetTexParameteriv (GLenum target, GLenum pname, GLint *params); */

		/* skip: GL_API void GL_APIENTRY glGetTexParameterxv (GLenum target, GLenum pname, GLfixed *params); */

		static int glHint(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glHint (GLenum target, GLenum mode); */
			::glHint((GLenum)os->toNumber(-params+0), (GLenum)os->toNumber(-params+1));
			return 0;
		}

		static int glIsBuffer(OS * os, int params, int, int, void*)
		{
			/* GL_API GLboolean GL_APIENTRY glIsBuffer (GLuint buffer); */
			os->pushBool(::glIsBuffer((GLuint)os->toNumber(-params+0)) ? true : false);
			return 1;
		}

		static int glIsEnabled(OS * os, int params, int, int, void*)
		{
			/* GL_API GLboolean GL_APIENTRY glIsEnabled (GLenum cap); */
			os->pushBool(::glIsEnabled((GLenum)os->toNumber(-params+0)) ? true : false);
			return 1;
		}

		static int glIsTexture(OS * os, int params, int, int, void*)
		{
			/* GL_API GLboolean GL_APIENTRY glIsTexture (GLuint texture); */
			os->pushBool(::glIsTexture((GLuint)os->toNumber(-params+0)) ? true : false);
			return 1;
		}

		static int glLightModelx(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glLightModelx (GLenum pname, GLfixed param); */
			::glLightModelx((GLenum)os->toNumber(-params+0), (GLfixed)os->toNumber(-params+1));
			return 0;
		}

		/* skip: GL_API void GL_APIENTRY glLightModelxv (GLenum pname, const GLfixed *params); */

		static int glLightx(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glLightx (GLenum light, GLenum pname, GLfixed param); */
			::glLightx((GLenum)os->toNumber(-params+0), (GLenum)os->toNumber(-params+1), (GLfixed)os->toNumber(-params+2));
			return 0;
		}

		/* skip: GL_API void GL_APIENTRY glLightxv (GLenum light, GLenum pname, const GLfixed *params); */

		static int glLineWidthx(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glLineWidthx (GLfixed width); */
			::glLineWidthx((GLfixed)os->toNumber(-params+0));
			return 0;
		}

		static int glLoadIdentity(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glLoadIdentity (void); */
			::glLoadIdentity();
			return 0;
		}

		/* skip: GL_API void GL_APIENTRY glLoadMatrixx (const GLfixed *m); */

		static int glLogicOp(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glLogicOp (GLenum opcode); */
			::glLogicOp((GLenum)os->toNumber(-params+0));
			return 0;
		}

		static int glMaterialx(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glMaterialx (GLenum face, GLenum pname, GLfixed param); */
			::glMaterialx((GLenum)os->toNumber(-params+0), (GLenum)os->toNumber(-params+1), (GLfixed)os->toNumber(-params+2));
			return 0;
		}

		/* skip: GL_API void GL_APIENTRY glMaterialxv (GLenum face, GLenum pname, const GLfixed *params); */

		static int glMatrixMode(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glMatrixMode (GLenum mode); */
			::glMatrixMode((GLenum)os->toNumber(-params+0));
			return 0;
		}

		/* skip: GL_API void GL_APIENTRY glMultMatrixx (const GLfixed *m); */

		static int glMultiTexCoord4x(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glMultiTexCoord4x (GLenum target, GLfixed s, GLfixed t, GLfixed r, GLfixed q); */
			::glMultiTexCoord4x((GLenum)os->toNumber(-params+0), (GLfixed)os->toNumber(-params+1), (GLfixed)os->toNumber(-params+2), (GLfixed)os->toNumber(-params+3), (GLfixed)os->toNumber(-params+4));
			return 0;
		}

		static int glNormal3x(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glNormal3x (GLfixed nx, GLfixed ny, GLfixed nz); */
			::glNormal3x((GLfixed)os->toNumber(-params+0), (GLfixed)os->toNumber(-params+1), (GLfixed)os->toNumber(-params+2));
			return 0;
		}

		/* skip: GL_API void GL_APIENTRY glNormalPointer (GLenum type, GLsizei stride, const GLvoid *pointer); */

		static int glOrthox(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glOrthox (GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar); */
			::glOrthox((GLfixed)os->toNumber(-params+0), (GLfixed)os->toNumber(-params+1), (GLfixed)os->toNumber(-params+2), (GLfixed)os->toNumber(-params+3), (GLfixed)os->toNumber(-params+4), (GLfixed)os->toNumber(-params+5));
			return 0;
		}

		static int glPixelStorei(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glPixelStorei (GLenum pname, GLint param); */
			::glPixelStorei((GLenum)os->toNumber(-params+0), (GLint)os->toNumber(-params+1));
			return 0;
		}

		static int glPointParameterx(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glPointParameterx (GLenum pname, GLfixed param); */
			::glPointParameterx((GLenum)os->toNumber(-params+0), (GLfixed)os->toNumber(-params+1));
			return 0;
		}

		/* skip: GL_API void GL_APIENTRY glPointParameterxv (GLenum pname, const GLfixed *params); */

		static int glPointSizex(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glPointSizex (GLfixed size); */
			::glPointSizex((GLfixed)os->toNumber(-params+0));
			return 0;
		}

		static int glPolygonOffsetx(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glPolygonOffsetx (GLfixed factor, GLfixed units); */
			::glPolygonOffsetx((GLfixed)os->toNumber(-params+0), (GLfixed)os->toNumber(-params+1));
			return 0;
		}

		static int glPopMatrix(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glPopMatrix (void); */
			::glPopMatrix();
			return 0;
		}

		static int glPushMatrix(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glPushMatrix (void); */
			::glPushMatrix();
			return 0;
		}

		/* skip: GL_API void GL_APIENTRY glReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels); */

		static int glRotatex(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glRotatex (GLfixed angle, GLfixed x, GLfixed y, GLfixed z); */
			::glRotatex((GLfixed)os->toNumber(-params+0), (GLfixed)os->toNumber(-params+1), (GLfixed)os->toNumber(-params+2), (GLfixed)os->toNumber(-params+3));
			return 0;
		}

		static int glSampleCoverage(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glSampleCoverage (GLclampf value, GLboolean invert); */
			::glSampleCoverage((GLclampf)os->toNumber(-params+0), (GLboolean)os->toNumber(-params+1));
			return 0;
		}

		static int glSampleCoveragex(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glSampleCoveragex (GLclampx value, GLboolean invert); */
			::glSampleCoveragex((GLclampx)os->toNumber(-params+0), (GLboolean)os->toNumber(-params+1));
			return 0;
		}

		static int glScalex(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glScalex (GLfixed x, GLfixed y, GLfixed z); */
			::glScalex((GLfixed)os->toNumber(-params+0), (GLfixed)os->toNumber(-params+1), (GLfixed)os->toNumber(-params+2));
			return 0;
		}

		static int glScissor(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glScissor (GLint x, GLint y, GLsizei width, GLsizei height); */
			::glScissor((GLint)os->toNumber(-params+0), (GLint)os->toNumber(-params+1), (GLsizei)os->toNumber(-params+2), (GLsizei)os->toNumber(-params+3));
			return 0;
		}

		static int glShadeModel(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glShadeModel (GLenum mode); */
			::glShadeModel((GLenum)os->toNumber(-params+0));
			return 0;
		}

		static int glStencilFunc(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glStencilFunc (GLenum func, GLint ref, GLuint mask); */
			::glStencilFunc((GLenum)os->toNumber(-params+0), (GLint)os->toNumber(-params+1), (GLuint)os->toNumber(-params+2));
			return 0;
		}

		static int glStencilMask(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glStencilMask (GLuint mask); */
			::glStencilMask((GLuint)os->toNumber(-params+0));
			return 0;
		}

		static int glStencilOp(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glStencilOp (GLenum fail, GLenum zfail, GLenum zpass); */
			::glStencilOp((GLenum)os->toNumber(-params+0), (GLenum)os->toNumber(-params+1), (GLenum)os->toNumber(-params+2));
			return 0;
		}

		/* skip: GL_API void GL_APIENTRY glTexCoordPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer); */

		static int glTexEnvi(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glTexEnvi (GLenum target, GLenum pname, GLint param); */
			::glTexEnvi((GLenum)os->toNumber(-params+0), (GLenum)os->toNumber(-params+1), (GLint)os->toNumber(-params+2));
			return 0;
		}

		static int glTexEnvx(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glTexEnvx (GLenum target, GLenum pname, GLfixed param); */
			::glTexEnvx((GLenum)os->toNumber(-params+0), (GLenum)os->toNumber(-params+1), (GLfixed)os->toNumber(-params+2));
			return 0;
		}

		/* skip: GL_API void GL_APIENTRY glTexEnviv (GLenum target, GLenum pname, const GLint *params); */

		/* skip: GL_API void GL_APIENTRY glTexEnvxv (GLenum target, GLenum pname, const GLfixed *params); */

		/* skip: GL_API void GL_APIENTRY glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels); */

		static int glTexParameteri(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glTexParameteri (GLenum target, GLenum pname, GLint param); */
			::glTexParameteri((GLenum)os->toNumber(-params+0), (GLenum)os->toNumber(-params+1), (GLint)os->toNumber(-params+2));
			return 0;
		}

		static int glTexParameterx(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glTexParameterx (GLenum target, GLenum pname, GLfixed param); */
			::glTexParameterx((GLenum)os->toNumber(-params+0), (GLenum)os->toNumber(-params+1), (GLfixed)os->toNumber(-params+2));
			return 0;
		}

		/* skip: GL_API void GL_APIENTRY glTexParameteriv (GLenum target, GLenum pname, const GLint *params); */

		/* skip: GL_API void GL_APIENTRY glTexParameterxv (GLenum target, GLenum pname, const GLfixed *params); */

		/* skip: GL_API void GL_APIENTRY glTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels); */

		static int glTranslatex(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glTranslatex (GLfixed x, GLfixed y, GLfixed z); */
			::glTranslatex((GLfixed)os->toNumber(-params+0), (GLfixed)os->toNumber(-params+1), (GLfixed)os->toNumber(-params+2));
			return 0;
		}

		/* skip: GL_API void GL_APIENTRY glVertexPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer); */

		static int glViewport(OS * os, int params, int, int, void*)
		{
			/* GL_API void GL_APIENTRY glViewport (GLint x, GLint y, GLsizei width, GLsizei height); */
			::glViewport((GLint)os->toNumber(-params+0), (GLint)os->toNumber(-params+1), (GLsizei)os->toNumber(-params+2), (GLsizei)os->toNumber(-params+3));
			return 0;
		}


	};

	OS::FuncDef list[] = {
		{OS_TEXT("glAlphaFunc"), OpenGL::glAlphaFunc},
		{OS_TEXT("glClearColor"), OpenGL::glClearColor},
		{OS_TEXT("glClearDepthf"), OpenGL::glClearDepthf},
		{OS_TEXT("glColor4f"), OpenGL::glColor4f},
		{OS_TEXT("glDepthRangef"), OpenGL::glDepthRangef},
		{OS_TEXT("glFogf"), OpenGL::glFogf},
		{OS_TEXT("glFrustumf"), OpenGL::glFrustumf},
		{OS_TEXT("glLightModelf"), OpenGL::glLightModelf},
		{OS_TEXT("glLightf"), OpenGL::glLightf},
		{OS_TEXT("glLineWidth"), OpenGL::glLineWidth},
		{OS_TEXT("glMaterialf"), OpenGL::glMaterialf},
		{OS_TEXT("glMultiTexCoord4f"), OpenGL::glMultiTexCoord4f},
		{OS_TEXT("glNormal3f"), OpenGL::glNormal3f},
		{OS_TEXT("glOrthof"), OpenGL::glOrthof},
		{OS_TEXT("glPointParameterf"), OpenGL::glPointParameterf},
		{OS_TEXT("glPointSize"), OpenGL::glPointSize},
		{OS_TEXT("glPolygonOffset"), OpenGL::glPolygonOffset},
		{OS_TEXT("glRotatef"), OpenGL::glRotatef},
		{OS_TEXT("glScalef"), OpenGL::glScalef},
		{OS_TEXT("glTexEnvf"), OpenGL::glTexEnvf},
		{OS_TEXT("glTexParameterf"), OpenGL::glTexParameterf},
		{OS_TEXT("glTranslatef"), OpenGL::glTranslatef},
		{OS_TEXT("glActiveTexture"), OpenGL::glActiveTexture},
		{OS_TEXT("glAlphaFuncx"), OpenGL::glAlphaFuncx},
		{OS_TEXT("glBindBuffer"), OpenGL::glBindBuffer},
		{OS_TEXT("glBindTexture"), OpenGL::glBindTexture},
		{OS_TEXT("glBlendFunc"), OpenGL::glBlendFunc},
		{OS_TEXT("glClear"), OpenGL::glClear},
		{OS_TEXT("glClearColorx"), OpenGL::glClearColorx},
		{OS_TEXT("glClearDepthx"), OpenGL::glClearDepthx},
		{OS_TEXT("glClearStencil"), OpenGL::glClearStencil},
		{OS_TEXT("glClientActiveTexture"), OpenGL::glClientActiveTexture},
		{OS_TEXT("glColor4ub"), OpenGL::glColor4ub},
		{OS_TEXT("glColor4x"), OpenGL::glColor4x},
		{OS_TEXT("glColorMask"), OpenGL::glColorMask},
		{OS_TEXT("glCopyTexImage2D"), OpenGL::glCopyTexImage2D},
		{OS_TEXT("glCopyTexSubImage2D"), OpenGL::glCopyTexSubImage2D},
		{OS_TEXT("glCullFace"), OpenGL::glCullFace},
		{OS_TEXT("glDepthFunc"), OpenGL::glDepthFunc},
		{OS_TEXT("glDepthMask"), OpenGL::glDepthMask},
		{OS_TEXT("glDepthRangex"), OpenGL::glDepthRangex},
		{OS_TEXT("glDisable"), OpenGL::glDisable},
		{OS_TEXT("glDisableClientState"), OpenGL::glDisableClientState},
		{OS_TEXT("glDrawArrays"), OpenGL::glDrawArrays},
		{OS_TEXT("glEnable"), OpenGL::glEnable},
		{OS_TEXT("glEnableClientState"), OpenGL::glEnableClientState},
		{OS_TEXT("glFinish"), OpenGL::glFinish},
		{OS_TEXT("glFlush"), OpenGL::glFlush},
		{OS_TEXT("glFogx"), OpenGL::glFogx},
		{OS_TEXT("glFrontFace"), OpenGL::glFrontFace},
		{OS_TEXT("glFrustumx"), OpenGL::glFrustumx},
		{OS_TEXT("glGetError"), OpenGL::glGetError},
		{OS_TEXT("glHint"), OpenGL::glHint},
		{OS_TEXT("glIsBuffer"), OpenGL::glIsBuffer},
		{OS_TEXT("glIsEnabled"), OpenGL::glIsEnabled},
		{OS_TEXT("glIsTexture"), OpenGL::glIsTexture},
		{OS_TEXT("glLightModelx"), OpenGL::glLightModelx},
		{OS_TEXT("glLightx"), OpenGL::glLightx},
		{OS_TEXT("glLineWidthx"), OpenGL::glLineWidthx},
		{OS_TEXT("glLoadIdentity"), OpenGL::glLoadIdentity},
		{OS_TEXT("glLogicOp"), OpenGL::glLogicOp},
		{OS_TEXT("glMaterialx"), OpenGL::glMaterialx},
		{OS_TEXT("glMatrixMode"), OpenGL::glMatrixMode},
		{OS_TEXT("glMultiTexCoord4x"), OpenGL::glMultiTexCoord4x},
		{OS_TEXT("glNormal3x"), OpenGL::glNormal3x},
		{OS_TEXT("glOrthox"), OpenGL::glOrthox},
		{OS_TEXT("glPixelStorei"), OpenGL::glPixelStorei},
		{OS_TEXT("glPointParameterx"), OpenGL::glPointParameterx},
		{OS_TEXT("glPointSizex"), OpenGL::glPointSizex},
		{OS_TEXT("glPolygonOffsetx"), OpenGL::glPolygonOffsetx},
		{OS_TEXT("glPopMatrix"), OpenGL::glPopMatrix},
		{OS_TEXT("glPushMatrix"), OpenGL::glPushMatrix},
		{OS_TEXT("glRotatex"), OpenGL::glRotatex},
		{OS_TEXT("glSampleCoverage"), OpenGL::glSampleCoverage},
		{OS_TEXT("glSampleCoveragex"), OpenGL::glSampleCoveragex},
		{OS_TEXT("glScalex"), OpenGL::glScalex},
		{OS_TEXT("glScissor"), OpenGL::glScissor},
		{OS_TEXT("glShadeModel"), OpenGL::glShadeModel},
		{OS_TEXT("glStencilFunc"), OpenGL::glStencilFunc},
		{OS_TEXT("glStencilMask"), OpenGL::glStencilMask},
		{OS_TEXT("glStencilOp"), OpenGL::glStencilOp},
		{OS_TEXT("glTexEnvi"), OpenGL::glTexEnvi},
		{OS_TEXT("glTexEnvx"), OpenGL::glTexEnvx},
		{OS_TEXT("glTexParameteri"), OpenGL::glTexParameteri},
		{OS_TEXT("glTexParameterx"), OpenGL::glTexParameterx},
		{OS_TEXT("glTranslatex"), OpenGL::glTranslatex},
		{OS_TEXT("glViewport"), OpenGL::glViewport},
		{}
	};

	OS::NumberDef numbers[] = {
		/* OpenGL ES core versions */
		{OS_TEXT("GL_VERSION_ES_CM_1_0"), GL_VERSION_ES_CM_1_0},
		{OS_TEXT("GL_VERSION_ES_CL_1_0"), GL_VERSION_ES_CL_1_0},
		{OS_TEXT("GL_VERSION_ES_CM_1_1"), GL_VERSION_ES_CM_1_1},
		{OS_TEXT("GL_VERSION_ES_CL_1_1"), GL_VERSION_ES_CL_1_1},

		/* ClearBufferMask */
		{OS_TEXT("GL_DEPTH_BUFFER_BIT"), GL_DEPTH_BUFFER_BIT},
		{OS_TEXT("GL_STENCIL_BUFFER_BIT"), GL_STENCIL_BUFFER_BIT},
		{OS_TEXT("GL_COLOR_BUFFER_BIT"), GL_COLOR_BUFFER_BIT},

		/* Boolean */
		{OS_TEXT("GL_FALSE"), GL_FALSE},
		{OS_TEXT("GL_TRUE"), GL_TRUE},

		/* BeginMode */
		{OS_TEXT("GL_POINTS"), GL_POINTS},
		{OS_TEXT("GL_LINES"), GL_LINES},
		{OS_TEXT("GL_LINE_LOOP"), GL_LINE_LOOP},
		{OS_TEXT("GL_LINE_STRIP"), GL_LINE_STRIP},
		{OS_TEXT("GL_TRIANGLES"), GL_TRIANGLES},
		{OS_TEXT("GL_TRIANGLE_STRIP"), GL_TRIANGLE_STRIP},
		{OS_TEXT("GL_TRIANGLE_FAN"), GL_TRIANGLE_FAN},

		/* AlphaFunction */
		{OS_TEXT("GL_NEVER"), GL_NEVER},
		{OS_TEXT("GL_LESS"), GL_LESS},
		{OS_TEXT("GL_EQUAL"), GL_EQUAL},
		{OS_TEXT("GL_LEQUAL"), GL_LEQUAL},
		{OS_TEXT("GL_GREATER"), GL_GREATER},
		{OS_TEXT("GL_NOTEQUAL"), GL_NOTEQUAL},
		{OS_TEXT("GL_GEQUAL"), GL_GEQUAL},
		{OS_TEXT("GL_ALWAYS"), GL_ALWAYS},

		/* BlendingFactorDest */
		{OS_TEXT("GL_ZERO"), GL_ZERO},
		{OS_TEXT("GL_ONE"), GL_ONE},
		{OS_TEXT("GL_SRC_COLOR"), GL_SRC_COLOR},
		{OS_TEXT("GL_ONE_MINUS_SRC_COLOR"), GL_ONE_MINUS_SRC_COLOR},
		{OS_TEXT("GL_SRC_ALPHA"), GL_SRC_ALPHA},
		{OS_TEXT("GL_ONE_MINUS_SRC_ALPHA"), GL_ONE_MINUS_SRC_ALPHA},
		{OS_TEXT("GL_DST_ALPHA"), GL_DST_ALPHA},
		{OS_TEXT("GL_ONE_MINUS_DST_ALPHA"), GL_ONE_MINUS_DST_ALPHA},

		/* BlendingFactorSrc */
		/*      GL_ZERO */
		/*      GL_ONE */
		{OS_TEXT("GL_DST_COLOR"), GL_DST_COLOR},
		{OS_TEXT("GL_ONE_MINUS_DST_COLOR"), GL_ONE_MINUS_DST_COLOR},
		{OS_TEXT("GL_SRC_ALPHA_SATURATE"), GL_SRC_ALPHA_SATURATE},
		/*      GL_SRC_ALPHA */
		/*      GL_ONE_MINUS_SRC_ALPHA */
		/*      GL_DST_ALPHA */
		/*      GL_ONE_MINUS_DST_ALPHA */

		/* ClipPlaneName */
		{OS_TEXT("GL_CLIP_PLANE0"), GL_CLIP_PLANE0},
		{OS_TEXT("GL_CLIP_PLANE1"), GL_CLIP_PLANE1},
		{OS_TEXT("GL_CLIP_PLANE2"), GL_CLIP_PLANE2},
		{OS_TEXT("GL_CLIP_PLANE3"), GL_CLIP_PLANE3},
		{OS_TEXT("GL_CLIP_PLANE4"), GL_CLIP_PLANE4},
		{OS_TEXT("GL_CLIP_PLANE5"), GL_CLIP_PLANE5},

		/* ColorMaterialFace */
		/*      GL_FRONT_AND_BACK */

		/* ColorMaterialParameter */
		/*      GL_AMBIENT_AND_DIFFUSE */

		/* ColorPointerType */
		/*      GL_UNSIGNED_BYTE */
		/*      GL_FLOAT */
		/*      GL_FIXED */

		/* CullFaceMode */
		{OS_TEXT("GL_FRONT"), GL_FRONT},
		{OS_TEXT("GL_BACK"), GL_BACK},
		{OS_TEXT("GL_FRONT_AND_BACK"), GL_FRONT_AND_BACK},

		/* DepthFunction */
		/*      GL_NEVER */
		/*      GL_LESS */
		/*      GL_EQUAL */
		/*      GL_LEQUAL */
		/*      GL_GREATER */
		/*      GL_NOTEQUAL */
		/*      GL_GEQUAL */
		/*      GL_ALWAYS */

		/* EnableCap */
		{OS_TEXT("GL_FOG"), GL_FOG},
		{OS_TEXT("GL_LIGHTING"), GL_LIGHTING},
		{OS_TEXT("GL_TEXTURE_2D"), GL_TEXTURE_2D},
		{OS_TEXT("GL_CULL_FACE"), GL_CULL_FACE},
		{OS_TEXT("GL_ALPHA_TEST"), GL_ALPHA_TEST},
		{OS_TEXT("GL_BLEND"), GL_BLEND},
		{OS_TEXT("GL_COLOR_LOGIC_OP"), GL_COLOR_LOGIC_OP},
		{OS_TEXT("GL_DITHER"), GL_DITHER},
		{OS_TEXT("GL_STENCIL_TEST"), GL_STENCIL_TEST},
		{OS_TEXT("GL_DEPTH_TEST"), GL_DEPTH_TEST},
		/*      GL_LIGHT0 */
		/*      GL_LIGHT1 */
		/*      GL_LIGHT2 */
		/*      GL_LIGHT3 */
		/*      GL_LIGHT4 */
		/*      GL_LIGHT5 */
		/*      GL_LIGHT6 */
		/*      GL_LIGHT7 */
		{OS_TEXT("GL_POINT_SMOOTH"), GL_POINT_SMOOTH},
		{OS_TEXT("GL_LINE_SMOOTH"), GL_LINE_SMOOTH},
		{OS_TEXT("GL_SCISSOR_TEST"), GL_SCISSOR_TEST},
		{OS_TEXT("GL_COLOR_MATERIAL"), GL_COLOR_MATERIAL},
		{OS_TEXT("GL_NORMALIZE"), GL_NORMALIZE},
		{OS_TEXT("GL_RESCALE_NORMAL"), GL_RESCALE_NORMAL},
		{OS_TEXT("GL_POLYGON_OFFSET_FILL"), GL_POLYGON_OFFSET_FILL},
		{OS_TEXT("GL_VERTEX_ARRAY"), GL_VERTEX_ARRAY},
		{OS_TEXT("GL_NORMAL_ARRAY"), GL_NORMAL_ARRAY},
		{OS_TEXT("GL_COLOR_ARRAY"), GL_COLOR_ARRAY},
		{OS_TEXT("GL_TEXTURE_COORD_ARRAY"), GL_TEXTURE_COORD_ARRAY},
		{OS_TEXT("GL_MULTISAMPLE"), GL_MULTISAMPLE},
		{OS_TEXT("GL_SAMPLE_ALPHA_TO_COVERAGE"), GL_SAMPLE_ALPHA_TO_COVERAGE},
		{OS_TEXT("GL_SAMPLE_ALPHA_TO_ONE"), GL_SAMPLE_ALPHA_TO_ONE},
		{OS_TEXT("GL_SAMPLE_COVERAGE"), GL_SAMPLE_COVERAGE},

		/* ErrorCode */
		{OS_TEXT("GL_NO_ERROR"), GL_NO_ERROR},
		{OS_TEXT("GL_INVALID_ENUM"), GL_INVALID_ENUM},
		{OS_TEXT("GL_INVALID_VALUE"), GL_INVALID_VALUE},
		{OS_TEXT("GL_INVALID_OPERATION"), GL_INVALID_OPERATION},
		{OS_TEXT("GL_STACK_OVERFLOW"), GL_STACK_OVERFLOW},
		{OS_TEXT("GL_STACK_UNDERFLOW"), GL_STACK_UNDERFLOW},
		{OS_TEXT("GL_OUT_OF_MEMORY"), GL_OUT_OF_MEMORY},

		/* FogMode */
		/*      GL_LINEAR */
		{OS_TEXT("GL_EXP"), GL_EXP},
		{OS_TEXT("GL_EXP2"), GL_EXP2},

		/* FogParameter */
		{OS_TEXT("GL_FOG_DENSITY"), GL_FOG_DENSITY},
		{OS_TEXT("GL_FOG_START"), GL_FOG_START},
		{OS_TEXT("GL_FOG_END"), GL_FOG_END},
		{OS_TEXT("GL_FOG_MODE"), GL_FOG_MODE},
		{OS_TEXT("GL_FOG_COLOR"), GL_FOG_COLOR},

		/* FrontFaceDirection */
		{OS_TEXT("GL_CW"), GL_CW},
		{OS_TEXT("GL_CCW"), GL_CCW},

		/* GetPName */
		{OS_TEXT("GL_CURRENT_COLOR"), GL_CURRENT_COLOR},
		{OS_TEXT("GL_CURRENT_NORMAL"), GL_CURRENT_NORMAL},
		{OS_TEXT("GL_CURRENT_TEXTURE_COORDS"), GL_CURRENT_TEXTURE_COORDS},
		{OS_TEXT("GL_POINT_SIZE"), GL_POINT_SIZE},
		{OS_TEXT("GL_POINT_SIZE_MIN"), GL_POINT_SIZE_MIN},
		{OS_TEXT("GL_POINT_SIZE_MAX"), GL_POINT_SIZE_MAX},
		{OS_TEXT("GL_POINT_FADE_THRESHOLD_SIZE"), GL_POINT_FADE_THRESHOLD_SIZE},
		{OS_TEXT("GL_POINT_DISTANCE_ATTENUATION"), GL_POINT_DISTANCE_ATTENUATION},
		{OS_TEXT("GL_SMOOTH_POINT_SIZE_RANGE"), GL_SMOOTH_POINT_SIZE_RANGE},
		{OS_TEXT("GL_LINE_WIDTH"), GL_LINE_WIDTH},
		{OS_TEXT("GL_SMOOTH_LINE_WIDTH_RANGE"), GL_SMOOTH_LINE_WIDTH_RANGE},
		{OS_TEXT("GL_ALIASED_POINT_SIZE_RANGE"), GL_ALIASED_POINT_SIZE_RANGE},
		{OS_TEXT("GL_ALIASED_LINE_WIDTH_RANGE"), GL_ALIASED_LINE_WIDTH_RANGE},
		{OS_TEXT("GL_CULL_FACE_MODE"), GL_CULL_FACE_MODE},
		{OS_TEXT("GL_FRONT_FACE"), GL_FRONT_FACE},
		{OS_TEXT("GL_SHADE_MODEL"), GL_SHADE_MODEL},
		{OS_TEXT("GL_DEPTH_RANGE"), GL_DEPTH_RANGE},
		{OS_TEXT("GL_DEPTH_WRITEMASK"), GL_DEPTH_WRITEMASK},
		{OS_TEXT("GL_DEPTH_CLEAR_VALUE"), GL_DEPTH_CLEAR_VALUE},
		{OS_TEXT("GL_DEPTH_FUNC"), GL_DEPTH_FUNC},
		{OS_TEXT("GL_STENCIL_CLEAR_VALUE"), GL_STENCIL_CLEAR_VALUE},
		{OS_TEXT("GL_STENCIL_FUNC"), GL_STENCIL_FUNC},
		{OS_TEXT("GL_STENCIL_VALUE_MASK"), GL_STENCIL_VALUE_MASK},
		{OS_TEXT("GL_STENCIL_FAIL"), GL_STENCIL_FAIL},
		{OS_TEXT("GL_STENCIL_PASS_DEPTH_FAIL"), GL_STENCIL_PASS_DEPTH_FAIL},
		{OS_TEXT("GL_STENCIL_PASS_DEPTH_PASS"), GL_STENCIL_PASS_DEPTH_PASS},
		{OS_TEXT("GL_STENCIL_REF"), GL_STENCIL_REF},
		{OS_TEXT("GL_STENCIL_WRITEMASK"), GL_STENCIL_WRITEMASK},
		{OS_TEXT("GL_MATRIX_MODE"), GL_MATRIX_MODE},
		{OS_TEXT("GL_VIEWPORT"), GL_VIEWPORT},
		{OS_TEXT("GL_MODELVIEW_STACK_DEPTH"), GL_MODELVIEW_STACK_DEPTH},
		{OS_TEXT("GL_PROJECTION_STACK_DEPTH"), GL_PROJECTION_STACK_DEPTH},
		{OS_TEXT("GL_TEXTURE_STACK_DEPTH"), GL_TEXTURE_STACK_DEPTH},
		{OS_TEXT("GL_MODELVIEW_MATRIX"), GL_MODELVIEW_MATRIX},
		{OS_TEXT("GL_PROJECTION_MATRIX"), GL_PROJECTION_MATRIX},
		{OS_TEXT("GL_TEXTURE_MATRIX"), GL_TEXTURE_MATRIX},
		{OS_TEXT("GL_ALPHA_TEST_FUNC"), GL_ALPHA_TEST_FUNC},
		{OS_TEXT("GL_ALPHA_TEST_REF"), GL_ALPHA_TEST_REF},
		{OS_TEXT("GL_BLEND_DST"), GL_BLEND_DST},
		{OS_TEXT("GL_BLEND_SRC"), GL_BLEND_SRC},
		{OS_TEXT("GL_LOGIC_OP_MODE"), GL_LOGIC_OP_MODE},
		{OS_TEXT("GL_SCISSOR_BOX"), GL_SCISSOR_BOX},
		{OS_TEXT("GL_SCISSOR_TEST"), GL_SCISSOR_TEST},
		{OS_TEXT("GL_COLOR_CLEAR_VALUE"), GL_COLOR_CLEAR_VALUE},
		{OS_TEXT("GL_COLOR_WRITEMASK"), GL_COLOR_WRITEMASK},
		{OS_TEXT("GL_UNPACK_ALIGNMENT"), GL_UNPACK_ALIGNMENT},
		{OS_TEXT("GL_PACK_ALIGNMENT"), GL_PACK_ALIGNMENT},
		{OS_TEXT("GL_MAX_LIGHTS"), GL_MAX_LIGHTS},
		{OS_TEXT("GL_MAX_CLIP_PLANES"), GL_MAX_CLIP_PLANES},
		{OS_TEXT("GL_MAX_TEXTURE_SIZE"), GL_MAX_TEXTURE_SIZE},
		{OS_TEXT("GL_MAX_MODELVIEW_STACK_DEPTH"), GL_MAX_MODELVIEW_STACK_DEPTH},
		{OS_TEXT("GL_MAX_PROJECTION_STACK_DEPTH"), GL_MAX_PROJECTION_STACK_DEPTH},
		{OS_TEXT("GL_MAX_TEXTURE_STACK_DEPTH"), GL_MAX_TEXTURE_STACK_DEPTH},
		{OS_TEXT("GL_MAX_VIEWPORT_DIMS"), GL_MAX_VIEWPORT_DIMS},
		{OS_TEXT("GL_MAX_TEXTURE_UNITS"), GL_MAX_TEXTURE_UNITS},
		{OS_TEXT("GL_SUBPIXEL_BITS"), GL_SUBPIXEL_BITS},
		{OS_TEXT("GL_RED_BITS"), GL_RED_BITS},
		{OS_TEXT("GL_GREEN_BITS"), GL_GREEN_BITS},
		{OS_TEXT("GL_BLUE_BITS"), GL_BLUE_BITS},
		{OS_TEXT("GL_ALPHA_BITS"), GL_ALPHA_BITS},
		{OS_TEXT("GL_DEPTH_BITS"), GL_DEPTH_BITS},
		{OS_TEXT("GL_STENCIL_BITS"), GL_STENCIL_BITS},
		{OS_TEXT("GL_POLYGON_OFFSET_UNITS"), GL_POLYGON_OFFSET_UNITS},
		{OS_TEXT("GL_POLYGON_OFFSET_FILL"), GL_POLYGON_OFFSET_FILL},
		{OS_TEXT("GL_POLYGON_OFFSET_FACTOR"), GL_POLYGON_OFFSET_FACTOR},
		{OS_TEXT("GL_TEXTURE_BINDING_2D"), GL_TEXTURE_BINDING_2D},
		{OS_TEXT("GL_VERTEX_ARRAY_SIZE"), GL_VERTEX_ARRAY_SIZE},
		{OS_TEXT("GL_VERTEX_ARRAY_TYPE"), GL_VERTEX_ARRAY_TYPE},
		{OS_TEXT("GL_VERTEX_ARRAY_STRIDE"), GL_VERTEX_ARRAY_STRIDE},
		{OS_TEXT("GL_NORMAL_ARRAY_TYPE"), GL_NORMAL_ARRAY_TYPE},
		{OS_TEXT("GL_NORMAL_ARRAY_STRIDE"), GL_NORMAL_ARRAY_STRIDE},
		{OS_TEXT("GL_COLOR_ARRAY_SIZE"), GL_COLOR_ARRAY_SIZE},
		{OS_TEXT("GL_COLOR_ARRAY_TYPE"), GL_COLOR_ARRAY_TYPE},
		{OS_TEXT("GL_COLOR_ARRAY_STRIDE"), GL_COLOR_ARRAY_STRIDE},
		{OS_TEXT("GL_TEXTURE_COORD_ARRAY_SIZE"), GL_TEXTURE_COORD_ARRAY_SIZE},
		{OS_TEXT("GL_TEXTURE_COORD_ARRAY_TYPE"), GL_TEXTURE_COORD_ARRAY_TYPE},
		{OS_TEXT("GL_TEXTURE_COORD_ARRAY_STRIDE"), GL_TEXTURE_COORD_ARRAY_STRIDE},
		{OS_TEXT("GL_VERTEX_ARRAY_POINTER"), GL_VERTEX_ARRAY_POINTER},
		{OS_TEXT("GL_NORMAL_ARRAY_POINTER"), GL_NORMAL_ARRAY_POINTER},
		{OS_TEXT("GL_COLOR_ARRAY_POINTER"), GL_COLOR_ARRAY_POINTER},
		{OS_TEXT("GL_TEXTURE_COORD_ARRAY_POINTER"), GL_TEXTURE_COORD_ARRAY_POINTER},
		{OS_TEXT("GL_SAMPLE_BUFFERS"), GL_SAMPLE_BUFFERS},
		{OS_TEXT("GL_SAMPLES"), GL_SAMPLES},
		{OS_TEXT("GL_SAMPLE_COVERAGE_VALUE"), GL_SAMPLE_COVERAGE_VALUE},
		{OS_TEXT("GL_SAMPLE_COVERAGE_INVERT"), GL_SAMPLE_COVERAGE_INVERT},

		/* GetTextureParameter */
		/*      GL_TEXTURE_MAG_FILTER */
		/*      GL_TEXTURE_MIN_FILTER */
		/*      GL_TEXTURE_WRAP_S */
		/*      GL_TEXTURE_WRAP_T */

		{OS_TEXT("GL_NUM_COMPRESSED_TEXTURE_FORMATS"), GL_NUM_COMPRESSED_TEXTURE_FORMATS},
		{OS_TEXT("GL_COMPRESSED_TEXTURE_FORMATS"), GL_COMPRESSED_TEXTURE_FORMATS},

		/* HintMode */
		{OS_TEXT("GL_DONT_CARE"), GL_DONT_CARE},
		{OS_TEXT("GL_FASTEST"), GL_FASTEST},
		{OS_TEXT("GL_NICEST"), GL_NICEST},

		/* HintTarget */
		{OS_TEXT("GL_PERSPECTIVE_CORRECTION_HINT"), GL_PERSPECTIVE_CORRECTION_HINT},
		{OS_TEXT("GL_POINT_SMOOTH_HINT"), GL_POINT_SMOOTH_HINT},
		{OS_TEXT("GL_LINE_SMOOTH_HINT"), GL_LINE_SMOOTH_HINT},
		{OS_TEXT("GL_FOG_HINT"), GL_FOG_HINT},
		{OS_TEXT("GL_GENERATE_MIPMAP_HINT"), GL_GENERATE_MIPMAP_HINT},

		/* LightModelParameter */
		{OS_TEXT("GL_LIGHT_MODEL_AMBIENT"), GL_LIGHT_MODEL_AMBIENT},
		{OS_TEXT("GL_LIGHT_MODEL_TWO_SIDE"), GL_LIGHT_MODEL_TWO_SIDE},

		/* LightParameter */
		{OS_TEXT("GL_AMBIENT"), GL_AMBIENT},
		{OS_TEXT("GL_DIFFUSE"), GL_DIFFUSE},
		{OS_TEXT("GL_SPECULAR"), GL_SPECULAR},
		{OS_TEXT("GL_POSITION"), GL_POSITION},
		{OS_TEXT("GL_SPOT_DIRECTION"), GL_SPOT_DIRECTION},
		{OS_TEXT("GL_SPOT_EXPONENT"), GL_SPOT_EXPONENT},
		{OS_TEXT("GL_SPOT_CUTOFF"), GL_SPOT_CUTOFF},
		{OS_TEXT("GL_CONSTANT_ATTENUATION"), GL_CONSTANT_ATTENUATION},
		{OS_TEXT("GL_LINEAR_ATTENUATION"), GL_LINEAR_ATTENUATION},
		{OS_TEXT("GL_QUADRATIC_ATTENUATION"), GL_QUADRATIC_ATTENUATION},

		/* DataType */
		{OS_TEXT("GL_BYTE"), GL_BYTE},
		{OS_TEXT("GL_UNSIGNED_BYTE"), GL_UNSIGNED_BYTE},
		{OS_TEXT("GL_SHORT"), GL_SHORT},
		{OS_TEXT("GL_UNSIGNED_SHORT"), GL_UNSIGNED_SHORT},
		{OS_TEXT("GL_FLOAT"), GL_FLOAT},
		{OS_TEXT("GL_FIXED"), GL_FIXED},

		/* LogicOp */
		{OS_TEXT("GL_CLEAR"), GL_CLEAR},
		{OS_TEXT("GL_AND"), GL_AND},
		{OS_TEXT("GL_AND_REVERSE"), GL_AND_REVERSE},
		{OS_TEXT("GL_COPY"), GL_COPY},
		{OS_TEXT("GL_AND_INVERTED"), GL_AND_INVERTED},
		{OS_TEXT("GL_NOOP"), GL_NOOP},
		{OS_TEXT("GL_XOR"), GL_XOR},
		{OS_TEXT("GL_OR"), GL_OR},
		{OS_TEXT("GL_NOR"), GL_NOR},
		{OS_TEXT("GL_EQUIV"), GL_EQUIV},
		{OS_TEXT("GL_INVERT"), GL_INVERT},
		{OS_TEXT("GL_OR_REVERSE"), GL_OR_REVERSE},
		{OS_TEXT("GL_COPY_INVERTED"), GL_COPY_INVERTED},
		{OS_TEXT("GL_OR_INVERTED"), GL_OR_INVERTED},
		{OS_TEXT("GL_NAND"), GL_NAND},
		{OS_TEXT("GL_SET"), GL_SET},

		/* MaterialFace */
		/*      GL_FRONT_AND_BACK */

		/* MaterialParameter */
		{OS_TEXT("GL_EMISSION"), GL_EMISSION},
		{OS_TEXT("GL_SHININESS"), GL_SHININESS},
		{OS_TEXT("GL_AMBIENT_AND_DIFFUSE"), GL_AMBIENT_AND_DIFFUSE},
		/*      GL_AMBIENT */
		/*      GL_DIFFUSE */
		/*      GL_SPECULAR */

		/* MatrixMode */
		{OS_TEXT("GL_MODELVIEW"), GL_MODELVIEW},
		{OS_TEXT("GL_PROJECTION"), GL_PROJECTION},
		{OS_TEXT("GL_TEXTURE"), GL_TEXTURE},

		/* NormalPointerType */
		/*      GL_BYTE */
		/*      GL_SHORT */
		/*      GL_FLOAT */
		/*      GL_FIXED */

		/* PixelFormat */
		{OS_TEXT("GL_ALPHA"), GL_ALPHA},
		{OS_TEXT("GL_RGB"), GL_RGB},
		{OS_TEXT("GL_RGBA"), GL_RGBA},
		{OS_TEXT("GL_LUMINANCE"), GL_LUMINANCE},
		{OS_TEXT("GL_LUMINANCE_ALPHA"), GL_LUMINANCE_ALPHA},

		/* PixelStoreParameter */
		{OS_TEXT("GL_UNPACK_ALIGNMENT"), GL_UNPACK_ALIGNMENT},
		{OS_TEXT("GL_PACK_ALIGNMENT"), GL_PACK_ALIGNMENT},

		/* PixelType */
		/*      GL_UNSIGNED_BYTE */
		{OS_TEXT("GL_UNSIGNED_SHORT_4_4_4_4"), GL_UNSIGNED_SHORT_4_4_4_4},
		{OS_TEXT("GL_UNSIGNED_SHORT_5_5_5_1"), GL_UNSIGNED_SHORT_5_5_5_1},
		{OS_TEXT("GL_UNSIGNED_SHORT_5_6_5"), GL_UNSIGNED_SHORT_5_6_5},

		/* ShadingModel */
		{OS_TEXT("GL_FLAT"), GL_FLAT},
		{OS_TEXT("GL_SMOOTH"), GL_SMOOTH},

		/* StencilFunction */
		/*      GL_NEVER */
		/*      GL_LESS */
		/*      GL_EQUAL */
		/*      GL_LEQUAL */
		/*      GL_GREATER */
		/*      GL_NOTEQUAL */
		/*      GL_GEQUAL */
		/*      GL_ALWAYS */

		/* StencilOp */
		/*      GL_ZERO */
		{OS_TEXT("GL_KEEP"), GL_KEEP},
		{OS_TEXT("GL_REPLACE"), GL_REPLACE},
		{OS_TEXT("GL_INCR"), GL_INCR},
		{OS_TEXT("GL_DECR"), GL_DECR},
		/*      GL_INVERT */

		/* StringName */
		{OS_TEXT("GL_VENDOR"), GL_VENDOR},
		{OS_TEXT("GL_RENDERER"), GL_RENDERER},
		{OS_TEXT("GL_VERSION"), GL_VERSION},
		{OS_TEXT("GL_EXTENSIONS"), GL_EXTENSIONS},

		/* TexCoordPointerType */
		/*      GL_SHORT */
		/*      GL_FLOAT */
		/*      GL_FIXED */
		/*      GL_BYTE */

		/* TextureEnvMode */
		{OS_TEXT("GL_MODULATE"), GL_MODULATE},
		{OS_TEXT("GL_DECAL"), GL_DECAL},
		/*      GL_BLEND */
		{OS_TEXT("GL_ADD"), GL_ADD},
		/*      GL_REPLACE */

		/* TextureEnvParameter */
		{OS_TEXT("GL_TEXTURE_ENV_MODE"), GL_TEXTURE_ENV_MODE},
		{OS_TEXT("GL_TEXTURE_ENV_COLOR"), GL_TEXTURE_ENV_COLOR},

		/* TextureEnvTarget */
		{OS_TEXT("GL_TEXTURE_ENV"), GL_TEXTURE_ENV},

		/* TextureMagFilter */
		{OS_TEXT("GL_NEAREST"), GL_NEAREST},
		{OS_TEXT("GL_LINEAR"), GL_LINEAR},

		/* TextureMinFilter */
		/*      GL_NEAREST */
		/*      GL_LINEAR */
		{OS_TEXT("GL_NEAREST_MIPMAP_NEAREST"), GL_NEAREST_MIPMAP_NEAREST},
		{OS_TEXT("GL_LINEAR_MIPMAP_NEAREST"), GL_LINEAR_MIPMAP_NEAREST},
		{OS_TEXT("GL_NEAREST_MIPMAP_LINEAR"), GL_NEAREST_MIPMAP_LINEAR},
		{OS_TEXT("GL_LINEAR_MIPMAP_LINEAR"), GL_LINEAR_MIPMAP_LINEAR},

		/* TextureParameterName */
		{OS_TEXT("GL_TEXTURE_MAG_FILTER"), GL_TEXTURE_MAG_FILTER},
		{OS_TEXT("GL_TEXTURE_MIN_FILTER"), GL_TEXTURE_MIN_FILTER},
		{OS_TEXT("GL_TEXTURE_WRAP_S"), GL_TEXTURE_WRAP_S},
		{OS_TEXT("GL_TEXTURE_WRAP_T"), GL_TEXTURE_WRAP_T},
		{OS_TEXT("GL_GENERATE_MIPMAP"), GL_GENERATE_MIPMAP},

		/* TextureTarget */
		/*      GL_TEXTURE_2D */

		/* TextureUnit */
		{OS_TEXT("GL_TEXTURE0"), GL_TEXTURE0},
		{OS_TEXT("GL_TEXTURE1"), GL_TEXTURE1},
		{OS_TEXT("GL_TEXTURE2"), GL_TEXTURE2},
		{OS_TEXT("GL_TEXTURE3"), GL_TEXTURE3},
		{OS_TEXT("GL_TEXTURE4"), GL_TEXTURE4},
		{OS_TEXT("GL_TEXTURE5"), GL_TEXTURE5},
		{OS_TEXT("GL_TEXTURE6"), GL_TEXTURE6},
		{OS_TEXT("GL_TEXTURE7"), GL_TEXTURE7},
		{OS_TEXT("GL_TEXTURE8"), GL_TEXTURE8},
		{OS_TEXT("GL_TEXTURE9"), GL_TEXTURE9},
		{OS_TEXT("GL_TEXTURE10"), GL_TEXTURE10},
		{OS_TEXT("GL_TEXTURE11"), GL_TEXTURE11},
		{OS_TEXT("GL_TEXTURE12"), GL_TEXTURE12},
		{OS_TEXT("GL_TEXTURE13"), GL_TEXTURE13},
		{OS_TEXT("GL_TEXTURE14"), GL_TEXTURE14},
		{OS_TEXT("GL_TEXTURE15"), GL_TEXTURE15},
		{OS_TEXT("GL_TEXTURE16"), GL_TEXTURE16},
		{OS_TEXT("GL_TEXTURE17"), GL_TEXTURE17},
		{OS_TEXT("GL_TEXTURE18"), GL_TEXTURE18},
		{OS_TEXT("GL_TEXTURE19"), GL_TEXTURE19},
		{OS_TEXT("GL_TEXTURE20"), GL_TEXTURE20},
		{OS_TEXT("GL_TEXTURE21"), GL_TEXTURE21},
		{OS_TEXT("GL_TEXTURE22"), GL_TEXTURE22},
		{OS_TEXT("GL_TEXTURE23"), GL_TEXTURE23},
		{OS_TEXT("GL_TEXTURE24"), GL_TEXTURE24},
		{OS_TEXT("GL_TEXTURE25"), GL_TEXTURE25},
		{OS_TEXT("GL_TEXTURE26"), GL_TEXTURE26},
		{OS_TEXT("GL_TEXTURE27"), GL_TEXTURE27},
		{OS_TEXT("GL_TEXTURE28"), GL_TEXTURE28},
		{OS_TEXT("GL_TEXTURE29"), GL_TEXTURE29},
		{OS_TEXT("GL_TEXTURE30"), GL_TEXTURE30},
		{OS_TEXT("GL_TEXTURE31"), GL_TEXTURE31},
		{OS_TEXT("GL_ACTIVE_TEXTURE"), GL_ACTIVE_TEXTURE},
		{OS_TEXT("GL_CLIENT_ACTIVE_TEXTURE"), GL_CLIENT_ACTIVE_TEXTURE},

		/* TextureWrapMode */
		{OS_TEXT("GL_REPEAT"), GL_REPEAT},
		{OS_TEXT("GL_CLAMP_TO_EDGE"), GL_CLAMP_TO_EDGE},

		/* VertexPointerType */
		/*      GL_SHORT */
		/*      GL_FLOAT */
		/*      GL_FIXED */
		/*      GL_BYTE */

		/* LightName */
		{OS_TEXT("GL_LIGHT0"), GL_LIGHT0},
		{OS_TEXT("GL_LIGHT1"), GL_LIGHT1},
		{OS_TEXT("GL_LIGHT2"), GL_LIGHT2},
		{OS_TEXT("GL_LIGHT3"), GL_LIGHT3},
		{OS_TEXT("GL_LIGHT4"), GL_LIGHT4},
		{OS_TEXT("GL_LIGHT5"), GL_LIGHT5},
		{OS_TEXT("GL_LIGHT6"), GL_LIGHT6},
		{OS_TEXT("GL_LIGHT7"), GL_LIGHT7},

		/* Buffer Objects */
		{OS_TEXT("GL_ARRAY_BUFFER"), GL_ARRAY_BUFFER},
		{OS_TEXT("GL_ELEMENT_ARRAY_BUFFER"), GL_ELEMENT_ARRAY_BUFFER},

		{OS_TEXT("GL_ARRAY_BUFFER_BINDING"), GL_ARRAY_BUFFER_BINDING},
		{OS_TEXT("GL_ELEMENT_ARRAY_BUFFER_BINDING"), GL_ELEMENT_ARRAY_BUFFER_BINDING},
		{OS_TEXT("GL_VERTEX_ARRAY_BUFFER_BINDING"), GL_VERTEX_ARRAY_BUFFER_BINDING},
		{OS_TEXT("GL_NORMAL_ARRAY_BUFFER_BINDING"), GL_NORMAL_ARRAY_BUFFER_BINDING},
		{OS_TEXT("GL_COLOR_ARRAY_BUFFER_BINDING"), GL_COLOR_ARRAY_BUFFER_BINDING},
		{OS_TEXT("GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING"), GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING},

		{OS_TEXT("GL_STATIC_DRAW"), GL_STATIC_DRAW},
		{OS_TEXT("GL_DYNAMIC_DRAW"), GL_DYNAMIC_DRAW},

		{OS_TEXT("GL_BUFFER_SIZE"), GL_BUFFER_SIZE},
		{OS_TEXT("GL_BUFFER_USAGE"), GL_BUFFER_USAGE},

		/* Texture combine + dot3 */
		{OS_TEXT("GL_SUBTRACT"), GL_SUBTRACT},
		{OS_TEXT("GL_COMBINE"), GL_COMBINE},
		{OS_TEXT("GL_COMBINE_RGB"), GL_COMBINE_RGB},
		{OS_TEXT("GL_COMBINE_ALPHA"), GL_COMBINE_ALPHA},
		{OS_TEXT("GL_RGB_SCALE"), GL_RGB_SCALE},
		{OS_TEXT("GL_ADD_SIGNED"), GL_ADD_SIGNED},
		{OS_TEXT("GL_INTERPOLATE"), GL_INTERPOLATE},
		{OS_TEXT("GL_CONSTANT"), GL_CONSTANT},
		{OS_TEXT("GL_PRIMARY_COLOR"), GL_PRIMARY_COLOR},
		{OS_TEXT("GL_PREVIOUS"), GL_PREVIOUS},
		{OS_TEXT("GL_OPERAND0_RGB"), GL_OPERAND0_RGB},
		{OS_TEXT("GL_OPERAND1_RGB"), GL_OPERAND1_RGB},
		{OS_TEXT("GL_OPERAND2_RGB"), GL_OPERAND2_RGB},
		{OS_TEXT("GL_OPERAND0_ALPHA"), GL_OPERAND0_ALPHA},
		{OS_TEXT("GL_OPERAND1_ALPHA"), GL_OPERAND1_ALPHA},
		{OS_TEXT("GL_OPERAND2_ALPHA"), GL_OPERAND2_ALPHA},

		{OS_TEXT("GL_ALPHA_SCALE"), GL_ALPHA_SCALE},

		{OS_TEXT("GL_SRC0_RGB"), GL_SRC0_RGB},
		{OS_TEXT("GL_SRC1_RGB"), GL_SRC1_RGB},
		{OS_TEXT("GL_SRC2_RGB"), GL_SRC2_RGB},
		{OS_TEXT("GL_SRC0_ALPHA"), GL_SRC0_ALPHA},
		{OS_TEXT("GL_SRC1_ALPHA"), GL_SRC1_ALPHA},
		{OS_TEXT("GL_SRC2_ALPHA"), GL_SRC2_ALPHA},

		{OS_TEXT("GL_DOT3_RGB"), GL_DOT3_RGB},
		{OS_TEXT("GL_DOT3_RGBA"), GL_DOT3_RGBA},

		/*------------------------------------------------------------------------*
		* required OES extension tokens
		*------------------------------------------------------------------------*/

		/* OES_read_format */
#ifndef GL_OES_read_format
		{OS_TEXT("GL_IMPLEMENTATION_COLOR_READ_TYPE_OES"), GL_IMPLEMENTATION_COLOR_READ_TYPE_OES},
		{OS_TEXT("GL_IMPLEMENTATION_COLOR_READ_FORMAT_OES"), GL_IMPLEMENTATION_COLOR_READ_FORMAT_OES},
#endif

		/* GL_OES_compressed_paletted_texture */
#ifndef GL_OES_compressed_paletted_texture
		{OS_TEXT("GL_PALETTE4_RGB8_OES"), GL_PALETTE4_RGB8_OES},
		{OS_TEXT("GL_PALETTE4_RGBA8_OES"), GL_PALETTE4_RGBA8_OES},
		{OS_TEXT("GL_PALETTE4_R5_G6_B5_OES"), GL_PALETTE4_R5_G6_B5_OES},
		{OS_TEXT("GL_PALETTE4_RGBA4_OES"), GL_PALETTE4_RGBA4_OES},
		{OS_TEXT("GL_PALETTE4_RGB5_A1_OES"), GL_PALETTE4_RGB5_A1_OES},
		{OS_TEXT("GL_PALETTE8_RGB8_OES"), GL_PALETTE8_RGB8_OES},
		{OS_TEXT("GL_PALETTE8_RGBA8_OES"), GL_PALETTE8_RGBA8_OES},
		{OS_TEXT("GL_PALETTE8_R5_G6_B5_OES"), GL_PALETTE8_R5_G6_B5_OES},
		{OS_TEXT("GL_PALETTE8_RGBA4_OES"), GL_PALETTE8_RGBA4_OES},
		{OS_TEXT("GL_PALETTE8_RGB5_A1_OES"), GL_PALETTE8_RGB5_A1_OES},
#endif

		/* OES_point_size_array */
#ifndef GL_OES_point_size_array
		{OS_TEXT("GL_POINT_SIZE_ARRAY_OES"), GL_POINT_SIZE_ARRAY_OES},
		{OS_TEXT("GL_POINT_SIZE_ARRAY_TYPE_OES"), GL_POINT_SIZE_ARRAY_TYPE_OES},
		{OS_TEXT("GL_POINT_SIZE_ARRAY_STRIDE_OES"), GL_POINT_SIZE_ARRAY_STRIDE_OES},
		{OS_TEXT("GL_POINT_SIZE_ARRAY_POINTER_OES"), GL_POINT_SIZE_ARRAY_POINTER_OES},
		{OS_TEXT("GL_POINT_SIZE_ARRAY_BUFFER_BINDING_OES"), GL_POINT_SIZE_ARRAY_BUFFER_BINDING_OES},
#endif

		/* GL_OES_point_sprite */
#ifndef GL_OES_point_sprite
		{OS_TEXT("GL_POINT_SPRITE_OES"), GL_POINT_SPRITE_OES},
		{OS_TEXT("GL_COORD_REPLACE_OES"), GL_COORD_REPLACE_OES},
#endif

		{}
	};

	os->pushGlobals();
	os->setFuncs(list);
	os->setNumbers(numbers);
	os->pop();
}

void initOpenGL2(OS * os)
{
	struct OpenGL
	{
		static int glActiveTexture(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glActiveTexture (GLenum texture); */
			::glActiveTexture((GLenum)os->toNumber(-params+0));
			return 0;
		}

		static int glAttachShader(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glAttachShader (GLuint program, GLuint shader); */
			::glAttachShader((GLuint)os->toNumber(-params+0), (GLuint)os->toNumber(-params+1));
			return 0;
		}

		/* skip: GL_APICALL void GL_APIENTRY glBindAttribLocation (GLuint program, GLuint index, const GLchar* name); */

		static int glBindBuffer(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glBindBuffer (GLenum target, GLuint buffer); */
			::glBindBuffer((GLenum)os->toNumber(-params+0), (GLuint)os->toNumber(-params+1));
			return 0;
		}

		static int glBindFramebuffer(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glBindFramebuffer (GLenum target, GLuint framebuffer); */
			::glBindFramebuffer((GLenum)os->toNumber(-params+0), (GLuint)os->toNumber(-params+1));
			return 0;
		}

		static int glBindRenderbuffer(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glBindRenderbuffer (GLenum target, GLuint renderbuffer); */
			::glBindRenderbuffer((GLenum)os->toNumber(-params+0), (GLuint)os->toNumber(-params+1));
			return 0;
		}

		static int glBindTexture(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glBindTexture (GLenum target, GLuint texture); */
			::glBindTexture((GLenum)os->toNumber(-params+0), (GLuint)os->toNumber(-params+1));
			return 0;
		}

		static int glBlendColor(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glBlendColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha); */
			::glBlendColor((GLclampf)os->toNumber(-params+0), (GLclampf)os->toNumber(-params+1), (GLclampf)os->toNumber(-params+2), (GLclampf)os->toNumber(-params+3));
			return 0;
		}

		static int glBlendEquation(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glBlendEquation ( GLenum mode ); */
			::glBlendEquation((GLenum)os->toNumber(-params+0));
			return 0;
		}

		static int glBlendEquationSeparate(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glBlendEquationSeparate (GLenum modeRGB, GLenum modeAlpha); */
			::glBlendEquationSeparate((GLenum)os->toNumber(-params+0), (GLenum)os->toNumber(-params+1));
			return 0;
		}

		static int glBlendFunc(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glBlendFunc (GLenum sfactor, GLenum dfactor); */
			::glBlendFunc((GLenum)os->toNumber(-params+0), (GLenum)os->toNumber(-params+1));
			return 0;
		}

		static int glBlendFuncSeparate(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glBlendFuncSeparate (GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha); */
			::glBlendFuncSeparate((GLenum)os->toNumber(-params+0), (GLenum)os->toNumber(-params+1), (GLenum)os->toNumber(-params+2), (GLenum)os->toNumber(-params+3));
			return 0;
		}

		/* skip: GL_APICALL void GL_APIENTRY glBufferData (GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage); */

		/* skip: GL_APICALL void GL_APIENTRY glBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data); */

		static int glCheckFramebufferStatus(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL GLenum GL_APIENTRY glCheckFramebufferStatus (GLenum target); */
			os->pushNumber((OS_NUMBER)::glCheckFramebufferStatus((GLenum)os->toNumber(-params+0)));
			return 1;
		}

		static int glClear(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glClear (GLbitfield mask); */
			::glClear((GLbitfield)os->toNumber(-params+0));
			return 0;
		}

		static int glClearColor(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glClearColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha); */
			::glClearColor((GLclampf)os->toNumber(-params+0), (GLclampf)os->toNumber(-params+1), (GLclampf)os->toNumber(-params+2), (GLclampf)os->toNumber(-params+3));
			return 0;
		}

		static int glClearDepthf(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glClearDepthf (GLclampf depth); */
			::glClearDepthf((GLclampf)os->toNumber(-params+0));
			return 0;
		}

		static int glClearStencil(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glClearStencil (GLint s); */
			::glClearStencil((GLint)os->toNumber(-params+0));
			return 0;
		}

		static int glColorMask(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha); */
			::glColorMask((GLboolean)os->toNumber(-params+0), (GLboolean)os->toNumber(-params+1), (GLboolean)os->toNumber(-params+2), (GLboolean)os->toNumber(-params+3));
			return 0;
		}

		static int glCompileShader(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glCompileShader (GLuint shader); */
			::glCompileShader((GLuint)os->toNumber(-params+0));
			return 0;
		}

		/* skip: GL_APICALL void GL_APIENTRY glCompressedTexImage2D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid* data); */

		/* skip: GL_APICALL void GL_APIENTRY glCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid* data); */

		static int glCopyTexImage2D(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glCopyTexImage2D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border); */
			::glCopyTexImage2D((GLenum)os->toNumber(-params+0), (GLint)os->toNumber(-params+1), (GLenum)os->toNumber(-params+2), (GLint)os->toNumber(-params+3), (GLint)os->toNumber(-params+4), (GLsizei)os->toNumber(-params+5), (GLsizei)os->toNumber(-params+6), (GLint)os->toNumber(-params+7));
			return 0;
		}

		static int glCopyTexSubImage2D(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glCopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height); */
			::glCopyTexSubImage2D((GLenum)os->toNumber(-params+0), (GLint)os->toNumber(-params+1), (GLint)os->toNumber(-params+2), (GLint)os->toNumber(-params+3), (GLint)os->toNumber(-params+4), (GLint)os->toNumber(-params+5), (GLsizei)os->toNumber(-params+6), (GLsizei)os->toNumber(-params+7));
			return 0;
		}

		static int glCreateProgram(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL GLuint GL_APIENTRY glCreateProgram (void); */
			os->pushNumber((OS_NUMBER)::glCreateProgram());
			return 1;
		}

		static int glCreateShader(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL GLuint GL_APIENTRY glCreateShader (GLenum type); */
			os->pushNumber((OS_NUMBER)::glCreateShader((GLenum)os->toNumber(-params+0)));
			return 1;
		}

		static int glCullFace(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glCullFace (GLenum mode); */
			::glCullFace((GLenum)os->toNumber(-params+0));
			return 0;
		}

		/* skip: GL_APICALL void GL_APIENTRY glDeleteBuffers (GLsizei n, const GLuint* buffers); */

		/* skip: GL_APICALL void GL_APIENTRY glDeleteFramebuffers (GLsizei n, const GLuint* framebuffers); */

		static int glDeleteProgram(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glDeleteProgram (GLuint program); */
			::glDeleteProgram((GLuint)os->toNumber(-params+0));
			return 0;
		}

		/* skip: GL_APICALL void GL_APIENTRY glDeleteRenderbuffers (GLsizei n, const GLuint* renderbuffers); */

		static int glDeleteShader(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glDeleteShader (GLuint shader); */
			::glDeleteShader((GLuint)os->toNumber(-params+0));
			return 0;
		}

		/* skip: GL_APICALL void GL_APIENTRY glDeleteTextures (GLsizei n, const GLuint* textures); */

		static int glDepthFunc(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glDepthFunc (GLenum func); */
			::glDepthFunc((GLenum)os->toNumber(-params+0));
			return 0;
		}

		static int glDepthMask(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glDepthMask (GLboolean flag); */
			::glDepthMask((GLboolean)os->toNumber(-params+0));
			return 0;
		}

		static int glDepthRangef(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glDepthRangef (GLclampf zNear, GLclampf zFar); */
			::glDepthRangef((GLclampf)os->toNumber(-params+0), (GLclampf)os->toNumber(-params+1));
			return 0;
		}

		static int glDetachShader(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glDetachShader (GLuint program, GLuint shader); */
			::glDetachShader((GLuint)os->toNumber(-params+0), (GLuint)os->toNumber(-params+1));
			return 0;
		}

		static int glDisable(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glDisable (GLenum cap); */
			::glDisable((GLenum)os->toNumber(-params+0));
			return 0;
		}

		static int glDisableVertexAttribArray(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glDisableVertexAttribArray (GLuint index); */
			::glDisableVertexAttribArray((GLuint)os->toNumber(-params+0));
			return 0;
		}

		static int glDrawArrays(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glDrawArrays (GLenum mode, GLint first, GLsizei count); */
			::glDrawArrays((GLenum)os->toNumber(-params+0), (GLint)os->toNumber(-params+1), (GLsizei)os->toNumber(-params+2));
			return 0;
		}

		/* skip: GL_APICALL void GL_APIENTRY glDrawElements (GLenum mode, GLsizei count, GLenum type, const GLvoid* indices); */

		static int glEnable(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glEnable (GLenum cap); */
			::glEnable((GLenum)os->toNumber(-params+0));
			return 0;
		}

		static int glEnableVertexAttribArray(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glEnableVertexAttribArray (GLuint index); */
			::glEnableVertexAttribArray((GLuint)os->toNumber(-params+0));
			return 0;
		}

		static int glFinish(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glFinish (void); */
			::glFinish();
			return 0;
		}

		static int glFlush(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glFlush (void); */
			::glFlush();
			return 0;
		}

		static int glFramebufferRenderbuffer(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glFramebufferRenderbuffer (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer); */
			::glFramebufferRenderbuffer((GLenum)os->toNumber(-params+0), (GLenum)os->toNumber(-params+1), (GLenum)os->toNumber(-params+2), (GLuint)os->toNumber(-params+3));
			return 0;
		}

		static int glFramebufferTexture2D(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glFramebufferTexture2D (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level); */
			::glFramebufferTexture2D((GLenum)os->toNumber(-params+0), (GLenum)os->toNumber(-params+1), (GLenum)os->toNumber(-params+2), (GLuint)os->toNumber(-params+3), (GLint)os->toNumber(-params+4));
			return 0;
		}

		static int glFrontFace(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glFrontFace (GLenum mode); */
			::glFrontFace((GLenum)os->toNumber(-params+0));
			return 0;
		}

		/* skip: GL_APICALL void GL_APIENTRY glGenBuffers (GLsizei n, GLuint* buffers); */

		static int glGenerateMipmap(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glGenerateMipmap (GLenum target); */
			::glGenerateMipmap((GLenum)os->toNumber(-params+0));
			return 0;
		}

		/* skip: GL_APICALL void GL_APIENTRY glGenFramebuffers (GLsizei n, GLuint* framebuffers); */

		/* skip: GL_APICALL void GL_APIENTRY glGenRenderbuffers (GLsizei n, GLuint* renderbuffers); */

		/* skip: GL_APICALL void GL_APIENTRY glGenTextures (GLsizei n, GLuint* textures); */

		/* skip: GL_APICALL void GL_APIENTRY glGetActiveAttrib (GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name); */

		/* skip: GL_APICALL void GL_APIENTRY glGetActiveUniform (GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name); */

		/* skip: GL_APICALL void GL_APIENTRY glGetAttachedShaders (GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders); */

		/* skip: GL_APICALL int GL_APIENTRY glGetAttribLocation (GLuint program, const GLchar* name); */

		/* skip: GL_APICALL void GL_APIENTRY glGetBooleanv (GLenum pname, GLboolean* params); */

		/* skip: GL_APICALL void GL_APIENTRY glGetBufferParameteriv (GLenum target, GLenum pname, GLint* params); */

		static int glGetError(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL GLenum GL_APIENTRY glGetError (void); */
			os->pushNumber((OS_NUMBER)::glGetError());
			return 1;
		}

		/* skip: GL_APICALL void GL_APIENTRY glGetFloatv (GLenum pname, GLfloat* params); */

		/* skip: GL_APICALL void GL_APIENTRY glGetFramebufferAttachmentParameteriv (GLenum target, GLenum attachment, GLenum pname, GLint* params); */

		/* skip: GL_APICALL void GL_APIENTRY glGetIntegerv (GLenum pname, GLint* params); */

		/* skip: GL_APICALL void GL_APIENTRY glGetProgramiv (GLuint program, GLenum pname, GLint* params); */

		/* skip: GL_APICALL void GL_APIENTRY glGetProgramInfoLog (GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog); */

		/* skip: GL_APICALL void GL_APIENTRY glGetRenderbufferParameteriv (GLenum target, GLenum pname, GLint* params); */

		/* skip: GL_APICALL void GL_APIENTRY glGetShaderiv (GLuint shader, GLenum pname, GLint* params); */

		/* skip: GL_APICALL void GL_APIENTRY glGetShaderInfoLog (GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* infolog); */

		/* skip: GL_APICALL void GL_APIENTRY glGetShaderPrecisionFormat (GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision); */

		/* skip: GL_APICALL void GL_APIENTRY glGetShaderSource (GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* source); */

		/* GL_APICALL const GLubyte* GL_APIENTRY glGetString (GLenum name); */    /* skip: GL_APICALL void GL_APIENTRY glGetTexParameterfv (GLenum target, GLenum pname, GLfloat* params); */

		/* skip: GL_APICALL void GL_APIENTRY glGetTexParameteriv (GLenum target, GLenum pname, GLint* params); */

		/* skip: GL_APICALL void GL_APIENTRY glGetUniformfv (GLuint program, GLint location, GLfloat* params); */

		/* skip: GL_APICALL void GL_APIENTRY glGetUniformiv (GLuint program, GLint location, GLint* params); */

		/* skip: GL_APICALL int GL_APIENTRY glGetUniformLocation (GLuint program, const GLchar* name); */

		/* skip: GL_APICALL void GL_APIENTRY glGetVertexAttribfv (GLuint index, GLenum pname, GLfloat* params); */

		/* skip: GL_APICALL void GL_APIENTRY glGetVertexAttribiv (GLuint index, GLenum pname, GLint* params); */

		/* skip: GL_APICALL void GL_APIENTRY glGetVertexAttribPointerv (GLuint index, GLenum pname, GLvoid** pointer); */

		static int glHint(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glHint (GLenum target, GLenum mode); */
			::glHint((GLenum)os->toNumber(-params+0), (GLenum)os->toNumber(-params+1));
			return 0;
		}

		static int glIsBuffer(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL GLboolean GL_APIENTRY glIsBuffer (GLuint buffer); */
			os->pushBool(::glIsBuffer((GLuint)os->toNumber(-params+0)) ? true : false);
			return 1;
		}

		static int glIsEnabled(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL GLboolean GL_APIENTRY glIsEnabled (GLenum cap); */
			os->pushBool(::glIsEnabled((GLenum)os->toNumber(-params+0)) ? true : false);
			return 1;
		}

		static int glIsFramebuffer(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL GLboolean GL_APIENTRY glIsFramebuffer (GLuint framebuffer); */
			os->pushBool(::glIsFramebuffer((GLuint)os->toNumber(-params+0)) ? true : false);
			return 1;
		}

		static int glIsProgram(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL GLboolean GL_APIENTRY glIsProgram (GLuint program); */
			os->pushBool(::glIsProgram((GLuint)os->toNumber(-params+0)) ? true : false);
			return 1;
		}

		static int glIsRenderbuffer(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL GLboolean GL_APIENTRY glIsRenderbuffer (GLuint renderbuffer); */
			os->pushBool(::glIsRenderbuffer((GLuint)os->toNumber(-params+0)) ? true : false);
			return 1;
		}

		static int glIsShader(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL GLboolean GL_APIENTRY glIsShader (GLuint shader); */
			os->pushBool(::glIsShader((GLuint)os->toNumber(-params+0)) ? true : false);
			return 1;
		}

		static int glIsTexture(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL GLboolean GL_APIENTRY glIsTexture (GLuint texture); */
			os->pushBool(::glIsTexture((GLuint)os->toNumber(-params+0)) ? true : false);
			return 1;
		}

		static int glLineWidth(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glLineWidth (GLfloat width); */
			::glLineWidth((GLfloat)os->toNumber(-params+0));
			return 0;
		}

		static int glLinkProgram(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glLinkProgram (GLuint program); */
			::glLinkProgram((GLuint)os->toNumber(-params+0));
			return 0;
		}

		static int glPixelStorei(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glPixelStorei (GLenum pname, GLint param); */
			::glPixelStorei((GLenum)os->toNumber(-params+0), (GLint)os->toNumber(-params+1));
			return 0;
		}

		static int glPolygonOffset(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glPolygonOffset (GLfloat factor, GLfloat units); */
			::glPolygonOffset((GLfloat)os->toNumber(-params+0), (GLfloat)os->toNumber(-params+1));
			return 0;
		}

		/* skip: GL_APICALL void GL_APIENTRY glReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* pixels); */

		static int glReleaseShaderCompiler(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glReleaseShaderCompiler (void); */
			::glReleaseShaderCompiler();
			return 0;
		}

		static int glRenderbufferStorage(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glRenderbufferStorage (GLenum target, GLenum internalformat, GLsizei width, GLsizei height); */
			::glRenderbufferStorage((GLenum)os->toNumber(-params+0), (GLenum)os->toNumber(-params+1), (GLsizei)os->toNumber(-params+2), (GLsizei)os->toNumber(-params+3));
			return 0;
		}

		static int glSampleCoverage(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glSampleCoverage (GLclampf value, GLboolean invert); */
			::glSampleCoverage((GLclampf)os->toNumber(-params+0), (GLboolean)os->toNumber(-params+1));
			return 0;
		}

		static int glScissor(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glScissor (GLint x, GLint y, GLsizei width, GLsizei height); */
			::glScissor((GLint)os->toNumber(-params+0), (GLint)os->toNumber(-params+1), (GLsizei)os->toNumber(-params+2), (GLsizei)os->toNumber(-params+3));
			return 0;
		}

		/* skip: GL_APICALL void GL_APIENTRY glShaderBinary (GLsizei n, const GLuint* shaders, GLenum binaryformat, const GLvoid* binary, GLsizei length); */

		/* skip: GL_APICALL void GL_APIENTRY glShaderSource (GLuint shader, GLsizei count, const GLchar** string, const GLint* length); */

		static int glStencilFunc(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glStencilFunc (GLenum func, GLint ref, GLuint mask); */
			::glStencilFunc((GLenum)os->toNumber(-params+0), (GLint)os->toNumber(-params+1), (GLuint)os->toNumber(-params+2));
			return 0;
		}

		static int glStencilFuncSeparate(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glStencilFuncSeparate (GLenum face, GLenum func, GLint ref, GLuint mask); */
			::glStencilFuncSeparate((GLenum)os->toNumber(-params+0), (GLenum)os->toNumber(-params+1), (GLint)os->toNumber(-params+2), (GLuint)os->toNumber(-params+3));
			return 0;
		}

		static int glStencilMask(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glStencilMask (GLuint mask); */
			::glStencilMask((GLuint)os->toNumber(-params+0));
			return 0;
		}

		static int glStencilMaskSeparate(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glStencilMaskSeparate (GLenum face, GLuint mask); */
			::glStencilMaskSeparate((GLenum)os->toNumber(-params+0), (GLuint)os->toNumber(-params+1));
			return 0;
		}

		static int glStencilOp(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glStencilOp (GLenum fail, GLenum zfail, GLenum zpass); */
			::glStencilOp((GLenum)os->toNumber(-params+0), (GLenum)os->toNumber(-params+1), (GLenum)os->toNumber(-params+2));
			return 0;
		}

		static int glStencilOpSeparate(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glStencilOpSeparate (GLenum face, GLenum fail, GLenum zfail, GLenum zpass); */
			::glStencilOpSeparate((GLenum)os->toNumber(-params+0), (GLenum)os->toNumber(-params+1), (GLenum)os->toNumber(-params+2), (GLenum)os->toNumber(-params+3));
			return 0;
		}

		/* skip: GL_APICALL void GL_APIENTRY glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels); */

		static int glTexParameterf(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glTexParameterf (GLenum target, GLenum pname, GLfloat param); */
			::glTexParameterf((GLenum)os->toNumber(-params+0), (GLenum)os->toNumber(-params+1), (GLfloat)os->toNumber(-params+2));
			return 0;
		}

		/* skip: GL_APICALL void GL_APIENTRY glTexParameterfv (GLenum target, GLenum pname, const GLfloat* params); */

		static int glTexParameteri(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glTexParameteri (GLenum target, GLenum pname, GLint param); */
			::glTexParameteri((GLenum)os->toNumber(-params+0), (GLenum)os->toNumber(-params+1), (GLint)os->toNumber(-params+2));
			return 0;
		}

		/* skip: GL_APICALL void GL_APIENTRY glTexParameteriv (GLenum target, GLenum pname, const GLint* params); */

		/* skip: GL_APICALL void GL_APIENTRY glTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels); */

		static int glUniform1f(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glUniform1f (GLint location, GLfloat x); */
			::glUniform1f((GLint)os->toNumber(-params+0), (GLfloat)os->toNumber(-params+1));
			return 0;
		}

		/* skip: GL_APICALL void GL_APIENTRY glUniform1fv (GLint location, GLsizei count, const GLfloat* v); */

		static int glUniform1i(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glUniform1i (GLint location, GLint x); */
			::glUniform1i((GLint)os->toNumber(-params+0), (GLint)os->toNumber(-params+1));
			return 0;
		}

		/* skip: GL_APICALL void GL_APIENTRY glUniform1iv (GLint location, GLsizei count, const GLint* v); */

		static int glUniform2f(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glUniform2f (GLint location, GLfloat x, GLfloat y); */
			::glUniform2f((GLint)os->toNumber(-params+0), (GLfloat)os->toNumber(-params+1), (GLfloat)os->toNumber(-params+2));
			return 0;
		}

		/* skip: GL_APICALL void GL_APIENTRY glUniform2fv (GLint location, GLsizei count, const GLfloat* v); */

		static int glUniform2i(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glUniform2i (GLint location, GLint x, GLint y); */
			::glUniform2i((GLint)os->toNumber(-params+0), (GLint)os->toNumber(-params+1), (GLint)os->toNumber(-params+2));
			return 0;
		}

		/* skip: GL_APICALL void GL_APIENTRY glUniform2iv (GLint location, GLsizei count, const GLint* v); */

		static int glUniform3f(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glUniform3f (GLint location, GLfloat x, GLfloat y, GLfloat z); */
			::glUniform3f((GLint)os->toNumber(-params+0), (GLfloat)os->toNumber(-params+1), (GLfloat)os->toNumber(-params+2), (GLfloat)os->toNumber(-params+3));
			return 0;
		}

		/* skip: GL_APICALL void GL_APIENTRY glUniform3fv (GLint location, GLsizei count, const GLfloat* v); */

		static int glUniform3i(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glUniform3i (GLint location, GLint x, GLint y, GLint z); */
			::glUniform3i((GLint)os->toNumber(-params+0), (GLint)os->toNumber(-params+1), (GLint)os->toNumber(-params+2), (GLint)os->toNumber(-params+3));
			return 0;
		}

		/* skip: GL_APICALL void GL_APIENTRY glUniform3iv (GLint location, GLsizei count, const GLint* v); */

		static int glUniform4f(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glUniform4f (GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w); */
			::glUniform4f((GLint)os->toNumber(-params+0), (GLfloat)os->toNumber(-params+1), (GLfloat)os->toNumber(-params+2), (GLfloat)os->toNumber(-params+3), (GLfloat)os->toNumber(-params+4));
			return 0;
		}

		/* skip: GL_APICALL void GL_APIENTRY glUniform4fv (GLint location, GLsizei count, const GLfloat* v); */

		static int glUniform4i(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glUniform4i (GLint location, GLint x, GLint y, GLint z, GLint w); */
			::glUniform4i((GLint)os->toNumber(-params+0), (GLint)os->toNumber(-params+1), (GLint)os->toNumber(-params+2), (GLint)os->toNumber(-params+3), (GLint)os->toNumber(-params+4));
			return 0;
		}

		/* skip: GL_APICALL void GL_APIENTRY glUniform4iv (GLint location, GLsizei count, const GLint* v); */

		/* skip: GL_APICALL void GL_APIENTRY glUniformMatrix2fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value); */

		/* skip: GL_APICALL void GL_APIENTRY glUniformMatrix3fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value); */

		/* skip: GL_APICALL void GL_APIENTRY glUniformMatrix4fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value); */

		static int glUseProgram(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glUseProgram (GLuint program); */
			::glUseProgram((GLuint)os->toNumber(-params+0));
			return 0;
		}

		static int glValidateProgram(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glValidateProgram (GLuint program); */
			::glValidateProgram((GLuint)os->toNumber(-params+0));
			return 0;
		}

		static int glVertexAttrib1f(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glVertexAttrib1f (GLuint indx, GLfloat x); */
			::glVertexAttrib1f((GLuint)os->toNumber(-params+0), (GLfloat)os->toNumber(-params+1));
			return 0;
		}

		/* skip: GL_APICALL void GL_APIENTRY glVertexAttrib1fv (GLuint indx, const GLfloat* values); */

		static int glVertexAttrib2f(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glVertexAttrib2f (GLuint indx, GLfloat x, GLfloat y); */
			::glVertexAttrib2f((GLuint)os->toNumber(-params+0), (GLfloat)os->toNumber(-params+1), (GLfloat)os->toNumber(-params+2));
			return 0;
		}

		/* skip: GL_APICALL void GL_APIENTRY glVertexAttrib2fv (GLuint indx, const GLfloat* values); */

		static int glVertexAttrib3f(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glVertexAttrib3f (GLuint indx, GLfloat x, GLfloat y, GLfloat z); */
			::glVertexAttrib3f((GLuint)os->toNumber(-params+0), (GLfloat)os->toNumber(-params+1), (GLfloat)os->toNumber(-params+2), (GLfloat)os->toNumber(-params+3));
			return 0;
		}

		/* skip: GL_APICALL void GL_APIENTRY glVertexAttrib3fv (GLuint indx, const GLfloat* values); */

		static int glVertexAttrib4f(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glVertexAttrib4f (GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w); */
			::glVertexAttrib4f((GLuint)os->toNumber(-params+0), (GLfloat)os->toNumber(-params+1), (GLfloat)os->toNumber(-params+2), (GLfloat)os->toNumber(-params+3), (GLfloat)os->toNumber(-params+4));
			return 0;
		}

		/* skip: GL_APICALL void GL_APIENTRY glVertexAttrib4fv (GLuint indx, const GLfloat* values); */

		/* skip: GL_APICALL void GL_APIENTRY glVertexAttribPointer (GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr); */

		static int glViewport(OS * os, int params, int, int, void*)
		{
			/* GL_APICALL void GL_APIENTRY glViewport (GLint x, GLint y, GLsizei width, GLsizei height); */
			::glViewport((GLint)os->toNumber(-params+0), (GLint)os->toNumber(-params+1), (GLsizei)os->toNumber(-params+2), (GLsizei)os->toNumber(-params+3));
			return 0;
		}


	};

	OS::FuncDef list[] = {
		{OS_TEXT("glActiveTexture"), OpenGL::glActiveTexture},
		{OS_TEXT("glAttachShader"), OpenGL::glAttachShader},
		{OS_TEXT("glBindBuffer"), OpenGL::glBindBuffer},
		{OS_TEXT("glBindFramebuffer"), OpenGL::glBindFramebuffer},
		{OS_TEXT("glBindRenderbuffer"), OpenGL::glBindRenderbuffer},
		{OS_TEXT("glBindTexture"), OpenGL::glBindTexture},
		{OS_TEXT("glBlendColor"), OpenGL::glBlendColor},
		{OS_TEXT("glBlendEquation"), OpenGL::glBlendEquation},
		{OS_TEXT("glBlendEquationSeparate"), OpenGL::glBlendEquationSeparate},
		{OS_TEXT("glBlendFunc"), OpenGL::glBlendFunc},
		{OS_TEXT("glBlendFuncSeparate"), OpenGL::glBlendFuncSeparate},
		{OS_TEXT("glCheckFramebufferStatus"), OpenGL::glCheckFramebufferStatus},
		{OS_TEXT("glClear"), OpenGL::glClear},
		{OS_TEXT("glClearColor"), OpenGL::glClearColor},
		{OS_TEXT("glClearDepthf"), OpenGL::glClearDepthf},
		{OS_TEXT("glClearStencil"), OpenGL::glClearStencil},
		{OS_TEXT("glColorMask"), OpenGL::glColorMask},
		{OS_TEXT("glCompileShader"), OpenGL::glCompileShader},
		{OS_TEXT("glCopyTexImage2D"), OpenGL::glCopyTexImage2D},
		{OS_TEXT("glCopyTexSubImage2D"), OpenGL::glCopyTexSubImage2D},
		{OS_TEXT("glCreateProgram"), OpenGL::glCreateProgram},
		{OS_TEXT("glCreateShader"), OpenGL::glCreateShader},
		{OS_TEXT("glCullFace"), OpenGL::glCullFace},
		{OS_TEXT("glDeleteProgram"), OpenGL::glDeleteProgram},
		{OS_TEXT("glDeleteShader"), OpenGL::glDeleteShader},
		{OS_TEXT("glDepthFunc"), OpenGL::glDepthFunc},
		{OS_TEXT("glDepthMask"), OpenGL::glDepthMask},
		{OS_TEXT("glDepthRangef"), OpenGL::glDepthRangef},
		{OS_TEXT("glDetachShader"), OpenGL::glDetachShader},
		{OS_TEXT("glDisable"), OpenGL::glDisable},
		{OS_TEXT("glDisableVertexAttribArray"), OpenGL::glDisableVertexAttribArray},
		{OS_TEXT("glDrawArrays"), OpenGL::glDrawArrays},
		{OS_TEXT("glEnable"), OpenGL::glEnable},
		{OS_TEXT("glEnableVertexAttribArray"), OpenGL::glEnableVertexAttribArray},
		{OS_TEXT("glFinish"), OpenGL::glFinish},
		{OS_TEXT("glFlush"), OpenGL::glFlush},
		{OS_TEXT("glFramebufferRenderbuffer"), OpenGL::glFramebufferRenderbuffer},
		{OS_TEXT("glFramebufferTexture2D"), OpenGL::glFramebufferTexture2D},
		{OS_TEXT("glFrontFace"), OpenGL::glFrontFace},
		{OS_TEXT("glGenerateMipmap"), OpenGL::glGenerateMipmap},
		{OS_TEXT("glGetError"), OpenGL::glGetError},
		{OS_TEXT("glHint"), OpenGL::glHint},
		{OS_TEXT("glIsBuffer"), OpenGL::glIsBuffer},
		{OS_TEXT("glIsEnabled"), OpenGL::glIsEnabled},
		{OS_TEXT("glIsFramebuffer"), OpenGL::glIsFramebuffer},
		{OS_TEXT("glIsProgram"), OpenGL::glIsProgram},
		{OS_TEXT("glIsRenderbuffer"), OpenGL::glIsRenderbuffer},
		{OS_TEXT("glIsShader"), OpenGL::glIsShader},
		{OS_TEXT("glIsTexture"), OpenGL::glIsTexture},
		{OS_TEXT("glLineWidth"), OpenGL::glLineWidth},
		{OS_TEXT("glLinkProgram"), OpenGL::glLinkProgram},
		{OS_TEXT("glPixelStorei"), OpenGL::glPixelStorei},
		{OS_TEXT("glPolygonOffset"), OpenGL::glPolygonOffset},
		{OS_TEXT("glReleaseShaderCompiler"), OpenGL::glReleaseShaderCompiler},
		{OS_TEXT("glRenderbufferStorage"), OpenGL::glRenderbufferStorage},
		{OS_TEXT("glSampleCoverage"), OpenGL::glSampleCoverage},
		{OS_TEXT("glScissor"), OpenGL::glScissor},
		{OS_TEXT("glStencilFunc"), OpenGL::glStencilFunc},
		{OS_TEXT("glStencilFuncSeparate"), OpenGL::glStencilFuncSeparate},
		{OS_TEXT("glStencilMask"), OpenGL::glStencilMask},
		{OS_TEXT("glStencilMaskSeparate"), OpenGL::glStencilMaskSeparate},
		{OS_TEXT("glStencilOp"), OpenGL::glStencilOp},
		{OS_TEXT("glStencilOpSeparate"), OpenGL::glStencilOpSeparate},
		{OS_TEXT("glTexParameterf"), OpenGL::glTexParameterf},
		{OS_TEXT("glTexParameteri"), OpenGL::glTexParameteri},
		{OS_TEXT("glUniform1f"), OpenGL::glUniform1f},
		{OS_TEXT("glUniform1i"), OpenGL::glUniform1i},
		{OS_TEXT("glUniform2f"), OpenGL::glUniform2f},
		{OS_TEXT("glUniform2i"), OpenGL::glUniform2i},
		{OS_TEXT("glUniform3f"), OpenGL::glUniform3f},
		{OS_TEXT("glUniform3i"), OpenGL::glUniform3i},
		{OS_TEXT("glUniform4f"), OpenGL::glUniform4f},
		{OS_TEXT("glUniform4i"), OpenGL::glUniform4i},
		{OS_TEXT("glUseProgram"), OpenGL::glUseProgram},
		{OS_TEXT("glValidateProgram"), OpenGL::glValidateProgram},
		{OS_TEXT("glVertexAttrib1f"), OpenGL::glVertexAttrib1f},
		{OS_TEXT("glVertexAttrib2f"), OpenGL::glVertexAttrib2f},
		{OS_TEXT("glVertexAttrib3f"), OpenGL::glVertexAttrib3f},
		{OS_TEXT("glVertexAttrib4f"), OpenGL::glVertexAttrib4f},
		{OS_TEXT("glViewport"), OpenGL::glViewport},
		{}
	};

	OS::NumberDef numbers[] = {
		/* OpenGL ES core versions */
		{OS_TEXT("GL_ES_VERSION_2_0"), GL_ES_VERSION_2_0},

		/* ClearBufferMask */
		{OS_TEXT("GL_DEPTH_BUFFER_BIT"), GL_DEPTH_BUFFER_BIT},
		{OS_TEXT("GL_STENCIL_BUFFER_BIT"), GL_STENCIL_BUFFER_BIT},
		{OS_TEXT("GL_COLOR_BUFFER_BIT"), GL_COLOR_BUFFER_BIT},

		/* Boolean */
		{OS_TEXT("GL_FALSE"), GL_FALSE},
		{OS_TEXT("GL_TRUE"), GL_TRUE},

		/* BeginMode */
		{OS_TEXT("GL_POINTS"), GL_POINTS},
		{OS_TEXT("GL_LINES"), GL_LINES},
		{OS_TEXT("GL_LINE_LOOP"), GL_LINE_LOOP},
		{OS_TEXT("GL_LINE_STRIP"), GL_LINE_STRIP},
		{OS_TEXT("GL_TRIANGLES"), GL_TRIANGLES},
		{OS_TEXT("GL_TRIANGLE_STRIP"), GL_TRIANGLE_STRIP},
		{OS_TEXT("GL_TRIANGLE_FAN"), GL_TRIANGLE_FAN},

		/* AlphaFunction (not supported in ES20) */
		/*      GL_NEVER */
		/*      GL_LESS */
		/*      GL_EQUAL */
		/*      GL_LEQUAL */
		/*      GL_GREATER */
		/*      GL_NOTEQUAL */
		/*      GL_GEQUAL */
		/*      GL_ALWAYS */

		/* BlendingFactorDest */
		{OS_TEXT("GL_ZERO"), GL_ZERO},
		{OS_TEXT("GL_ONE"), GL_ONE},
		{OS_TEXT("GL_SRC_COLOR"), GL_SRC_COLOR},
		{OS_TEXT("GL_ONE_MINUS_SRC_COLOR"), GL_ONE_MINUS_SRC_COLOR},
		{OS_TEXT("GL_SRC_ALPHA"), GL_SRC_ALPHA},
		{OS_TEXT("GL_ONE_MINUS_SRC_ALPHA"), GL_ONE_MINUS_SRC_ALPHA},
		{OS_TEXT("GL_DST_ALPHA"), GL_DST_ALPHA},
		{OS_TEXT("GL_ONE_MINUS_DST_ALPHA"), GL_ONE_MINUS_DST_ALPHA},

		/* BlendingFactorSrc */
		/*      GL_ZERO */
		/*      GL_ONE */
		{OS_TEXT("GL_DST_COLOR"), GL_DST_COLOR},
		{OS_TEXT("GL_ONE_MINUS_DST_COLOR"), GL_ONE_MINUS_DST_COLOR},
		{OS_TEXT("GL_SRC_ALPHA_SATURATE"), GL_SRC_ALPHA_SATURATE},
		/*      GL_SRC_ALPHA */
		/*      GL_ONE_MINUS_SRC_ALPHA */
		/*      GL_DST_ALPHA */
		/*      GL_ONE_MINUS_DST_ALPHA */

		/* BlendEquationSeparate */
		{OS_TEXT("GL_FUNC_ADD"), GL_FUNC_ADD},
		{OS_TEXT("GL_BLEND_EQUATION"), GL_BLEND_EQUATION},
		{OS_TEXT("GL_BLEND_EQUATION_RGB"), GL_BLEND_EQUATION_RGB},
		{OS_TEXT("GL_BLEND_EQUATION_ALPHA"), GL_BLEND_EQUATION_ALPHA},

		/* BlendSubtract */
		{OS_TEXT("GL_FUNC_SUBTRACT"), GL_FUNC_SUBTRACT},
		{OS_TEXT("GL_FUNC_REVERSE_SUBTRACT"), GL_FUNC_REVERSE_SUBTRACT},

		/* Separate Blend Functions */
		{OS_TEXT("GL_BLEND_DST_RGB"), GL_BLEND_DST_RGB},
		{OS_TEXT("GL_BLEND_SRC_RGB"), GL_BLEND_SRC_RGB},
		{OS_TEXT("GL_BLEND_DST_ALPHA"), GL_BLEND_DST_ALPHA},
		{OS_TEXT("GL_BLEND_SRC_ALPHA"), GL_BLEND_SRC_ALPHA},
		{OS_TEXT("GL_CONSTANT_COLOR"), GL_CONSTANT_COLOR},
		{OS_TEXT("GL_ONE_MINUS_CONSTANT_COLOR"), GL_ONE_MINUS_CONSTANT_COLOR},
		{OS_TEXT("GL_CONSTANT_ALPHA"), GL_CONSTANT_ALPHA},
		{OS_TEXT("GL_ONE_MINUS_CONSTANT_ALPHA"), GL_ONE_MINUS_CONSTANT_ALPHA},
		{OS_TEXT("GL_BLEND_COLOR"), GL_BLEND_COLOR},

		/* Buffer Objects */
		{OS_TEXT("GL_ARRAY_BUFFER"), GL_ARRAY_BUFFER},
		{OS_TEXT("GL_ELEMENT_ARRAY_BUFFER"), GL_ELEMENT_ARRAY_BUFFER},
		{OS_TEXT("GL_ARRAY_BUFFER_BINDING"), GL_ARRAY_BUFFER_BINDING},
		{OS_TEXT("GL_ELEMENT_ARRAY_BUFFER_BINDING"), GL_ELEMENT_ARRAY_BUFFER_BINDING},

		{OS_TEXT("GL_STREAM_DRAW"), GL_STREAM_DRAW},
		{OS_TEXT("GL_STATIC_DRAW"), GL_STATIC_DRAW},
		{OS_TEXT("GL_DYNAMIC_DRAW"), GL_DYNAMIC_DRAW},

		{OS_TEXT("GL_BUFFER_SIZE"), GL_BUFFER_SIZE},
		{OS_TEXT("GL_BUFFER_USAGE"), GL_BUFFER_USAGE},

		{OS_TEXT("GL_CURRENT_VERTEX_ATTRIB"), GL_CURRENT_VERTEX_ATTRIB},

		/* CullFaceMode */
		{OS_TEXT("GL_FRONT"), GL_FRONT},
		{OS_TEXT("GL_BACK"), GL_BACK},
		{OS_TEXT("GL_FRONT_AND_BACK"), GL_FRONT_AND_BACK},

		/* DepthFunction */
		/*      GL_NEVER */
		/*      GL_LESS */
		/*      GL_EQUAL */
		/*      GL_LEQUAL */
		/*      GL_GREATER */
		/*      GL_NOTEQUAL */
		/*      GL_GEQUAL */
		/*      GL_ALWAYS */

		/* EnableCap */
		{OS_TEXT("GL_TEXTURE_2D"), GL_TEXTURE_2D},
		{OS_TEXT("GL_CULL_FACE"), GL_CULL_FACE},
		{OS_TEXT("GL_BLEND"), GL_BLEND},
		{OS_TEXT("GL_DITHER"), GL_DITHER},
		{OS_TEXT("GL_STENCIL_TEST"), GL_STENCIL_TEST},
		{OS_TEXT("GL_DEPTH_TEST"), GL_DEPTH_TEST},
		{OS_TEXT("GL_SCISSOR_TEST"), GL_SCISSOR_TEST},
		{OS_TEXT("GL_POLYGON_OFFSET_FILL"), GL_POLYGON_OFFSET_FILL},
		{OS_TEXT("GL_SAMPLE_ALPHA_TO_COVERAGE"), GL_SAMPLE_ALPHA_TO_COVERAGE},
		{OS_TEXT("GL_SAMPLE_COVERAGE"), GL_SAMPLE_COVERAGE},

		/* ErrorCode */
		{OS_TEXT("GL_NO_ERROR"), GL_NO_ERROR},
		{OS_TEXT("GL_INVALID_ENUM"), GL_INVALID_ENUM},
		{OS_TEXT("GL_INVALID_VALUE"), GL_INVALID_VALUE},
		{OS_TEXT("GL_INVALID_OPERATION"), GL_INVALID_OPERATION},
		{OS_TEXT("GL_OUT_OF_MEMORY"), GL_OUT_OF_MEMORY},

		/* FrontFaceDirection */
		{OS_TEXT("GL_CW"), GL_CW},
		{OS_TEXT("GL_CCW"), GL_CCW},

		/* GetPName */
		{OS_TEXT("GL_LINE_WIDTH"), GL_LINE_WIDTH},
		{OS_TEXT("GL_ALIASED_POINT_SIZE_RANGE"), GL_ALIASED_POINT_SIZE_RANGE},
		{OS_TEXT("GL_ALIASED_LINE_WIDTH_RANGE"), GL_ALIASED_LINE_WIDTH_RANGE},
		{OS_TEXT("GL_CULL_FACE_MODE"), GL_CULL_FACE_MODE},
		{OS_TEXT("GL_FRONT_FACE"), GL_FRONT_FACE},
		{OS_TEXT("GL_DEPTH_RANGE"), GL_DEPTH_RANGE},
		{OS_TEXT("GL_DEPTH_WRITEMASK"), GL_DEPTH_WRITEMASK},
		{OS_TEXT("GL_DEPTH_CLEAR_VALUE"), GL_DEPTH_CLEAR_VALUE},
		{OS_TEXT("GL_DEPTH_FUNC"), GL_DEPTH_FUNC},
		{OS_TEXT("GL_STENCIL_CLEAR_VALUE"), GL_STENCIL_CLEAR_VALUE},
		{OS_TEXT("GL_STENCIL_FUNC"), GL_STENCIL_FUNC},
		{OS_TEXT("GL_STENCIL_FAIL"), GL_STENCIL_FAIL},
		{OS_TEXT("GL_STENCIL_PASS_DEPTH_FAIL"), GL_STENCIL_PASS_DEPTH_FAIL},
		{OS_TEXT("GL_STENCIL_PASS_DEPTH_PASS"), GL_STENCIL_PASS_DEPTH_PASS},
		{OS_TEXT("GL_STENCIL_REF"), GL_STENCIL_REF},
		{OS_TEXT("GL_STENCIL_VALUE_MASK"), GL_STENCIL_VALUE_MASK},
		{OS_TEXT("GL_STENCIL_WRITEMASK"), GL_STENCIL_WRITEMASK},
		{OS_TEXT("GL_STENCIL_BACK_FUNC"), GL_STENCIL_BACK_FUNC},
		{OS_TEXT("GL_STENCIL_BACK_FAIL"), GL_STENCIL_BACK_FAIL},
		{OS_TEXT("GL_STENCIL_BACK_PASS_DEPTH_FAIL"), GL_STENCIL_BACK_PASS_DEPTH_FAIL},
		{OS_TEXT("GL_STENCIL_BACK_PASS_DEPTH_PASS"), GL_STENCIL_BACK_PASS_DEPTH_PASS},
		{OS_TEXT("GL_STENCIL_BACK_REF"), GL_STENCIL_BACK_REF},
		{OS_TEXT("GL_STENCIL_BACK_VALUE_MASK"), GL_STENCIL_BACK_VALUE_MASK},
		{OS_TEXT("GL_STENCIL_BACK_WRITEMASK"), GL_STENCIL_BACK_WRITEMASK},
		{OS_TEXT("GL_VIEWPORT"), GL_VIEWPORT},
		{OS_TEXT("GL_SCISSOR_BOX"), GL_SCISSOR_BOX},
		/*      GL_SCISSOR_TEST */
		{OS_TEXT("GL_COLOR_CLEAR_VALUE"), GL_COLOR_CLEAR_VALUE},
		{OS_TEXT("GL_COLOR_WRITEMASK"), GL_COLOR_WRITEMASK},
		{OS_TEXT("GL_UNPACK_ALIGNMENT"), GL_UNPACK_ALIGNMENT},
		{OS_TEXT("GL_PACK_ALIGNMENT"), GL_PACK_ALIGNMENT},
		{OS_TEXT("GL_MAX_TEXTURE_SIZE"), GL_MAX_TEXTURE_SIZE},
		{OS_TEXT("GL_MAX_VIEWPORT_DIMS"), GL_MAX_VIEWPORT_DIMS},
		{OS_TEXT("GL_SUBPIXEL_BITS"), GL_SUBPIXEL_BITS},
		{OS_TEXT("GL_RED_BITS"), GL_RED_BITS},
		{OS_TEXT("GL_GREEN_BITS"), GL_GREEN_BITS},
		{OS_TEXT("GL_BLUE_BITS"), GL_BLUE_BITS},
		{OS_TEXT("GL_ALPHA_BITS"), GL_ALPHA_BITS},
		{OS_TEXT("GL_DEPTH_BITS"), GL_DEPTH_BITS},
		{OS_TEXT("GL_STENCIL_BITS"), GL_STENCIL_BITS},
		{OS_TEXT("GL_POLYGON_OFFSET_UNITS"), GL_POLYGON_OFFSET_UNITS},
		/*      GL_POLYGON_OFFSET_FILL */
		{OS_TEXT("GL_POLYGON_OFFSET_FACTOR"), GL_POLYGON_OFFSET_FACTOR},
		{OS_TEXT("GL_TEXTURE_BINDING_2D"), GL_TEXTURE_BINDING_2D},
		{OS_TEXT("GL_SAMPLE_BUFFERS"), GL_SAMPLE_BUFFERS},
		{OS_TEXT("GL_SAMPLES"), GL_SAMPLES},
		{OS_TEXT("GL_SAMPLE_COVERAGE_VALUE"), GL_SAMPLE_COVERAGE_VALUE},
		{OS_TEXT("GL_SAMPLE_COVERAGE_INVERT"), GL_SAMPLE_COVERAGE_INVERT},

		/* GetTextureParameter */
		/*      GL_TEXTURE_MAG_FILTER */
		/*      GL_TEXTURE_MIN_FILTER */
		/*      GL_TEXTURE_WRAP_S */
		/*      GL_TEXTURE_WRAP_T */

		{OS_TEXT("GL_NUM_COMPRESSED_TEXTURE_FORMATS"), GL_NUM_COMPRESSED_TEXTURE_FORMATS},
		{OS_TEXT("GL_COMPRESSED_TEXTURE_FORMATS"), GL_COMPRESSED_TEXTURE_FORMATS},

		/* HintMode */
		{OS_TEXT("GL_DONT_CARE"), GL_DONT_CARE},
		{OS_TEXT("GL_FASTEST"), GL_FASTEST},
		{OS_TEXT("GL_NICEST"), GL_NICEST},

		/* HintTarget */
		{OS_TEXT("GL_GENERATE_MIPMAP_HINT"), GL_GENERATE_MIPMAP_HINT},

		/* DataType */
		{OS_TEXT("GL_BYTE"), GL_BYTE},
		{OS_TEXT("GL_UNSIGNED_BYTE"), GL_UNSIGNED_BYTE},
		{OS_TEXT("GL_SHORT"), GL_SHORT},
		{OS_TEXT("GL_UNSIGNED_SHORT"), GL_UNSIGNED_SHORT},
		{OS_TEXT("GL_INT"), GL_INT},
		{OS_TEXT("GL_UNSIGNED_INT"), GL_UNSIGNED_INT},
		{OS_TEXT("GL_FLOAT"), GL_FLOAT},
		{OS_TEXT("GL_FIXED"), GL_FIXED},

		/* PixelFormat */
		{OS_TEXT("GL_DEPTH_COMPONENT"), GL_DEPTH_COMPONENT},
		{OS_TEXT("GL_ALPHA"), GL_ALPHA},
		{OS_TEXT("GL_RGB"), GL_RGB},
		{OS_TEXT("GL_RGBA"), GL_RGBA},
		{OS_TEXT("GL_LUMINANCE"), GL_LUMINANCE},
		{OS_TEXT("GL_LUMINANCE_ALPHA"), GL_LUMINANCE_ALPHA},

		/* PixelType */
		/*      GL_UNSIGNED_BYTE */
		{OS_TEXT("GL_UNSIGNED_SHORT_4_4_4_4"), GL_UNSIGNED_SHORT_4_4_4_4},
		{OS_TEXT("GL_UNSIGNED_SHORT_5_5_5_1"), GL_UNSIGNED_SHORT_5_5_5_1},
		{OS_TEXT("GL_UNSIGNED_SHORT_5_6_5"), GL_UNSIGNED_SHORT_5_6_5},

		/* Shaders */
		{OS_TEXT("GL_FRAGMENT_SHADER"), GL_FRAGMENT_SHADER},
		{OS_TEXT("GL_VERTEX_SHADER"), GL_VERTEX_SHADER},
		{OS_TEXT("GL_MAX_VERTEX_ATTRIBS"), GL_MAX_VERTEX_ATTRIBS},
		{OS_TEXT("GL_MAX_VERTEX_UNIFORM_VECTORS"), GL_MAX_VERTEX_UNIFORM_VECTORS},
		{OS_TEXT("GL_MAX_VARYING_VECTORS"), GL_MAX_VARYING_VECTORS},
		{OS_TEXT("GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS"), GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS},
		{OS_TEXT("GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS"), GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS},
		{OS_TEXT("GL_MAX_TEXTURE_IMAGE_UNITS"), GL_MAX_TEXTURE_IMAGE_UNITS},
		{OS_TEXT("GL_MAX_FRAGMENT_UNIFORM_VECTORS"), GL_MAX_FRAGMENT_UNIFORM_VECTORS},
		{OS_TEXT("GL_SHADER_TYPE"), GL_SHADER_TYPE},
		{OS_TEXT("GL_DELETE_STATUS"), GL_DELETE_STATUS},
		{OS_TEXT("GL_LINK_STATUS"), GL_LINK_STATUS},
		{OS_TEXT("GL_VALIDATE_STATUS"), GL_VALIDATE_STATUS},
		{OS_TEXT("GL_ATTACHED_SHADERS"), GL_ATTACHED_SHADERS},
		{OS_TEXT("GL_ACTIVE_UNIFORMS"), GL_ACTIVE_UNIFORMS},
		{OS_TEXT("GL_ACTIVE_UNIFORM_MAX_LENGTH"), GL_ACTIVE_UNIFORM_MAX_LENGTH},
		{OS_TEXT("GL_ACTIVE_ATTRIBUTES"), GL_ACTIVE_ATTRIBUTES},
		{OS_TEXT("GL_ACTIVE_ATTRIBUTE_MAX_LENGTH"), GL_ACTIVE_ATTRIBUTE_MAX_LENGTH},
		{OS_TEXT("GL_SHADING_LANGUAGE_VERSION"), GL_SHADING_LANGUAGE_VERSION},
		{OS_TEXT("GL_CURRENT_PROGRAM"), GL_CURRENT_PROGRAM},

		/* StencilFunction */
		{OS_TEXT("GL_NEVER"), GL_NEVER},
		{OS_TEXT("GL_LESS"), GL_LESS},
		{OS_TEXT("GL_EQUAL"), GL_EQUAL},
		{OS_TEXT("GL_LEQUAL"), GL_LEQUAL},
		{OS_TEXT("GL_GREATER"), GL_GREATER},
		{OS_TEXT("GL_NOTEQUAL"), GL_NOTEQUAL},
		{OS_TEXT("GL_GEQUAL"), GL_GEQUAL},
		{OS_TEXT("GL_ALWAYS"), GL_ALWAYS},

		/* StencilOp */
		/*      GL_ZERO */
		{OS_TEXT("GL_KEEP"), GL_KEEP},
		{OS_TEXT("GL_REPLACE"), GL_REPLACE},
		{OS_TEXT("GL_INCR"), GL_INCR},
		{OS_TEXT("GL_DECR"), GL_DECR},
		{OS_TEXT("GL_INVERT"), GL_INVERT},
		{OS_TEXT("GL_INCR_WRAP"), GL_INCR_WRAP},
		{OS_TEXT("GL_DECR_WRAP"), GL_DECR_WRAP},

		/* StringName */
		{OS_TEXT("GL_VENDOR"), GL_VENDOR},
		{OS_TEXT("GL_RENDERER"), GL_RENDERER},
		{OS_TEXT("GL_VERSION"), GL_VERSION},
		{OS_TEXT("GL_EXTENSIONS"), GL_EXTENSIONS},

		/* TextureMagFilter */
		{OS_TEXT("GL_NEAREST"), GL_NEAREST},
		{OS_TEXT("GL_LINEAR"), GL_LINEAR},

		/* TextureMinFilter */
		/*      GL_NEAREST */
		/*      GL_LINEAR */
		{OS_TEXT("GL_NEAREST_MIPMAP_NEAREST"), GL_NEAREST_MIPMAP_NEAREST},
		{OS_TEXT("GL_LINEAR_MIPMAP_NEAREST"), GL_LINEAR_MIPMAP_NEAREST},
		{OS_TEXT("GL_NEAREST_MIPMAP_LINEAR"), GL_NEAREST_MIPMAP_LINEAR},
		{OS_TEXT("GL_LINEAR_MIPMAP_LINEAR"), GL_LINEAR_MIPMAP_LINEAR},

		/* TextureParameterName */
		{OS_TEXT("GL_TEXTURE_MAG_FILTER"), GL_TEXTURE_MAG_FILTER},
		{OS_TEXT("GL_TEXTURE_MIN_FILTER"), GL_TEXTURE_MIN_FILTER},
		{OS_TEXT("GL_TEXTURE_WRAP_S"), GL_TEXTURE_WRAP_S},
		{OS_TEXT("GL_TEXTURE_WRAP_T"), GL_TEXTURE_WRAP_T},

		/* TextureTarget */
		/*      GL_TEXTURE_2D */
		{OS_TEXT("GL_TEXTURE"), GL_TEXTURE},

		{OS_TEXT("GL_TEXTURE_CUBE_MAP"), GL_TEXTURE_CUBE_MAP},
		{OS_TEXT("GL_TEXTURE_BINDING_CUBE_MAP"), GL_TEXTURE_BINDING_CUBE_MAP},
		{OS_TEXT("GL_TEXTURE_CUBE_MAP_POSITIVE_X"), GL_TEXTURE_CUBE_MAP_POSITIVE_X},
		{OS_TEXT("GL_TEXTURE_CUBE_MAP_NEGATIVE_X"), GL_TEXTURE_CUBE_MAP_NEGATIVE_X},
		{OS_TEXT("GL_TEXTURE_CUBE_MAP_POSITIVE_Y"), GL_TEXTURE_CUBE_MAP_POSITIVE_Y},
		{OS_TEXT("GL_TEXTURE_CUBE_MAP_NEGATIVE_Y"), GL_TEXTURE_CUBE_MAP_NEGATIVE_Y},
		{OS_TEXT("GL_TEXTURE_CUBE_MAP_POSITIVE_Z"), GL_TEXTURE_CUBE_MAP_POSITIVE_Z},
		{OS_TEXT("GL_TEXTURE_CUBE_MAP_NEGATIVE_Z"), GL_TEXTURE_CUBE_MAP_NEGATIVE_Z},
		{OS_TEXT("GL_MAX_CUBE_MAP_TEXTURE_SIZE"), GL_MAX_CUBE_MAP_TEXTURE_SIZE},

		/* TextureUnit */
		{OS_TEXT("GL_TEXTURE0"), GL_TEXTURE0},
		{OS_TEXT("GL_TEXTURE1"), GL_TEXTURE1},
		{OS_TEXT("GL_TEXTURE2"), GL_TEXTURE2},
		{OS_TEXT("GL_TEXTURE3"), GL_TEXTURE3},
		{OS_TEXT("GL_TEXTURE4"), GL_TEXTURE4},
		{OS_TEXT("GL_TEXTURE5"), GL_TEXTURE5},
		{OS_TEXT("GL_TEXTURE6"), GL_TEXTURE6},
		{OS_TEXT("GL_TEXTURE7"), GL_TEXTURE7},
		{OS_TEXT("GL_TEXTURE8"), GL_TEXTURE8},
		{OS_TEXT("GL_TEXTURE9"), GL_TEXTURE9},
		{OS_TEXT("GL_TEXTURE10"), GL_TEXTURE10},
		{OS_TEXT("GL_TEXTURE11"), GL_TEXTURE11},
		{OS_TEXT("GL_TEXTURE12"), GL_TEXTURE12},
		{OS_TEXT("GL_TEXTURE13"), GL_TEXTURE13},
		{OS_TEXT("GL_TEXTURE14"), GL_TEXTURE14},
		{OS_TEXT("GL_TEXTURE15"), GL_TEXTURE15},
		{OS_TEXT("GL_TEXTURE16"), GL_TEXTURE16},
		{OS_TEXT("GL_TEXTURE17"), GL_TEXTURE17},
		{OS_TEXT("GL_TEXTURE18"), GL_TEXTURE18},
		{OS_TEXT("GL_TEXTURE19"), GL_TEXTURE19},
		{OS_TEXT("GL_TEXTURE20"), GL_TEXTURE20},
		{OS_TEXT("GL_TEXTURE21"), GL_TEXTURE21},
		{OS_TEXT("GL_TEXTURE22"), GL_TEXTURE22},
		{OS_TEXT("GL_TEXTURE23"), GL_TEXTURE23},
		{OS_TEXT("GL_TEXTURE24"), GL_TEXTURE24},
		{OS_TEXT("GL_TEXTURE25"), GL_TEXTURE25},
		{OS_TEXT("GL_TEXTURE26"), GL_TEXTURE26},
		{OS_TEXT("GL_TEXTURE27"), GL_TEXTURE27},
		{OS_TEXT("GL_TEXTURE28"), GL_TEXTURE28},
		{OS_TEXT("GL_TEXTURE29"), GL_TEXTURE29},
		{OS_TEXT("GL_TEXTURE30"), GL_TEXTURE30},
		{OS_TEXT("GL_TEXTURE31"), GL_TEXTURE31},
		{OS_TEXT("GL_ACTIVE_TEXTURE"), GL_ACTIVE_TEXTURE},

		/* TextureWrapMode */
		{OS_TEXT("GL_REPEAT"), GL_REPEAT},
		{OS_TEXT("GL_CLAMP_TO_EDGE"), GL_CLAMP_TO_EDGE},
		{OS_TEXT("GL_MIRRORED_REPEAT"), GL_MIRRORED_REPEAT},

		/* Uniform Types */
		{OS_TEXT("GL_FLOAT_VEC2"), GL_FLOAT_VEC2},
		{OS_TEXT("GL_FLOAT_VEC3"), GL_FLOAT_VEC3},
		{OS_TEXT("GL_FLOAT_VEC4"), GL_FLOAT_VEC4},
		{OS_TEXT("GL_INT_VEC2"), GL_INT_VEC2},
		{OS_TEXT("GL_INT_VEC3"), GL_INT_VEC3},
		{OS_TEXT("GL_INT_VEC4"), GL_INT_VEC4},
		{OS_TEXT("GL_BOOL"), GL_BOOL},
		{OS_TEXT("GL_BOOL_VEC2"), GL_BOOL_VEC2},
		{OS_TEXT("GL_BOOL_VEC3"), GL_BOOL_VEC3},
		{OS_TEXT("GL_BOOL_VEC4"), GL_BOOL_VEC4},
		{OS_TEXT("GL_FLOAT_MAT2"), GL_FLOAT_MAT2},
		{OS_TEXT("GL_FLOAT_MAT3"), GL_FLOAT_MAT3},
		{OS_TEXT("GL_FLOAT_MAT4"), GL_FLOAT_MAT4},
		{OS_TEXT("GL_SAMPLER_2D"), GL_SAMPLER_2D},
		{OS_TEXT("GL_SAMPLER_CUBE"), GL_SAMPLER_CUBE},

		/* Vertex Arrays */
		{OS_TEXT("GL_VERTEX_ATTRIB_ARRAY_ENABLED"), GL_VERTEX_ATTRIB_ARRAY_ENABLED},
		{OS_TEXT("GL_VERTEX_ATTRIB_ARRAY_SIZE"), GL_VERTEX_ATTRIB_ARRAY_SIZE},
		{OS_TEXT("GL_VERTEX_ATTRIB_ARRAY_STRIDE"), GL_VERTEX_ATTRIB_ARRAY_STRIDE},
		{OS_TEXT("GL_VERTEX_ATTRIB_ARRAY_TYPE"), GL_VERTEX_ATTRIB_ARRAY_TYPE},
		{OS_TEXT("GL_VERTEX_ATTRIB_ARRAY_NORMALIZED"), GL_VERTEX_ATTRIB_ARRAY_NORMALIZED},
		{OS_TEXT("GL_VERTEX_ATTRIB_ARRAY_POINTER"), GL_VERTEX_ATTRIB_ARRAY_POINTER},
		{OS_TEXT("GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING"), GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING},

		/* Read Format */
		{OS_TEXT("GL_IMPLEMENTATION_COLOR_READ_TYPE"), GL_IMPLEMENTATION_COLOR_READ_TYPE},
		{OS_TEXT("GL_IMPLEMENTATION_COLOR_READ_FORMAT"), GL_IMPLEMENTATION_COLOR_READ_FORMAT},

		/* Shader Source */
		{OS_TEXT("GL_COMPILE_STATUS"), GL_COMPILE_STATUS},
		{OS_TEXT("GL_INFO_LOG_LENGTH"), GL_INFO_LOG_LENGTH},
		{OS_TEXT("GL_SHADER_SOURCE_LENGTH"), GL_SHADER_SOURCE_LENGTH},
		{OS_TEXT("GL_SHADER_COMPILER"), GL_SHADER_COMPILER},

		/* Shader Binary */
		{OS_TEXT("GL_SHADER_BINARY_FORMATS"), GL_SHADER_BINARY_FORMATS},
		{OS_TEXT("GL_NUM_SHADER_BINARY_FORMATS"), GL_NUM_SHADER_BINARY_FORMATS},

		/* Shader Precision-Specified Types */
		{OS_TEXT("GL_LOW_FLOAT"), GL_LOW_FLOAT},
		{OS_TEXT("GL_MEDIUM_FLOAT"), GL_MEDIUM_FLOAT},
		{OS_TEXT("GL_HIGH_FLOAT"), GL_HIGH_FLOAT},
		{OS_TEXT("GL_LOW_INT"), GL_LOW_INT},
		{OS_TEXT("GL_MEDIUM_INT"), GL_MEDIUM_INT},
		{OS_TEXT("GL_HIGH_INT"), GL_HIGH_INT},

		/* Framebuffer Object. */
		{OS_TEXT("GL_FRAMEBUFFER"), GL_FRAMEBUFFER},
		{OS_TEXT("GL_RENDERBUFFER"), GL_RENDERBUFFER},

		{OS_TEXT("GL_RGBA4"), GL_RGBA4},
		{OS_TEXT("GL_RGB5_A1"), GL_RGB5_A1},
		{OS_TEXT("GL_RGB565"), GL_RGB565},
		{OS_TEXT("GL_DEPTH_COMPONENT16"), GL_DEPTH_COMPONENT16},
		{OS_TEXT("GL_STENCIL_INDEX"), GL_STENCIL_INDEX},
		{OS_TEXT("GL_STENCIL_INDEX8"), GL_STENCIL_INDEX8},

		{OS_TEXT("GL_RENDERBUFFER_WIDTH"), GL_RENDERBUFFER_WIDTH},
		{OS_TEXT("GL_RENDERBUFFER_HEIGHT"), GL_RENDERBUFFER_HEIGHT},
		{OS_TEXT("GL_RENDERBUFFER_INTERNAL_FORMAT"), GL_RENDERBUFFER_INTERNAL_FORMAT},
		{OS_TEXT("GL_RENDERBUFFER_RED_SIZE"), GL_RENDERBUFFER_RED_SIZE},
		{OS_TEXT("GL_RENDERBUFFER_GREEN_SIZE"), GL_RENDERBUFFER_GREEN_SIZE},
		{OS_TEXT("GL_RENDERBUFFER_BLUE_SIZE"), GL_RENDERBUFFER_BLUE_SIZE},
		{OS_TEXT("GL_RENDERBUFFER_ALPHA_SIZE"), GL_RENDERBUFFER_ALPHA_SIZE},
		{OS_TEXT("GL_RENDERBUFFER_DEPTH_SIZE"), GL_RENDERBUFFER_DEPTH_SIZE},
		{OS_TEXT("GL_RENDERBUFFER_STENCIL_SIZE"), GL_RENDERBUFFER_STENCIL_SIZE},

		{OS_TEXT("GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE"), GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE},
		{OS_TEXT("GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME"), GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME},
		{OS_TEXT("GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL"), GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL},
		{OS_TEXT("GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE"), GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE},

		{OS_TEXT("GL_COLOR_ATTACHMENT0"), GL_COLOR_ATTACHMENT0},
		{OS_TEXT("GL_DEPTH_ATTACHMENT"), GL_DEPTH_ATTACHMENT},
		{OS_TEXT("GL_STENCIL_ATTACHMENT"), GL_STENCIL_ATTACHMENT},

		{OS_TEXT("GL_NONE"), GL_NONE},

		{OS_TEXT("GL_FRAMEBUFFER_COMPLETE"), GL_FRAMEBUFFER_COMPLETE},
		{OS_TEXT("GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT"), GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT},
		{OS_TEXT("GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT"), GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT},
		{OS_TEXT("GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS"), GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS},
		{OS_TEXT("GL_FRAMEBUFFER_UNSUPPORTED"), GL_FRAMEBUFFER_UNSUPPORTED},

		{OS_TEXT("GL_FRAMEBUFFER_BINDING"), GL_FRAMEBUFFER_BINDING},
		{OS_TEXT("GL_RENDERBUFFER_BINDING"), GL_RENDERBUFFER_BINDING},
		{OS_TEXT("GL_MAX_RENDERBUFFER_SIZE"), GL_MAX_RENDERBUFFER_SIZE},

		{OS_TEXT("GL_INVALID_FRAMEBUFFER_OPERATION"), GL_INVALID_FRAMEBUFFER_OPERATION}, 
		{}
	};

	os->pushGlobals();
	os->setFuncs(list);
	os->setNumbers(numbers);
	os->pop();
}

void initOpenGLExt(OS * os)
{
	struct OpenGL
	{
		static int glSwapBuffers(OS * os, int params, int, int, void*)
		{
			IwGLSwapBuffers();
			return 0;
		}

		static int glVertexPointer(OS * os, int params, int, int, void*)
		{
			if(params >= 4 && os->isArray(-params+3) && (GLenum)os->toNumber(-params+1) == GL_FLOAT){
				params = os->getAbsoluteOffs(-params);
				int count = os->getLen(params+3) & ~1;
				int size = os->toInt(params+0);
				float * points = (float*)os->pushUserdata(sizeof(float)*count*size);
				for(int i = 0; i < count; i++){
					os->pushStackValue(params+3);
					os->pushNumber(i);
					os->getProperty();
					if(os->isArray()){
						for(int j = 0; j < size; j++){
							os->pushStackValue(-1);
							os->pushNumber(j);
							os->getProperty();
							points[i*size + j] = os->popFloat();
						}
					}else if(os->isObject()){
						static const OS_CHAR * xyz[] = {
							OS_TEXT("x"), OS_TEXT("y"), OS_TEXT("z")
						};
						for(int j = 0; j < size; j++){
							os->pushStackValue(-1);
							os->pushString(xyz[j%3]);
							os->getProperty();
							if(os->isNull()){
								os->pop();
								os->pushStackValue(-1);
								os->pushNumber(j);
								os->getProperty();
							}
							points[i*size + j] = os->popFloat();
						}
					}
				}
				::glVertexPointer((GLint)os->toNumber(params+0), GL_FLOAT, (GLsizei)os->toNumber(params+2), points);
				return 1;
			}
			return 0;
		}

		static int gluPerspective(OS * os, int params, int, int, void*)
		{
			cocos2d::gluPerspective(
				os->toFloat(-params+0),
				os->toFloat(-params+1),
				os->toFloat(-params+2),
				os->toFloat(-params+3));
			return 0;
		}

		static int gluLookAt(OS * os, int params, int, int, void*)
		{
			cocos2d::gluLookAt(
				os->toFloat(-params+0),
				os->toFloat(-params+1),
				os->toFloat(-params+2),
				os->toFloat(-params+3),
				os->toFloat(-params+4),
				os->toFloat(-params+5),
				os->toFloat(-params+6),
				os->toFloat(-params+7),
				os->toFloat(-params+8));
			return 0;
		}

		static int glMultMatrix(OS * os, int params, int, int, void*)
		{
			float mat[16];
			if(params == 1 && os->isArray(-params)){
				for(int i = 0; i < 16; i++){
					os->pushStackValue(-params);
					os->pushNumber(i);
					os->getProperty();
					mat[i] = os->popFloat();
				}
				::glMultMatrixf(mat);
			}else if(params == 16){
				for(int i = 0; i < 16; i++){
					mat[i] = os->toFloat(-params+i);
				}
				::glMultMatrixf(mat);
			}
			return 0;
		}

		static float clampColor(float f)
		{
			if(f < 0.0f) return 0.0f;
			if(f > 1.0f) return 1.0f;
			return f;
		}

		static int glColor(OS * os, int params, int, int, void*)
		{
			float color[4];
			if(params == 1 && os->isArray(-params)){
				for(int i = 0; i < 4; i++){
					os->pushStackValue(-params);
					os->pushNumber(i);
					os->getProperty();
					color[i] = os->isNull() ? 1.0f : clampColor(os->popFloat());
				}
			}else if(params == 1 && os->isObject(-params)){
				static const OS_CHAR * rgba[] = {
					OS_TEXT("r"), OS_TEXT("g"), OS_TEXT("b"), OS_TEXT("a") 
				};
				for(int i = 0; i < 4; i++){
					os->pushStackValue(-params);
					os->pushString(rgba[i]);
					os->getProperty();
					color[i] = os->isNull() ? 1.0f : clampColor(os->popFloat());
				}
			}else{ // if(os->isNumber(-params)){
				for(int i = 0; i < 4; i++){
					color[i] = os->isNull(-params+i) ? 1.0f : clampColor(os->toFloat(-params+i));
				}
			}
			::glColor4f(color[0], color[1], color[2], color[3]);
			return 0;
		}
	};

	OS::FuncDef funcs[] = {
		{OS_TEXT("glSwapBuffers"), OpenGL::glSwapBuffers},
		{OS_TEXT("gluPerspective"), OpenGL::gluPerspective},
		{OS_TEXT("gluLookAt"), OpenGL::gluLookAt},
		{OS_TEXT("glVertexPointer"), OpenGL::glVertexPointer},
		{OS_TEXT("glMultMatrix"), OpenGL::glMultMatrix},
		{OS_TEXT("glColor"), OpenGL::glColor},
		{}
	};

	os->pushGlobals();
	os->setFuncs(funcs);
	os->pop();

	os->require("opengl");
}
