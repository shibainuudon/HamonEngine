/**
 *	@file	glext.hpp
 *
 *	@brief	glext
 */

#ifndef HAMON_RENDER_GL_GLEXT_HPP
#define HAMON_RENDER_GL_GLEXT_HPP

#include <hamon/render/gl/gl.hpp>

namespace hamon
{

inline namespace render
{

namespace gl
{

#if defined(_WIN32)
#define GET_PROC_ADDRESS(name)	wglGetProcAddress((LPCSTR)name)
#elif defined(__linux)
#define GET_PROC_ADDRESS(name)	(*glXGetProcAddressARB)((const GLubyte*)name)
#endif

inline void APIENTRY glDebugMessageCallback (GLDEBUGPROC callback, const void *userParam)
{
	static auto func = (PFNGLDEBUGMESSAGECALLBACKPROC)GET_PROC_ADDRESS("glDebugMessageCallback");
	return func(callback, userParam);
}

/* GL_VERSION_1_4 */
inline void APIENTRY glBlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha)
{
	static auto func = (PFNGLBLENDFUNCSEPARATEPROC)GET_PROC_ADDRESS("glBlendFuncSeparate");
	return func(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
}
//GLAPI void APIENTRY glMultiDrawArrays (GLenum mode, const GLint *first, const GLsizei *count, GLsizei drawcount);
//GLAPI void APIENTRY glMultiDrawElements (GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei drawcount);
//GLAPI void APIENTRY glPointParameterf (GLenum pname, GLfloat param);
//GLAPI void APIENTRY glPointParameterfv (GLenum pname, const GLfloat *params);
//GLAPI void APIENTRY glPointParameteri (GLenum pname, GLint param);
//GLAPI void APIENTRY glPointParameteriv (GLenum pname, const GLint *params);
//GLAPI void APIENTRY glBlendColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
//GLAPI void APIENTRY glBlendEquation (GLenum mode);

/* GL_VERSION_1_5 */
//GLAPI void APIENTRY glGenQueries(GLsizei n, GLuint* ids);
//GLAPI void APIENTRY glDeleteQueries(GLsizei n, const GLuint* ids);
//GLAPI GLboolean APIENTRY glIsQuery(GLuint id);
//GLAPI void APIENTRY glBeginQuery(GLenum target, GLuint id);
//GLAPI void APIENTRY glEndQuery(GLenum target);
//GLAPI void APIENTRY glGetQueryiv(GLenum target, GLenum pname, GLint* params);
//GLAPI void APIENTRY glGetQueryObjectiv(GLuint id, GLenum pname, GLint* params);
//GLAPI void APIENTRY glGetQueryObjectuiv(GLuint id, GLenum pname, GLuint* params);
//GLAPI void APIENTRY glBindBuffer(GLenum target, GLuint buffer);
inline void APIENTRY glDeleteBuffers(GLsizei n, const GLuint* buffers)
{
	static auto func = (PFNGLDELETEBUFFERSPROC)GET_PROC_ADDRESS("glDeleteBuffers");
	return func(n, buffers);
}
//GLAPI void APIENTRY glGenBuffers(GLsizei n, GLuint* buffers);
//GLAPI GLboolean APIENTRY glIsBuffer(GLuint buffer);
//GLAPI void APIENTRY glBufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage);
//GLAPI void APIENTRY glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void* data);
//GLAPI void APIENTRY glGetBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, void* data);
//GLAPI void* APIENTRY glMapBuffer(GLenum target, GLenum access);
//GLAPI GLboolean APIENTRY glUnmapBuffer(GLenum target);
//GLAPI void APIENTRY glGetBufferParameteriv(GLenum target, GLenum pname, GLint* params);
//GLAPI void APIENTRY glGetBufferPointerv(GLenum target, GLenum pname, void** params);

/* GL_VERSION_2_0 */
inline void APIENTRY glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha)
{
	static auto func = (PFNGLBLENDEQUATIONSEPARATEPROC)GET_PROC_ADDRESS("glBlendEquationSeparate");
	return func(modeRGB, modeAlpha);
}
//GLAPI void APIENTRY glDrawBuffers(GLsizei n, const GLenum* bufs);
//GLAPI void APIENTRY glStencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
//GLAPI void APIENTRY glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask);
//GLAPI void APIENTRY glStencilMaskSeparate(GLenum face, GLuint mask);
inline void APIENTRY glAttachShader(GLuint program, GLuint shader)
{
	static auto func = (PFNGLATTACHSHADERPROC)GET_PROC_ADDRESS("glAttachShader");
	return func(program, shader);
}
//GLAPI void APIENTRY glBindAttribLocation(GLuint program, GLuint index, const GLchar* name);
inline void APIENTRY glCompileShader(GLuint shader)
{
	static auto func = (PFNGLCOMPILESHADERPROC)GET_PROC_ADDRESS("glCompileShader");
	return func(shader);
}
inline GLuint APIENTRY glCreateProgram(void)
{
	static auto func = (PFNGLCREATEPROGRAMPROC)GET_PROC_ADDRESS("glCreateProgram");
	return func();
}
inline GLuint APIENTRY glCreateShader(GLenum type)
{
	static auto func = (PFNGLCREATESHADERPROC)GET_PROC_ADDRESS("glCreateShader");
	return func(type);
}
inline void APIENTRY glDeleteProgram(GLuint program)
{
	static auto func = (PFNGLDELETEPROGRAMPROC)GET_PROC_ADDRESS("glDeleteProgram");
	return func(program);
}
inline void APIENTRY glDeleteShader(GLuint shader)
{
	static auto func = (PFNGLDELETESHADERPROC)GET_PROC_ADDRESS("glDeleteShader");
	return func(shader);
}
//GLAPI void APIENTRY glDetachShader(GLuint program, GLuint shader);
//GLAPI void APIENTRY glDisableVertexAttribArray(GLuint index);
//GLAPI void APIENTRY glEnableVertexAttribArray(GLuint index);
//GLAPI void APIENTRY glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
inline void APIENTRY glGetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name)
{
	static auto func = (PFNGLGETACTIVEUNIFORMPROC)GET_PROC_ADDRESS("glGetActiveUniform");
	return func(program, index, bufSize, length, size, type, name);
}
//GLAPI void APIENTRY glGetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei* count, GLuint* shaders);
//GLAPI GLint APIENTRY glGetAttribLocation(GLuint program, const GLchar* name);
inline void APIENTRY glGetProgramiv(GLuint program, GLenum pname, GLint* params)
{
	static auto func = (PFNGLGETPROGRAMIVPROC)GET_PROC_ADDRESS("glGetProgramiv");
	return func(program, pname, params);
}
inline void APIENTRY glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog)
{
	static auto func = (PFNGLGETPROGRAMINFOLOGPROC)GET_PROC_ADDRESS("glGetProgramInfoLog");
	return func(program, bufSize, length, infoLog);
}
inline void APIENTRY glGetShaderiv(GLuint shader, GLenum pname, GLint* params)
{
	static auto func = (PFNGLGETSHADERIVPROC)GET_PROC_ADDRESS("glGetShaderiv");
	return func(shader, pname, params);
}
inline void APIENTRY glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog)
{
	static auto func = (PFNGLGETSHADERINFOLOGPROC)GET_PROC_ADDRESS("glGetShaderInfoLog");
	return func(shader, bufSize, length, infoLog);
}
//GLAPI void APIENTRY glGetShaderSource(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* source);
inline GLint APIENTRY glGetUniformLocation(GLuint program, const GLchar* name)
{
	static auto func = (PFNGLGETUNIFORMLOCATIONPROC)GET_PROC_ADDRESS("glGetUniformLocation");
	return func(program, name);
}
//GLAPI void APIENTRY glGetUniformfv(GLuint program, GLint location, GLfloat* params);
//GLAPI void APIENTRY glGetUniformiv(GLuint program, GLint location, GLint* params);
//GLAPI void APIENTRY glGetVertexAttribdv(GLuint index, GLenum pname, GLdouble* params);
//GLAPI void APIENTRY glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat* params);
//GLAPI void APIENTRY glGetVertexAttribiv(GLuint index, GLenum pname, GLint* params);
//GLAPI void APIENTRY glGetVertexAttribPointerv(GLuint index, GLenum pname, void** pointer);
//GLAPI GLboolean APIENTRY glIsProgram(GLuint program);
//GLAPI GLboolean APIENTRY glIsShader(GLuint shader);
inline void APIENTRY glLinkProgram(GLuint program)
{
	static auto func = (PFNGLLINKPROGRAMPROC)GET_PROC_ADDRESS("glLinkProgram");
	return func(program);
}
inline void APIENTRY glShaderSource(GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length)
{
	static auto func = (PFNGLSHADERSOURCEPROC)GET_PROC_ADDRESS("glShaderSource");
	return func(shader, count, string, length);
}
inline void APIENTRY glUseProgram(GLuint program)
{
	static auto func = (PFNGLUSEPROGRAMPROC)GET_PROC_ADDRESS("glUseProgram");
	return func(program);
}
//GLAPI void APIENTRY glUniform1f(GLint location, GLfloat v0);
//GLAPI void APIENTRY glUniform2f(GLint location, GLfloat v0, GLfloat v1);
//GLAPI void APIENTRY glUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
//GLAPI void APIENTRY glUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
//GLAPI void APIENTRY glUniform1i(GLint location, GLint v0);
//GLAPI void APIENTRY glUniform2i(GLint location, GLint v0, GLint v1);
//GLAPI void APIENTRY glUniform3i(GLint location, GLint v0, GLint v1, GLint v2);
//GLAPI void APIENTRY glUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
inline void APIENTRY glUniform1fv(GLint location, GLsizei count, const GLfloat* value)
{
	static auto func = (PFNGLUNIFORM1FVPROC)GET_PROC_ADDRESS("glUniform1fv");
	return func(location, count, value);
}
inline void APIENTRY glUniform2fv(GLint location, GLsizei count, const GLfloat* value)
{
	static auto func = (PFNGLUNIFORM2FVPROC)GET_PROC_ADDRESS("glUniform2fv");
	return func(location, count, value);
}
inline void APIENTRY glUniform3fv(GLint location, GLsizei count, const GLfloat* value)
{
	static auto func = (PFNGLUNIFORM3FVPROC)GET_PROC_ADDRESS("glUniform3fv");
	return func(location, count, value);
}
inline void APIENTRY glUniform4fv(GLint location, GLsizei count, const GLfloat* value)
{
	static auto func = (PFNGLUNIFORM4FVPROC)GET_PROC_ADDRESS("glUniform4fv");
	return func(location, count, value);
}
inline void APIENTRY glUniform1iv(GLint location, GLsizei count, const GLint* value)
{
	static auto func = (PFNGLUNIFORM1IVPROC)GET_PROC_ADDRESS("glUniform1iv");
	return func(location, count, value);
}
inline void APIENTRY glUniform2iv(GLint location, GLsizei count, const GLint* value)
{
	static auto func = (PFNGLUNIFORM2IVPROC)GET_PROC_ADDRESS("glUniform2iv");
	return func(location, count, value);
}
inline void APIENTRY glUniform3iv(GLint location, GLsizei count, const GLint* value)
{
	static auto func = (PFNGLUNIFORM3IVPROC)GET_PROC_ADDRESS("glUniform3iv");
	return func(location, count, value);
}
inline void APIENTRY glUniform4iv(GLint location, GLsizei count, const GLint* value)
{
	static auto func = (PFNGLUNIFORM4IVPROC)GET_PROC_ADDRESS("glUniform4iv");
	return func(location, count, value);
}
inline void APIENTRY glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	static auto func = (PFNGLUNIFORMMATRIX2FVPROC)GET_PROC_ADDRESS("glUniformMatrix2fv");
	return func(location, count, transpose, value);
}
inline void APIENTRY glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	static auto func = (PFNGLUNIFORMMATRIX3FVPROC)GET_PROC_ADDRESS("glUniformMatrix3fv");
	return func(location, count, transpose, value);
}
inline void APIENTRY glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	static auto func = (PFNGLUNIFORMMATRIX4FVPROC)GET_PROC_ADDRESS("glUniformMatrix4fv");
	return func(location, count, transpose, value);
}
//GLAPI void APIENTRY glValidateProgram(GLuint program);
//GLAPI void APIENTRY glVertexAttrib1d(GLuint index, GLdouble x);
//GLAPI void APIENTRY glVertexAttrib1dv(GLuint index, const GLdouble* v);
//GLAPI void APIENTRY glVertexAttrib1f(GLuint index, GLfloat x);
//GLAPI void APIENTRY glVertexAttrib1fv(GLuint index, const GLfloat* v);
//GLAPI void APIENTRY glVertexAttrib1s(GLuint index, GLshort x);
//GLAPI void APIENTRY glVertexAttrib1sv(GLuint index, const GLshort* v);
//GLAPI void APIENTRY glVertexAttrib2d(GLuint index, GLdouble x, GLdouble y);
//GLAPI void APIENTRY glVertexAttrib2dv(GLuint index, const GLdouble* v);
//GLAPI void APIENTRY glVertexAttrib2f(GLuint index, GLfloat x, GLfloat y);
//GLAPI void APIENTRY glVertexAttrib2fv(GLuint index, const GLfloat* v);
//GLAPI void APIENTRY glVertexAttrib2s(GLuint index, GLshort x, GLshort y);
//GLAPI void APIENTRY glVertexAttrib2sv(GLuint index, const GLshort* v);
//GLAPI void APIENTRY glVertexAttrib3d(GLuint index, GLdouble x, GLdouble y, GLdouble z);
//GLAPI void APIENTRY glVertexAttrib3dv(GLuint index, const GLdouble* v);
//GLAPI void APIENTRY glVertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z);
//GLAPI void APIENTRY glVertexAttrib3fv(GLuint index, const GLfloat* v);
//GLAPI void APIENTRY glVertexAttrib3s(GLuint index, GLshort x, GLshort y, GLshort z);
//GLAPI void APIENTRY glVertexAttrib3sv(GLuint index, const GLshort* v);
//GLAPI void APIENTRY glVertexAttrib4Nbv(GLuint index, const GLbyte* v);
//GLAPI void APIENTRY glVertexAttrib4Niv(GLuint index, const GLint* v);
//GLAPI void APIENTRY glVertexAttrib4Nsv(GLuint index, const GLshort* v);
//GLAPI void APIENTRY glVertexAttrib4Nub(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
//GLAPI void APIENTRY glVertexAttrib4Nubv(GLuint index, const GLubyte* v);
//GLAPI void APIENTRY glVertexAttrib4Nuiv(GLuint index, const GLuint* v);
//GLAPI void APIENTRY glVertexAttrib4Nusv(GLuint index, const GLushort* v);
//GLAPI void APIENTRY glVertexAttrib4bv(GLuint index, const GLbyte* v);
//GLAPI void APIENTRY glVertexAttrib4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
//GLAPI void APIENTRY glVertexAttrib4dv(GLuint index, const GLdouble* v);
//GLAPI void APIENTRY glVertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
//GLAPI void APIENTRY glVertexAttrib4fv(GLuint index, const GLfloat* v);
//GLAPI void APIENTRY glVertexAttrib4iv(GLuint index, const GLint* v);
//GLAPI void APIENTRY glVertexAttrib4s(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
//GLAPI void APIENTRY glVertexAttrib4sv(GLuint index, const GLshort* v);
//GLAPI void APIENTRY glVertexAttrib4ubv(GLuint index, const GLubyte* v);
//GLAPI void APIENTRY glVertexAttrib4uiv(GLuint index, const GLuint* v);
//GLAPI void APIENTRY glVertexAttrib4usv(GLuint index, const GLushort* v);
//GLAPI void APIENTRY glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);

