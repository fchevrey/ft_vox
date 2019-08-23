#ifndef RENDERBUFFER_HPP
# define RENDERBUFFER_HPP

# include <iostream>
# include "glad.h"
# include <glm.hpp>

class RenderBuffer 
{

public: 
/*	constructors / destrucors	*/
    RenderBuffer(void); 
    RenderBuffer(GLuint width, GLuint height, GLenum format = GL_RGBA, GLenum internalFormat = GL_RGBA, bool depth = false, bool stencil = false); 
    virtual ~RenderBuffer(void); 

/*	public variables	*/
/*	public functions	*/
    bool        LoadBuffer(void);
    bool        AddStencilBuffer(void);
    bool        AddDepthBuffer(void);


private:
/*	private variables	*/
GLuint          _id;
unsigned int    _width;
unsigned int    _height;
GLenum          _format;//RGB, ARGB etc
GLenum          _internalFormat; //pixel order
GLuint          _idStencil;
GLuint          _idDepth;
bool            _isDepth;
bool            _isStencil;
/*	private functions	*/

};

#endif