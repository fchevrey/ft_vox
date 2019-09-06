#ifndef RENDERER_HPP
# define RENDERER_HPP

# include <iostream>
# include "Transform.hpp"
# include "Shader.hpp"
//# include "glm.hpp"
#include "gtc/matrix_transform.hpp"

class Renderer 
{

public: 
/*	constructors / destrucors	*/
    Renderer();
    Renderer(std::shared_ptr<Shader>  shader);
    Renderer(std::shared_ptr<Shader>  shader, Transform trans);
    virtual ~Renderer() {};
/*	public variables	*/
    Transform           transform;
/*	public functions	*/
    virtual glm::mat4       GetModelMatrix(void) const;
    virtual void            SetModelMatrix(glm::mat4 matrix);
    virtual void            UpdateMatrix(void);

    virtual std::shared_ptr<Shader> GetShader(void) const;
    //void                    Destroy(void);
    virtual void                    SetShader(std::shared_ptr<Shader>  shader);
    virtual void        Draw() const = 0;
protected:
    std::shared_ptr<Shader>    _shader;
    glm::mat4                  _modelMatrix;
};
#endif
