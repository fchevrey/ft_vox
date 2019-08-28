#ifndef ARENDERER_HPP
# define ARENDERER_HPP

# include <iostream>
# include "Transform.hpp"
# include "Model.hpp"


class ARenderer 
{

public: 
/*	constructors / destrucors	*/
    ARenderer() : _shader(nullptr) {}
    ARenderer(std::shared_ptr<Shader>  shader) :_shader(shader) {}
    ARenderer(std::shared_ptr<Shader>  shader, Transform trans) : _shader(shader) {transform = trans;}
    virtual ~ARenderer() {};
/*	public variables	*/
    Transform           transform;
/*	public functions	*/
    virtual glm::mat4       GetModelMatrix(void) const  = 0;
    virtual void            SetModelMatrix(glm::mat4 matrix) = 0;
    virtual void            UpdateMatrix(void) = 0;
    virtual std::shared_ptr<Shader> GetShader(void) const { return _shader;}
    //void                    Destroy(void);
    virtual void                    SetShader(std::shared_ptr<Shader>  shader) {_shader = shader;}
    virtual void        Draw() const = 0;
protected:
    std::shared_ptr<Shader>    _shader;
    glm::mat4                  _modelMatrix;
};
#endif