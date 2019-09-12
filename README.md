# ft_vox
42 infographie project :  a modest Voxel engine

Screenshots taken on this mac

<img src="/screenshots/mac%20config.png" width="300">
Rendering are mde using openGl 4.1


We used `FastNoise c++ library` for noise. Exteriors are made using 2d perlin noise, caves are generating using Simplex 3d noise.

For optimision, we don't draw neither empty and full chunk.

To ensure framerate chunk mesh are generated asynchronously.

chunk are 32 x 32 x 32 blocks


## Commands

=== COMMANDS ===

WASD : move camera (1 block / s)

SPACE/L-CTRL : Move camera up and down

L-SHIFT : Move faster (20 blocks / s)

ESC : Quit


## screenshots width a render view of 10 x 10 x 10 chunks :


### Exteriors :
<img src="/screenshots/320%20blocks%20at%2011.07.12%20AM.png" width="700">
<img src="/screenshots/320%20blocks%20at%2011.07.25%20AM.png" width="700">
<img src="/screenshots/320%20blocks%20at%2011.07.39%20AM.png" width="700">


### Caves : 
<img src="/screenshots/320%20blocks%20at%2011.08.01%20AM.png" width="700">
<img src="/screenshots/320%20blocks%20cave.png" width="700">

Within walls, full chunk aren't draw : 
                                                              
<img src="/screenshots/320%20blocks%20at%2011.10.00%20AM.png" width="700">



## screenshots width a render view of 8 x 8 x 8 chunks :
<img src="/screenshots/240%20blocks.png" width="700">
<img src="/screenshots/240%20blocks%20cave.png" width="700">
<img src="/screenshots/240%20blocks%20cave%202.png" width="700">


## Built With

* [SDL2](https://www.libsdl.org/) - Library for handling window.
* [STBI](https://github.com/nothings/stb) - C++ library to load image.
* [GLM](https://glm.g-truc.net/0.9.9/index.html) - C++ mathematics library for graphics software based on the OpenGL Shading Language (GLSL) specifications. 
* [OpenGL](https://www.opengl.org/) - OpenGL
* [FastNoise](https://github.com/Auburns/FastNoise) - FastNoise
* [freetype](https://www.freetype.org/) - FreeType

## Authors

* **Jules Loro** - [jloro](https://github.com/jloro)
* **Fabien Chevrey** - [fchevrey](https://github.com/fchevrey)
