#ifndef FRAMEBUFFERRENDERER_HPP
# define FRAMEBUFFERRENDERER_HPP

# include <iostream>
# include "MeshRenderer.hpp"
# include "FrameBuffer.hpp"

class FrameBufferRenderer : public MeshRenderer
{

public: 
/*	constructors / destrucors	*/
    FrameBufferRenderer(void); 
    FrameBufferRenderer(const FrameBufferRenderer & src); 
    virtual ~FrameBufferRenderer(void); 

/*	public variables	*/
/*	public functions	*/
	FrameBufferRenderer &		operator=(const FrameBufferRenderer & rhs);

    std::string const	toString(void) const;

private:
/*	private variables	*/
    Shader          *_shader;
    FrameBuffer     *_frameBuffer;
/*	private functions	*/

};

std::ostream &	operator<< (std::ostream & o, const FrameBufferRenderer & rhs);

#endif


#include "FrameBufferRenderer.hpp"
#include <iostream>

FrameBufferRenderer::FrameBufferRenderer(void)
{
    
}

FrameBufferRenderer::FrameBufferRenderer(FrameBufferRenderer const & src) 
{
    *this = src;
    return;
}

FrameBufferRenderer::~FrameBufferRenderer(void)
{
    
}

FrameBufferRenderer &	FrameBufferRenderer::operator=(FrameBufferRenderer const & rhs)
{
    return *this;
}

std::string const FrameBufferRenderer::toString(void) const
{
    
}

std::ostream &	operator<< (std::ostream & o, FrameBufferRenderer const & rhs)
{
    o << rhs.toString();
    return o;
}