/* GL_VERSION_2_1 */
inline void APIENTRY glUniformMatrix2x3fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
	static auto func = (PFNGLUNIFORMMATRIX2X3FVPROC)GET_PROC_ADDRESS("glUniformMatrix2x3fv");
	return func(location, count, transpose, value);
}
inline void APIENTRY glUniformMatrix3x2fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
	static auto func = (PFNGLUNIFORMMATRIX3X2FVPROC)GET_PROC_ADDRESS("glUniformMatrix3x2fv");
	return func(location, count, transpose, value);
}
inline void APIENTRY glUniformMatrix2x4fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
	static auto func = (PFNGLUNIFORMMATRIX2X4FVPROC)GET_PROC_ADDRESS("glUniformMatrix2x4fv");
	return func(location, count, transpose, value);
}
inline void APIENTRY glUniformMatrix4x2fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
	static auto func = (PFNGLUNIFORMMATRIX4X2FVPROC)GET_PROC_ADDRESS("glUniformMatrix4x2fv");
	return func(location, count, transpose, value);
}
inline void APIENTRY glUniformMatrix3x4fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
	static auto func = (PFNGLUNIFORMMATRIX3X4FVPROC)GET_PROC_ADDRESS("glUniformMatrix3x4fv");
	return func(location, count, transpose, value);
}
inline void APIENTRY glUniformMatrix4x3fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
	static auto func = (PFNGLUNIFORMMATRIX4X3FVPROC)GET_PROC_ADDRESS("glUniformMatrix4x3fv");
	return func(location, count, transpose, value);
}

