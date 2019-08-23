#include "RenderBuffer.hpp"
#include <iostream>

RenderBuffer::RenderBuffer(void)
{
    
}
RenderBuffer::RenderBuffer(GLuint width, GLuint height, GLenum format = GL_RGBA, GLenum internalFormat = GL_RGBA, 
bool depth = false, bool stencil = false) : _width(width), _height(height), _format(format), _internalFormat(internalFormat),
_isDepth(depth), _isStencil(stencil)
{
    glGenRenderbuffers(1, &_id);
    glBindRenderbuffer(GL_RENDERBUFFER, _id); 
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _width, _height);  
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

RenderBuffer::~RenderBuffer(void)
{
    
}