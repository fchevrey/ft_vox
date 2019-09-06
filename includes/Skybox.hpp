#ifndef SKYBOX_HPP
# define SKYBOX_HPP

# include <iostream>
# include <vector>
/* # ifndef STB_IMAGE_IMPLEMENTATION
#  define STB_IMAGE_IMPLEMENTATION
# endif*/
# include "stb_image.h"
# include "glad.h"
# include "Shader.hpp"
# include "Camera.hpp"
# include "Model.hpp"
# include <memory>
class Skybox
{

public: 
/*	constructors / Destructor*/	
    Skybox(const std::vector<std::string> &texFilenames,const std::vector< const char *> &shadersFilenames, const std::vector<GLenum> &shaderType);
    //Skybox(Skybox const & src); 
    ~Skybox(void); 
/*	public variables*/	
/*	public functions*/	
    virtual void            Draw() const;
    virtual void    Draw(const std::shared_ptr<Shader> shader) const ;
	void	_LoadModel();

    std::string const	toString(void) const;


protected:
    unsigned int _vbo;
    unsigned int _vao;
    unsigned int _ebo;
    unsigned int _cubeMap;
/*	protected variables*/
    std::shared_ptr<Shader>         _shader;
    std::shared_ptr<Model>           _model;
/*	protected functions*/
    //void _CreateCube(void);

    static unsigned int _LoadCubeMap(const std::vector<std::string> &filenames);

};

#endif