/* GL_VERSION_3_0 */
//GLAPI void APIENTRY glColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
//GLAPI void APIENTRY glGetBooleani_v(GLenum target, GLuint index, GLboolean* data);
//GLAPI void APIENTRY glGetIntegeri_v(GLenum target, GLuint index, GLint* data);
//GLAPI void APIENTRY glEnablei(GLenum target, GLuint index);
//GLAPI void APIENTRY glDisablei(GLenum target, GLuint index);
//GLAPI GLboolean APIENTRY glIsEnabledi(GLenum target, GLuint index);
//GLAPI void APIENTRY glBeginTransformFeedback(GLenum primitiveMode);
//GLAPI void APIENTRY glEndTransformFeedback(void);
//GLAPI void APIENTRY glBindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
inline void APIENTRY glBindBufferBase(GLenum target, GLuint index, GLuint buffer)
{
	static auto func = (PFNGLBINDBUFFERBASEPROC)GET_PROC_ADDRESS("glBindBufferBase");
	return func(target, index, buffer);
}
//GLAPI void APIENTRY glTransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar* const* varyings, GLenum bufferMode);
//GLAPI void APIENTRY glGetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLsizei* size, GLenum* type, GLchar* name);
//GLAPI void APIENTRY glClampColor(GLenum target, GLenum clamp);
//GLAPI void APIENTRY glBeginConditionalRender(GLuint id, GLenum mode);
//GLAPI void APIENTRY glEndConditionalRender(void);
//GLAPI void APIENTRY glVertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer);
//GLAPI void APIENTRY glGetVertexAttribIiv(GLuint index, GLenum pname, GLint* params);
//GLAPI void APIENTRY glGetVertexAttribIuiv(GLuint index, GLenum pname, GLuint* params);
//GLAPI void APIENTRY glVertexAttribI1i(GLuint index, GLint x);
//GLAPI void APIENTRY glVertexAttribI2i(GLuint index, GLint x, GLint y);
//GLAPI void APIENTRY glVertexAttribI3i(GLuint index, GLint x, GLint y, GLint z);
//GLAPI void APIENTRY glVertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w);
//GLAPI void APIENTRY glVertexAttribI1ui(GLuint index, GLuint x);
//GLAPI void APIENTRY glVertexAttribI2ui(GLuint index, GLuint x, GLuint y);
//GLAPI void APIENTRY glVertexAttribI3ui(GLuint index, GLuint x, GLuint y, GLuint z);
//GLAPI void APIENTRY glVertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
//GLAPI void APIENTRY glVertexAttribI1iv(GLuint index, const GLint* v);
//GLAPI void APIENTRY glVertexAttribI2iv(GLuint index, const GLint* v);
//GLAPI void APIENTRY glVertexAttribI3iv(GLuint index, const GLint* v);
//GLAPI void APIENTRY glVertexAttribI4iv(GLuint index, const GLint* v);
//GLAPI void APIENTRY glVertexAttribI1uiv(GLuint index, const GLuint* v);
//GLAPI void APIENTRY glVertexAttribI2uiv(GLuint index, const GLuint* v);
//GLAPI void APIENTRY glVertexAttribI3uiv(GLuint index, const GLuint* v);
//GLAPI void APIENTRY glVertexAttribI4uiv(GLuint index, const GLuint* v);
//GLAPI void APIENTRY glVertexAttribI4bv(GLuint index, const GLbyte* v);
//GLAPI void APIENTRY glVertexAttribI4sv(GLuint index, const GLshort* v);
//GLAPI void APIENTRY glVertexAttribI4ubv(GLuint index, const GLubyte* v);
//GLAPI void APIENTRY glVertexAttribI4usv(GLuint index, const GLushort* v);
//GLAPI void APIENTRY glGetUniformuiv(GLuint program, GLint location, GLuint* params);
//GLAPI void APIENTRY glBindFragDataLocation(GLuint program, GLuint color, const GLchar* name);
//GLAPI GLint APIENTRY glGetFragDataLocation(GLuint program, const GLchar* name);
//GLAPI void APIENTRY glUniform1ui(GLint location, GLuint v0);
//GLAPI void APIENTRY glUniform2ui(GLint location, GLuint v0, GLuint v1);
//GLAPI void APIENTRY glUniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2);
//GLAPI void APIENTRY glUniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
inline void APIENTRY glUniform1uiv(GLint location, GLsizei count, const GLuint* value)
{
	static auto func = (PFNGLUNIFORM1UIVPROC)GET_PROC_ADDRESS("glUniform1uiv");
	return func(location, count, value);
}
inline void APIENTRY glUniform2uiv(GLint location, GLsizei count, const GLuint* value)
{
	static auto func = (PFNGLUNIFORM2UIVPROC)GET_PROC_ADDRESS("glUniform2uiv");
	return func(location, count, value);
}
inline void APIENTRY glUniform3uiv(GLint location, GLsizei count, const GLuint* value)
{
	static auto func = (PFNGLUNIFORM3UIVPROC)GET_PROC_ADDRESS("glUniform3uiv");
	return func(location, count, value);
}
inline void APIENTRY glUniform4uiv(GLint location, GLsizei count, const GLuint* value)
{
	static auto func = (PFNGLUNIFORM4UIVPROC)GET_PROC_ADDRESS("glUniform4uiv");
	return func(location, count, value);
}
//GLAPI void APIENTRY glTexParameterIiv(GLenum target, GLenum pname, const GLint* params);
//GLAPI void APIENTRY glTexParameterIuiv(GLenum target, GLenum pname, const GLuint* params);
//GLAPI void APIENTRY glGetTexParameterIiv(GLenum target, GLenum pname, GLint* params);
//GLAPI void APIENTRY glGetTexParameterIuiv(GLenum target, GLenum pname, GLuint* params);
//GLAPI void APIENTRY glClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint* value);
//GLAPI void APIENTRY glClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint* value);
//GLAPI void APIENTRY glClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat* value);
//GLAPI void APIENTRY glClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
//GLAPI const GLubyte* APIENTRY glGetStringi(GLenum name, GLuint index);
//GLAPI GLboolean APIENTRY glIsRenderbuffer(GLuint renderbuffer);
//GLAPI void APIENTRY glBindRenderbuffer(GLenum target, GLuint renderbuffer);
//GLAPI void APIENTRY glDeleteRenderbuffers(GLsizei n, const GLuint* renderbuffers);
//GLAPI void APIENTRY glGenRenderbuffers(GLsizei n, GLuint* renderbuffers);
//GLAPI void APIENTRY glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
//GLAPI void APIENTRY glGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint* params);
//GLAPI GLboolean APIENTRY glIsFramebuffer(GLuint framebuffer);
//GLAPI void APIENTRY glBindFramebuffer(GLenum target, GLuint framebuffer);
//GLAPI void APIENTRY glDeleteFramebuffers(GLsizei n, const GLuint* framebuffers);
//GLAPI void APIENTRY glGenFramebuffers(GLsizei n, GLuint* framebuffers);
//GLAPI GLenum APIENTRY glCheckFramebufferStatus(GLenum target);
//GLAPI void APIENTRY glFramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
//GLAPI void APIENTRY glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
//GLAPI void APIENTRY glFramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
//GLAPI void APIENTRY glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
//GLAPI void APIENTRY glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint* params);
//GLAPI void APIENTRY glGenerateMipmap(GLenum target);
//GLAPI void APIENTRY glBlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
//GLAPI void APIENTRY glRenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
//GLAPI void APIENTRY glFramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
//GLAPI void* APIENTRY glMapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
//GLAPI void APIENTRY glFlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length);
inline void APIENTRY glBindVertexArray(GLuint array)
{
	static auto func = (PFNGLBINDVERTEXARRAYPROC)GET_PROC_ADDRESS("glBindVertexArray");
	return func(array);
}
inline void APIENTRY glDeleteVertexArrays(GLsizei n, const GLuint* arrays)
{
	static auto func = (PFNGLDELETEVERTEXARRAYSPROC)GET_PROC_ADDRESS("glDeleteVertexArrays");
	return func(n, arrays);
}
//GLAPI void APIENTRY glGenVertexArrays(GLsizei n, GLuint* arrays);
//GLAPI GLboolean APIENTRY glIsVertexArray(GLuint array);

