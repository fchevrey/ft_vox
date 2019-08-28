#ifndef MESHRENDERER_HPP
# define MESHRENDERER_HPP

# include <iostream>
# include "Camera.hpp"
# include "Time.hpp"
# include "Renderer.hpp"
# include <memory>

class MeshRenderer : public Renderer
{
public: 
/*	constructors / destrucors	*/
    MeshRenderer(std::shared_ptr<Model> model, std::shared_ptr<Shader>  shader, bool useNoise = false); 
    MeshRenderer(std::shared_ptr<Model> model, std::shared_ptr<Shader>  shader, const Transform &transform, bool useNoise = false); 
    MeshRenderer(const MeshRenderer & src); 
    virtual ~MeshRenderer(void); 

/*	public variables	*/
    Transform           transform;
/*	public functions	*/
    void                    Destroy(void);
	MeshRenderer &		    operator=(const MeshRenderer & rhs);
    virtual void        Draw() const;
protected:
    std::shared_ptr<Model>     _model;

private:
/*	private variables	*/
	bool				_noise;
	GLuint				_noiseID;
/*	private functions	*/
	void				InitNoiseText(void);
};
#endif