/* GL_VERSION_3_1 */
//GLAPI void APIENTRY glDrawArraysInstanced (GLenum mode, GLint first, GLsizei count, GLsizei instancecount);
//GLAPI void APIENTRY glDrawElementsInstanced (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount);
//GLAPI void APIENTRY glTexBuffer (GLenum target, GLenum internalformat, GLuint buffer);
//GLAPI void APIENTRY glPrimitiveRestartIndex (GLuint index);
//GLAPI void APIENTRY glCopyBufferSubData (GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
//GLAPI void APIENTRY glGetUniformIndices (GLuint program, GLsizei uniformCount, const GLchar *const*uniformNames, GLuint *uniformIndices);
inline void APIENTRY glGetActiveUniformsiv (GLuint program, GLsizei uniformCount, const GLuint *uniformIndices, GLenum pname, GLint *params)
{
	static auto func = (PFNGLGETACTIVEUNIFORMSIVPROC)GET_PROC_ADDRESS("glGetActiveUniformsiv");
	return func(program, uniformCount, uniformIndices, pname, params);
}
//GLAPI void APIENTRY glGetActiveUniformName (GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformName);
//GLAPI GLuint APIENTRY glGetUniformBlockIndex (GLuint program, const GLchar *uniformBlockName);
inline void APIENTRY glGetActiveUniformBlockiv (GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint *params)
{
	static auto func = (PFNGLGETACTIVEUNIFORMBLOCKIVPROC)GET_PROC_ADDRESS("glGetActiveUniformBlockiv");
	return func(program, uniformBlockIndex, pname, params);
}
inline void APIENTRY glGetActiveUniformBlockName (GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformBlockName)
{
	static auto func = (PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC)GET_PROC_ADDRESS("glGetActiveUniformBlockName");
	return func(program, uniformBlockIndex, bufSize, length, uniformBlockName);
}
inline void APIENTRY glUniformBlockBinding (GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding)
{
	static auto func = (PFNGLUNIFORMBLOCKBINDINGPROC)GET_PROC_ADDRESS("glUniformBlockBinding");
	return func(program, uniformBlockIndex, uniformBlockBinding);
}

/* GL_VERSION_4_0 */
//GLAPI void APIENTRY glMinSampleShading (GLfloat value);
//GLAPI void APIENTRY glBlendEquationi (GLuint buf, GLenum mode);
//GLAPI void APIENTRY glBlendEquationSeparatei (GLuint buf, GLenum modeRGB, GLenum modeAlpha);
//GLAPI void APIENTRY glBlendFunci (GLuint buf, GLenum src, GLenum dst);
//GLAPI void APIENTRY glBlendFuncSeparatei (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
//GLAPI void APIENTRY glDrawArraysIndirect (GLenum mode, const void *indirect);
//GLAPI void APIENTRY glDrawElementsIndirect (GLenum mode, GLenum type, const void *indirect);
//GLAPI void APIENTRY glUniform1d (GLint location, GLdouble x);
//GLAPI void APIENTRY glUniform2d (GLint location, GLdouble x, GLdouble y);
//GLAPI void APIENTRY glUniform3d (GLint location, GLdouble x, GLdouble y, GLdouble z);
//GLAPI void APIENTRY glUniform4d (GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
inline void APIENTRY glUniform1dv (GLint location, GLsizei count, const GLdouble *value)
{
	static auto func = (PFNGLUNIFORM1DVPROC)GET_PROC_ADDRESS("glUniform1dv");
	return func(location, count, value);
}
inline void APIENTRY glUniform2dv (GLint location, GLsizei count, const GLdouble *value)
{
	static auto func = (PFNGLUNIFORM2DVPROC)GET_PROC_ADDRESS("glUniform2dv");
	return func(location, count, value);
}
inline void APIENTRY glUniform3dv (GLint location, GLsizei count, const GLdouble *value)
{
	static auto func = (PFNGLUNIFORM3DVPROC)GET_PROC_ADDRESS("glUniform3dv");
	return func(location, count, value);
}
inline void APIENTRY glUniform4dv (GLint location, GLsizei count, const GLdouble *value)
{
	static auto func = (PFNGLUNIFORM4DVPROC)GET_PROC_ADDRESS("glUniform4dv");
	return func(location, count, value);
}
inline void APIENTRY glUniformMatrix2dv (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
{
	static auto func = (PFNGLUNIFORMMATRIX2DVPROC)GET_PROC_ADDRESS("glUniformMatrix2dv");
	return func(location, count, transpose, value);
}
inline void APIENTRY glUniformMatrix3dv (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
{
	static auto func = (PFNGLUNIFORMMATRIX3DVPROC)GET_PROC_ADDRESS("glUniformMatrix3dv");
	return func(location, count, transpose, value);
}
inline void APIENTRY glUniformMatrix4dv (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
{
	static auto func = (PFNGLUNIFORMMATRIX4DVPROC)GET_PROC_ADDRESS("glUniformMatrix4dv");
	return func(location, count, transpose, value);
}
inline void APIENTRY glUniformMatrix2x3dv (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
{
	static auto func = (PFNGLUNIFORMMATRIX2X3DVPROC)GET_PROC_ADDRESS("glUniformMatrix2x3dv");
	return func(location, count, transpose, value);
}
inline void APIENTRY glUniformMatrix2x4dv (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
{
	static auto func = (PFNGLUNIFORMMATRIX2X4DVPROC)GET_PROC_ADDRESS("glUniformMatrix2x4dv");
	return func(location, count, transpose, value);
}
inline void APIENTRY glUniformMatrix3x2dv (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
{
	static auto func = (PFNGLUNIFORMMATRIX3X2DVPROC)GET_PROC_ADDRESS("glUniformMatrix3x2dv");
	return func(location, count, transpose, value);
}
inline void APIENTRY glUniformMatrix3x4dv (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
{
	static auto func = (PFNGLUNIFORMMATRIX3X4DVPROC)GET_PROC_ADDRESS("glUniformMatrix3x4dv");
	return func(location, count, transpose, value);
}
inline void APIENTRY glUniformMatrix4x2dv (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
{
	static auto func = (PFNGLUNIFORMMATRIX4X2DVPROC)GET_PROC_ADDRESS("glUniformMatrix4x2dv");
	return func(location, count, transpose, value);
}
inline void APIENTRY glUniformMatrix4x3dv (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
{
	static auto func = (PFNGLUNIFORMMATRIX4X3DVPROC)GET_PROC_ADDRESS("glUniformMatrix4x3dv");
	return func(location, count, transpose, value);
}
//GLAPI void APIENTRY glGetUniformdv (GLuint program, GLint location, GLdouble *params);
//GLAPI GLint APIENTRY glGetSubroutineUniformLocation (GLuint program, GLenum shadertype, const GLchar *name);
//GLAPI GLuint APIENTRY glGetSubroutineIndex (GLuint program, GLenum shadertype, const GLchar *name);
//GLAPI void APIENTRY glGetActiveSubroutineUniformiv (GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint *values);
//GLAPI void APIENTRY glGetActiveSubroutineUniformName (GLuint program, GLenum shadertype, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name);
//GLAPI void APIENTRY glGetActiveSubroutineName (GLuint program, GLenum shadertype, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name);
//GLAPI void APIENTRY glUniformSubroutinesuiv (GLenum shadertype, GLsizei count, const GLuint *indices);
//GLAPI void APIENTRY glGetUniformSubroutineuiv (GLenum shadertype, GLint location, GLuint *params);
//GLAPI void APIENTRY glGetProgramStageiv (GLuint program, GLenum shadertype, GLenum pname, GLint *values);
//GLAPI void APIENTRY glPatchParameteri (GLenum pname, GLint value);
//GLAPI void APIENTRY glPatchParameterfv (GLenum pname, const GLfloat *values);
//GLAPI void APIENTRY glBindTransformFeedback (GLenum target, GLuint id);
//GLAPI void APIENTRY glDeleteTransformFeedbacks (GLsizei n, const GLuint *ids);
//GLAPI void APIENTRY glGenTransformFeedbacks (GLsizei n, GLuint *ids);
//GLAPI GLboolean APIENTRY glIsTransformFeedback (GLuint id);
//GLAPI void APIENTRY glPauseTransformFeedback (void);
//GLAPI void APIENTRY glResumeTransformFeedback (void);
//GLAPI void APIENTRY glDrawTransformFeedback (GLenum mode, GLuint id);
//GLAPI void APIENTRY glDrawTransformFeedbackStream (GLenum mode, GLuint id, GLuint stream);
//GLAPI void APIENTRY glBeginQueryIndexed (GLenum target, GLuint index, GLuint id);
//GLAPI void APIENTRY glEndQueryIndexed (GLenum target, GLuint index);
//GLAPI void APIENTRY glGetQueryIndexediv (GLenum target, GLuint index, GLenum pname, GLint *params);

/* GL_VERSION_4_1 */
//GLAPI void APIENTRY glReleaseShaderCompiler (void);
//GLAPI void APIENTRY glShaderBinary (GLsizei count, const GLuint *shaders, GLenum binaryFormat, const void *binary, GLsizei length);
//GLAPI void APIENTRY glGetShaderPrecisionFormat (GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision);
inline void APIENTRY glDepthRangef (GLfloat n, GLfloat f)
{
	static auto func = (PFNGLDEPTHRANGEFPROC)GET_PROC_ADDRESS("glDepthRangef");
	return func(n, f);
}
//GLAPI void APIENTRY glClearDepthf (GLfloat d);
//GLAPI void APIENTRY glGetProgramBinary (GLuint program, GLsizei bufSize, GLsizei *length, GLenum *binaryFormat, void *binary);
//GLAPI void APIENTRY glProgramBinary (GLuint program, GLenum binaryFormat, const void *binary, GLsizei length);
//GLAPI void APIENTRY glProgramParameteri (GLuint program, GLenum pname, GLint value);
//GLAPI void APIENTRY glUseProgramStages (GLuint pipeline, GLbitfield stages, GLuint program);
//GLAPI void APIENTRY glActiveShaderProgram (GLuint pipeline, GLuint program);
//GLAPI GLuint APIENTRY glCreateShaderProgramv (GLenum type, GLsizei count, const GLchar *const*strings);
//GLAPI void APIENTRY glBindProgramPipeline (GLuint pipeline);
//GLAPI void APIENTRY glDeleteProgramPipelines (GLsizei n, const GLuint *pipelines);
//GLAPI void APIENTRY glGenProgramPipelines (GLsizei n, GLuint *pipelines);
//GLAPI GLboolean APIENTRY glIsProgramPipeline (GLuint pipeline);
//GLAPI void APIENTRY glGetProgramPipelineiv (GLuint pipeline, GLenum pname, GLint *params);
//GLAPI void APIENTRY glProgramUniform1i (GLuint program, GLint location, GLint v0);
//GLAPI void APIENTRY glProgramUniform1iv (GLuint program, GLint location, GLsizei count, const GLint *value);
//GLAPI void APIENTRY glProgramUniform1f (GLuint program, GLint location, GLfloat v0);
//GLAPI void APIENTRY glProgramUniform1fv (GLuint program, GLint location, GLsizei count, const GLfloat *value);
//GLAPI void APIENTRY glProgramUniform1d (GLuint program, GLint location, GLdouble v0);
//GLAPI void APIENTRY glProgramUniform1dv (GLuint program, GLint location, GLsizei count, const GLdouble *value);
//GLAPI void APIENTRY glProgramUniform1ui (GLuint program, GLint location, GLuint v0);
//GLAPI void APIENTRY glProgramUniform1uiv (GLuint program, GLint location, GLsizei count, const GLuint *value);
//GLAPI void APIENTRY glProgramUniform2i (GLuint program, GLint location, GLint v0, GLint v1);
//GLAPI void APIENTRY glProgramUniform2iv (GLuint program, GLint location, GLsizei count, const GLint *value);
//GLAPI void APIENTRY glProgramUniform2f (GLuint program, GLint location, GLfloat v0, GLfloat v1);
//GLAPI void APIENTRY glProgramUniform2fv (GLuint program, GLint location, GLsizei count, const GLfloat *value);
//GLAPI void APIENTRY glProgramUniform2d (GLuint program, GLint location, GLdouble v0, GLdouble v1);
//GLAPI void APIENTRY glProgramUniform2dv (GLuint program, GLint location, GLsizei count, const GLdouble *value);
//GLAPI void APIENTRY glProgramUniform2ui (GLuint program, GLint location, GLuint v0, GLuint v1);
//GLAPI void APIENTRY glProgramUniform2uiv (GLuint program, GLint location, GLsizei count, const GLuint *value);
//GLAPI void APIENTRY glProgramUniform3i (GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
//GLAPI void APIENTRY glProgramUniform3iv (GLuint program, GLint location, GLsizei count, const GLint *value);
//GLAPI void APIENTRY glProgramUniform3f (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
//GLAPI void APIENTRY glProgramUniform3fv (GLuint program, GLint location, GLsizei count, const GLfloat *value);
//GLAPI void APIENTRY glProgramUniform3d (GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2);
//GLAPI void APIENTRY glProgramUniform3dv (GLuint program, GLint location, GLsizei count, const GLdouble *value);
//GLAPI void APIENTRY glProgramUniform3ui (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2);
//GLAPI void APIENTRY glProgramUniform3uiv (GLuint program, GLint location, GLsizei count, const GLuint *value);
//GLAPI void APIENTRY glProgramUniform4i (GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
//GLAPI void APIENTRY glProgramUniform4iv (GLuint program, GLint location, GLsizei count, const GLint *value);
//GLAPI void APIENTRY glProgramUniform4f (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
//GLAPI void APIENTRY glProgramUniform4fv (GLuint program, GLint location, GLsizei count, const GLfloat *value);
//GLAPI void APIENTRY glProgramUniform4d (GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3);
//GLAPI void APIENTRY glProgramUniform4dv (GLuint program, GLint location, GLsizei count, const GLdouble *value);
//GLAPI void APIENTRY glProgramUniform4ui (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
//GLAPI void APIENTRY glProgramUniform4uiv (GLuint program, GLint location, GLsizei count, const GLuint *value);
//GLAPI void APIENTRY glProgramUniformMatrix2fv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
//GLAPI void APIENTRY glProgramUniformMatrix3fv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
//GLAPI void APIENTRY glProgramUniformMatrix4fv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
//GLAPI void APIENTRY glProgramUniformMatrix2dv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
//GLAPI void APIENTRY glProgramUniformMatrix3dv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
//GLAPI void APIENTRY glProgramUniformMatrix4dv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
//GLAPI void APIENTRY glProgramUniformMatrix2x3fv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
//GLAPI void APIENTRY glProgramUniformMatrix3x2fv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
//GLAPI void APIENTRY glProgramUniformMatrix2x4fv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
//GLAPI void APIENTRY glProgramUniformMatrix4x2fv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
//GLAPI void APIENTRY glProgramUniformMatrix3x4fv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
//GLAPI void APIENTRY glProgramUniformMatrix4x3fv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
//GLAPI void APIENTRY glProgramUniformMatrix2x3dv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
//GLAPI void APIENTRY glProgramUniformMatrix3x2dv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
//GLAPI void APIENTRY glProgramUniformMatrix2x4dv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
//GLAPI void APIENTRY glProgramUniformMatrix4x2dv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
//GLAPI void APIENTRY glProgramUniformMatrix3x4dv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
//GLAPI void APIENTRY glProgramUniformMatrix4x3dv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
//GLAPI void APIENTRY glValidateProgramPipeline (GLuint pipeline);
//GLAPI void APIENTRY glGetProgramPipelineInfoLog (GLuint pipeline, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
//GLAPI void APIENTRY glVertexAttribL1d (GLuint index, GLdouble x);
//GLAPI void APIENTRY glVertexAttribL2d (GLuint index, GLdouble x, GLdouble y);
//GLAPI void APIENTRY glVertexAttribL3d (GLuint index, GLdouble x, GLdouble y, GLdouble z);
//GLAPI void APIENTRY glVertexAttribL4d (GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
//GLAPI void APIENTRY glVertexAttribL1dv (GLuint index, const GLdouble *v);
//GLAPI void APIENTRY glVertexAttribL2dv (GLuint index, const GLdouble *v);
//GLAPI void APIENTRY glVertexAttribL3dv (GLuint index, const GLdouble *v);
//GLAPI void APIENTRY glVertexAttribL4dv (GLuint index, const GLdouble *v);
//GLAPI void APIENTRY glVertexAttribLPointer (GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer);
//GLAPI void APIENTRY glGetVertexAttribLdv (GLuint index, GLenum pname, GLdouble *params);
//GLAPI void APIENTRY glViewportArrayv (GLuint first, GLsizei count, const GLfloat *v);
//GLAPI void APIENTRY glViewportIndexedf (GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
//GLAPI void APIENTRY glViewportIndexedfv (GLuint index, const GLfloat *v);
//GLAPI void APIENTRY glScissorArrayv (GLuint first, GLsizei count, const GLint *v);
//GLAPI void APIENTRY glScissorIndexed (GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height);
//GLAPI void APIENTRY glScissorIndexedv (GLuint index, const GLint *v);
//GLAPI void APIENTRY glDepthRangeArrayv (GLuint first, GLsizei count, const GLdouble *v);
//GLAPI void APIENTRY glDepthRangeIndexed (GLuint index, GLdouble n, GLdouble f);
//GLAPI void APIENTRY glGetFloati_v (GLenum target, GLuint index, GLfloat *data);
//GLAPI void APIENTRY glGetDoublei_v (GLenum target, GLuint index, GLdouble *data);

/* GL_VERSION_4_3 */
//GLAPI void APIENTRY glClearBufferData(GLenum target, GLenum internalformat, GLenum format, GLenum type, const void* data);
//GLAPI void APIENTRY glClearBufferSubData(GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void* data);
//GLAPI void APIENTRY glDispatchCompute(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z);
//GLAPI void APIENTRY glDispatchComputeIndirect(GLintptr indirect);
//GLAPI void APIENTRY glCopyImageSubData(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth);
//GLAPI void APIENTRY glFramebufferParameteri(GLenum target, GLenum pname, GLint param);
//GLAPI void APIENTRY glGetFramebufferParameteriv(GLenum target, GLenum pname, GLint* params);
//GLAPI void APIENTRY glGetInternalformati64v(GLenum target, GLenum internalformat, GLenum pname, GLsizei count, GLint64* params);
//GLAPI void APIENTRY glInvalidateTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth);
//GLAPI void APIENTRY glInvalidateTexImage(GLuint texture, GLint level);
//GLAPI void APIENTRY glInvalidateBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr length);
//GLAPI void APIENTRY glInvalidateBufferData(GLuint buffer);
//GLAPI void APIENTRY glInvalidateFramebuffer(GLenum target, GLsizei numAttachments, const GLenum* attachments);
//GLAPI void APIENTRY glInvalidateSubFramebuffer(GLenum target, GLsizei numAttachments, const GLenum* attachments, GLint x, GLint y, GLsizei width, GLsizei height);
//GLAPI void APIENTRY glMultiDrawArraysIndirect(GLenum mode, const void* indirect, GLsizei drawcount, GLsizei stride);
//GLAPI void APIENTRY glMultiDrawElementsIndirect(GLenum mode, GLenum type, const void* indirect, GLsizei drawcount, GLsizei stride);
//GLAPI void APIENTRY glGetProgramInterfaceiv(GLuint program, GLenum programInterface, GLenum pname, GLint* params);
//GLAPI GLuint APIENTRY glGetProgramResourceIndex(GLuint program, GLenum programInterface, const GLchar* name);
//GLAPI void APIENTRY glGetProgramResourceName(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei* length, GLchar* name);
//GLAPI void APIENTRY glGetProgramResourceiv(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum* props, GLsizei count, GLsizei* length, GLint* params);
//GLAPI GLint APIENTRY glGetProgramResourceLocation(GLuint program, GLenum programInterface, const GLchar* name);
//GLAPI GLint APIENTRY glGetProgramResourceLocationIndex(GLuint program, GLenum programInterface, const GLchar* name);
//GLAPI void APIENTRY glShaderStorageBlockBinding(GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding);
//GLAPI void APIENTRY glTexBufferRange(GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);
//GLAPI void APIENTRY glTexStorage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
//GLAPI void APIENTRY glTexStorage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
//GLAPI void APIENTRY glTextureView(GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
//GLAPI void APIENTRY glBindVertexBuffer(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
//GLAPI void APIENTRY glVertexAttribFormat(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
//GLAPI void APIENTRY glVertexAttribIFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
//GLAPI void APIENTRY glVertexAttribLFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
//GLAPI void APIENTRY glVertexAttribBinding(GLuint attribindex, GLuint bindingindex);
//GLAPI void APIENTRY glVertexBindingDivisor(GLuint bindingindex, GLuint divisor);
inline void APIENTRY glDebugMessageControl(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint* ids, GLboolean enabled)
{
	static auto func = (PFNGLDEBUGMESSAGECONTROLPROC)GET_PROC_ADDRESS("glDebugMessageControl");
	return func(source, type, severity, count, ids, enabled);
}
//GLAPI void APIENTRY glDebugMessageInsert(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* buf);
//GLAPI void APIENTRY glDebugMessageCallback(GLDEBUGPROC callback, const void* userParam);
//GLAPI GLuint APIENTRY glGetDebugMessageLog(GLuint count, GLsizei bufSize, GLenum* sources, GLenum* types, GLuint* ids, GLenum* severities, GLsizei* lengths, GLchar* messageLog);
//GLAPI void APIENTRY glPushDebugGroup(GLenum source, GLuint id, GLsizei length, const GLchar* message);
//GLAPI void APIENTRY glPopDebugGroup(void);
//GLAPI void APIENTRY glObjectLabel(GLenum identifier, GLuint name, GLsizei length, const GLchar* label);
//GLAPI void APIENTRY glGetObjectLabel(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei* length, GLchar* label);
//GLAPI void APIENTRY glObjectPtrLabel(const void* ptr, GLsizei length, const GLchar* label);
//GLAPI void APIENTRY glGetObjectPtrLabel(const void* ptr, GLsizei bufSize, GLsizei* length, GLchar* label);

/* GL_VERSION_4_5 */
//GLAPI void APIENTRY glClipControl(GLenum origin, GLenum depth);
//GLAPI void APIENTRY glCreateTransformFeedbacks(GLsizei n, GLuint* ids);
//GLAPI void APIENTRY glTransformFeedbackBufferBase(GLuint xfb, GLuint index, GLuint buffer);
//GLAPI void APIENTRY glTransformFeedbackBufferRange(GLuint xfb, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
//GLAPI void APIENTRY glGetTransformFeedbackiv(GLuint xfb, GLenum pname, GLint* param);
//GLAPI void APIENTRY glGetTransformFeedbacki_v(GLuint xfb, GLenum pname, GLuint index, GLint* param);
//GLAPI void APIENTRY glGetTransformFeedbacki64_v(GLuint xfb, GLenum pname, GLuint index, GLint64* param);
inline void APIENTRY glCreateBuffers(GLsizei n, GLuint* buffers)
{
	static auto func = (PFNGLCREATEBUFFERSPROC)GET_PROC_ADDRESS("glCreateBuffers");
	return func(n, buffers);
}
//GLAPI void APIENTRY glNamedBufferStorage(GLuint buffer, GLsizeiptr size, const void* data, GLbitfield flags);
inline void APIENTRY glNamedBufferData(GLuint buffer, GLsizeiptr size, const void* data, GLenum usage)
{
	static auto func = (PFNGLNAMEDBUFFERDATAPROC)GET_PROC_ADDRESS("glNamedBufferData");
	return func(buffer, size, data, usage);
}
inline void APIENTRY glNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, const void* data)
{
	static auto func = (PFNGLNAMEDBUFFERSUBDATAPROC)GET_PROC_ADDRESS("glNamedBufferSubData");
	return func(buffer, offset, size, data);
}
//GLAPI void APIENTRY glCopyNamedBufferSubData(GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
//GLAPI void APIENTRY glClearNamedBufferData(GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void* data);
//GLAPI void APIENTRY glClearNamedBufferSubData(GLuint buffer, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void* data);
//GLAPI void* APIENTRY glMapNamedBuffer(GLuint buffer, GLenum access);
//GLAPI void* APIENTRY glMapNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access);
//GLAPI GLboolean APIENTRY glUnmapNamedBuffer(GLuint buffer);
//GLAPI void APIENTRY glFlushMappedNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length);
//GLAPI void APIENTRY glGetNamedBufferParameteriv(GLuint buffer, GLenum pname, GLint* params);
//GLAPI void APIENTRY glGetNamedBufferParameteri64v(GLuint buffer, GLenum pname, GLint64* params);
//GLAPI void APIENTRY glGetNamedBufferPointerv(GLuint buffer, GLenum pname, void** params);
//GLAPI void APIENTRY glGetNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, void* data);
//GLAPI void APIENTRY glCreateFramebuffers(GLsizei n, GLuint* framebuffers);
//GLAPI void APIENTRY glNamedFramebufferRenderbuffer(GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
//GLAPI void APIENTRY glNamedFramebufferParameteri(GLuint framebuffer, GLenum pname, GLint param);
//GLAPI void APIENTRY glNamedFramebufferTexture(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level);
//GLAPI void APIENTRY glNamedFramebufferTextureLayer(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer);
//GLAPI void APIENTRY glNamedFramebufferDrawBuffer(GLuint framebuffer, GLenum buf);
//GLAPI void APIENTRY glNamedFramebufferDrawBuffers(GLuint framebuffer, GLsizei n, const GLenum* bufs);
//GLAPI void APIENTRY glNamedFramebufferReadBuffer(GLuint framebuffer, GLenum src);
//GLAPI void APIENTRY glInvalidateNamedFramebufferData(GLuint framebuffer, GLsizei numAttachments, const GLenum* attachments);
//GLAPI void APIENTRY glInvalidateNamedFramebufferSubData(GLuint framebuffer, GLsizei numAttachments, const GLenum* attachments, GLint x, GLint y, GLsizei width, GLsizei height);
//GLAPI void APIENTRY glClearNamedFramebufferiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint* value);
//GLAPI void APIENTRY glClearNamedFramebufferuiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint* value);
//GLAPI void APIENTRY glClearNamedFramebufferfv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat* value);
//GLAPI void APIENTRY glClearNamedFramebufferfi(GLuint framebuffer, GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
//GLAPI void APIENTRY glBlitNamedFramebuffer(GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
//GLAPI GLenum APIENTRY glCheckNamedFramebufferStatus(GLuint framebuffer, GLenum target);
//GLAPI void APIENTRY glGetNamedFramebufferParameteriv(GLuint framebuffer, GLenum pname, GLint* param);
//GLAPI void APIENTRY glGetNamedFramebufferAttachmentParameteriv(GLuint framebuffer, GLenum attachment, GLenum pname, GLint* params);
//GLAPI void APIENTRY glCreateRenderbuffers(GLsizei n, GLuint* renderbuffers);
//GLAPI void APIENTRY glNamedRenderbufferStorage(GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height);
//GLAPI void APIENTRY glNamedRenderbufferStorageMultisample(GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
//GLAPI void APIENTRY glGetNamedRenderbufferParameteriv(GLuint renderbuffer, GLenum pname, GLint* params);
//GLAPI void APIENTRY glCreateTextures(GLenum target, GLsizei n, GLuint* textures);
//GLAPI void APIENTRY glTextureBuffer(GLuint texture, GLenum internalformat, GLuint buffer);
//GLAPI void APIENTRY glTextureBufferRange(GLuint texture, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);
//GLAPI void APIENTRY glTextureStorage1D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width);
//GLAPI void APIENTRY glTextureStorage2D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
//GLAPI void APIENTRY glTextureStorage3D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
//GLAPI void APIENTRY glTextureStorage2DMultisample(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
//GLAPI void APIENTRY glTextureStorage3DMultisample(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
//GLAPI void APIENTRY glTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels);
//GLAPI void APIENTRY glTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels);
//GLAPI void APIENTRY glTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels);
//GLAPI void APIENTRY glCompressedTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void* data);
//GLAPI void APIENTRY glCompressedTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data);
//GLAPI void APIENTRY glCompressedTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void* data);
//GLAPI void APIENTRY glCopyTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
//GLAPI void APIENTRY glCopyTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
//GLAPI void APIENTRY glCopyTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
//GLAPI void APIENTRY glTextureParameterf(GLuint texture, GLenum pname, GLfloat param);
//GLAPI void APIENTRY glTextureParameterfv(GLuint texture, GLenum pname, const GLfloat* param);
//GLAPI void APIENTRY glTextureParameteri(GLuint texture, GLenum pname, GLint param);
//GLAPI void APIENTRY glTextureParameterIiv(GLuint texture, GLenum pname, const GLint* params);
//GLAPI void APIENTRY glTextureParameterIuiv(GLuint texture, GLenum pname, const GLuint* params);
//GLAPI void APIENTRY glTextureParameteriv(GLuint texture, GLenum pname, const GLint* param);
//GLAPI void APIENTRY glGenerateTextureMipmap(GLuint texture);
//GLAPI void APIENTRY glBindTextureUnit(GLuint unit, GLuint texture);
//GLAPI void APIENTRY glGetTextureImage(GLuint texture, GLint level, GLenum format, GLenum type, GLsizei bufSize, void* pixels);
//GLAPI void APIENTRY glGetCompressedTextureImage(GLuint texture, GLint level, GLsizei bufSize, void* pixels);
//GLAPI void APIENTRY glGetTextureLevelParameterfv(GLuint texture, GLint level, GLenum pname, GLfloat* params);
//GLAPI void APIENTRY glGetTextureLevelParameteriv(GLuint texture, GLint level, GLenum pname, GLint* params);
//GLAPI void APIENTRY glGetTextureParameterfv(GLuint texture, GLenum pname, GLfloat* params);
//GLAPI void APIENTRY glGetTextureParameterIiv(GLuint texture, GLenum pname, GLint* params);
//GLAPI void APIENTRY glGetTextureParameterIuiv(GLuint texture, GLenum pname, GLuint* params);
//GLAPI void APIENTRY glGetTextureParameteriv(GLuint texture, GLenum pname, GLint* params);
inline void APIENTRY glCreateVertexArrays(GLsizei n, GLuint* arrays)
{
	static auto func = (PFNGLCREATEVERTEXARRAYSPROC)GET_PROC_ADDRESS("glCreateVertexArrays");
	return func(n, arrays);
}
//GLAPI void APIENTRY glDisableVertexArrayAttrib(GLuint vaobj, GLuint index);
inline void APIENTRY glEnableVertexArrayAttrib(GLuint vaobj, GLuint index)
{
	static auto func = (PFNGLENABLEVERTEXARRAYATTRIBPROC)GET_PROC_ADDRESS("glEnableVertexArrayAttrib");
	return func(vaobj, index);
}
inline void APIENTRY glVertexArrayElementBuffer(GLuint vaobj, GLuint buffer)
{
	static auto func = (PFNGLVERTEXARRAYELEMENTBUFFERPROC)GET_PROC_ADDRESS("glVertexArrayElementBuffer");
	return func(vaobj, buffer);
}
inline void APIENTRY glVertexArrayVertexBuffer(GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride)
{
	static auto func = (PFNGLVERTEXARRAYVERTEXBUFFERPROC)GET_PROC_ADDRESS("glVertexArrayVertexBuffer");
	return func(vaobj, bindingindex, buffer, offset, stride);
}
//GLAPI void APIENTRY glVertexArrayVertexBuffers(GLuint vaobj, GLuint first, GLsizei count, const GLuint* buffers, const GLintptr* offsets, const GLsizei* strides);
inline void APIENTRY glVertexArrayAttribBinding(GLuint vaobj, GLuint attribindex, GLuint bindingindex)
{
	static auto func = (PFNGLVERTEXARRAYATTRIBBINDINGPROC)GET_PROC_ADDRESS("glVertexArrayAttribBinding");
	return func(vaobj, attribindex, bindingindex);
}
inline void APIENTRY glVertexArrayAttribFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset)
{
	static auto func = (PFNGLVERTEXARRAYATTRIBFORMATPROC)GET_PROC_ADDRESS("glVertexArrayAttribFormat");
	return func(vaobj, attribindex, size, type, normalized, relativeoffset);
}
//GLAPI void APIENTRY glVertexArrayAttribIFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
//GLAPI void APIENTRY glVertexArrayAttribLFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
//GLAPI void APIENTRY glVertexArrayBindingDivisor(GLuint vaobj, GLuint bindingindex, GLuint divisor);
//GLAPI void APIENTRY glGetVertexArrayiv(GLuint vaobj, GLenum pname, GLint* param);
//GLAPI void APIENTRY glGetVertexArrayIndexediv(GLuint vaobj, GLuint index, GLenum pname, GLint* param);
//GLAPI void APIENTRY glGetVertexArrayIndexed64iv(GLuint vaobj, GLuint index, GLenum pname, GLint64* param);
//GLAPI void APIENTRY glCreateSamplers(GLsizei n, GLuint* samplers);
//GLAPI void APIENTRY glCreateProgramPipelines(GLsizei n, GLuint* pipelines);
//GLAPI void APIENTRY glCreateQueries(GLenum target, GLsizei n, GLuint* ids);
//GLAPI void APIENTRY glGetQueryBufferObjecti64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
//GLAPI void APIENTRY glGetQueryBufferObjectiv(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
//GLAPI void APIENTRY glGetQueryBufferObjectui64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
//GLAPI void APIENTRY glGetQueryBufferObjectuiv(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
//GLAPI void APIENTRY glMemoryBarrierByRegion(GLbitfield barriers);
//GLAPI void APIENTRY glGetTextureSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize, void* pixels);
//GLAPI void APIENTRY glGetCompressedTextureSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei bufSize, void* pixels);
//GLAPI GLenum APIENTRY glGetGraphicsResetStatus(void);
//GLAPI void APIENTRY glGetnCompressedTexImage(GLenum target, GLint lod, GLsizei bufSize, void* pixels);
//GLAPI void APIENTRY glGetnTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void* pixels);
//GLAPI void APIENTRY glGetnUniformdv(GLuint program, GLint location, GLsizei bufSize, GLdouble* params);
//GLAPI void APIENTRY glGetnUniformfv(GLuint program, GLint location, GLsizei bufSize, GLfloat* params);
//GLAPI void APIENTRY glGetnUniformiv(GLuint program, GLint location, GLsizei bufSize, GLint* params);
//GLAPI void APIENTRY glGetnUniformuiv(GLuint program, GLint location, GLsizei bufSize, GLuint* params);
//GLAPI void APIENTRY glReadnPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void* data);
//GLAPI void APIENTRY glTextureBarrier(void);

}	// namespace gl

}	// inline namespace render

}	// namespace hamon

#endif // HAMON_RENDER_GL_GLEXT_HPP
