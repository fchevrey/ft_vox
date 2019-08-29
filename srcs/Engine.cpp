#include "Engine.hpp"
#include <algorithm>
#include <vector>
#include <map>
#include "Chunk.hpp"

Engine42::Engine          Engine42::Engine::_inst = Engine();
Engine42::Engine::Engine(void){
	_skybox = nullptr;
}

Engine42::Engine::~Engine(void){
	glDeleteBuffers(1, &_inst._quadVao);
    glDeleteBuffers(1, &_inst._quadVbo);
	glDeleteTextures(1, &_inst._colorBuffer);
	glDeleteRenderbuffers(1, &_inst._rbo);
	glDeleteFramebuffers(1, &_fbo);
}

void            Engine42::Engine::SetWindow(const SdlWindow *win) {_inst._win = win;}
void            Engine42::Engine::AddRenderer(std::list<std::shared_ptr<Renderer>> renderers)
{
	_inst._renderers.insert(_inst._renderers.end(), renderers.begin(), renderers.end());
}
void            Engine42::Engine::AddRenderer(std::shared_ptr<Renderer> renderers) 
{
	if (renderers != nullptr)
		_inst._renderers.push_back(renderers);
}

void            Engine42::Engine::AddFramebuffer(std::shared_ptr<Framebuffer> fbo) 
{
	if (fbo != nullptr)
	{
		_inst._framebuffers.push_back(fbo);
		_inst._renderers.push_back(fbo);
	}
}

void            Engine42::Engine::AddGameObject(std::shared_ptr<Engine42::IGameObject> object)
{
	if (object != nullptr)
		_inst._gameObjs.push_back(object);
}

void            Engine42::Engine::AddUIElement(std::shared_ptr<Engine42::IGameObject> object)
{
	if (object != nullptr)
		_inst._UI.push_back(object);
}
void            Engine42::Engine::ChangeFontUI(std::shared_ptr<Text> font)
{
	_inst._fontUI = font;
}
void Engine42::Engine::SetSkybox(std::shared_ptr<Skybox> skybox)
{
	_inst._skybox = skybox;
}

void            Engine42::Engine::AddGameObject(std::list<std::shared_ptr<Engine42::IGameObject>> objs)
{
	_inst._gameObjs.insert(_inst._gameObjs.begin(), objs.begin(), objs.end());
}

const SDL_Event &Engine42::Engine::GetEvent(){ return _inst._event;}
const Uint8 *Engine42::Engine::GetKeyInput(){ return _inst._keys;}

void            Engine42::Engine::AddPostProcessShader(std::shared_ptr<Shader> postProcessShader)
{
	if (_inst._shaderFbo == nullptr)
	{
		createFBO();
	}
	_inst._shaderFbo = postProcessShader;
}

void            Engine42::Engine::createFBO(void)
{
	glGenFramebuffers(1, &_inst._fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, _inst._fbo);

	glGenTextures(1, &_inst._colorBuffer);
	glBindTexture(GL_TEXTURE_2D, _inst._colorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SdlWindow::GetMain()->GetWidth(), SdlWindow::GetMain()->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _inst._colorBuffer, 0);

	glGenRenderbuffers(1, &_inst._rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, _inst._rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SdlWindow::GetMain()->GetWidth(), SdlWindow::GetMain()->GetHeight());
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _inst._rbo);

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	float quadVertices[] = { 
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 0.0f,
		1.0f,  1.0f,  1.0f, 1.0f
	};

	glGenVertexArrays(1, &_inst._quadVao);
	glGenBuffers(1, &_inst._quadVbo);
	glBindVertexArray(_inst._quadVao);
	glBindBuffer(GL_ARRAY_BUFFER, _inst._quadVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}

void            Engine42::Engine::Loop(void)
{
	bool        quit = false;
	float       delta = ((float)SDL_GetTicks()) / 1000;
	float       lastTime = delta;
	const float fixedTimeUpdate = 0.02f;
	float       fixedDelta = 0.02f;

	while (!quit)
	{
		if (_inst._shaderFbo != nullptr)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, _inst._fbo);
		}
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);  
		delta = (((float)SDL_GetTicks()) / 1000) - lastTime;
		Time::SetDeltaTime(delta);
		_inst._event.type = SDL_USEREVENT;
		while (SDL_PollEvent(&_inst._event) != 0)
		{
			if (_inst._event.type == SDL_MOUSEMOTION)
				Camera::instance->LookAround(_inst._event.motion.xrel, -_inst._event.motion.yrel);
			if ((_inst._event.type == SDL_WINDOWEVENT 
						&& _inst._event.window.event == SDL_WINDOWEVENT_CLOSE)
					|| (_inst._event.type == SDL_KEYDOWN 
						&& _inst._event.key.keysym.sym == SDLK_ESCAPE))
				quit = true;
		}
		_inst._keys = SDL_GetKeyboardState(NULL);
		_inst._UpdateAll();
		lastTime += delta;
		fixedDelta += delta;
		if (fixedDelta >= fixedTimeUpdate)
		{
			Time::SetFixedDeltaTime(fixedDelta);
			_inst._FixedUpdateAll();
			fixedDelta = 0.0f;
		}
		_inst._RenderAll();
	}
}

bool      Engine42::Engine::Destroy(std::shared_ptr<Renderer> renderer)
{
    if (renderer == nullptr)
        return false;
    _inst._renderers.remove(renderer);
    return true;
}
bool		_sort(const std::shared_ptr<Renderer> first, const std::shared_ptr<Renderer> sec)
{
	float d1 = glm::distance(first->transform.position, Camera::instance->GetPos());
	float d2 = glm::distance(sec->transform.position, Camera::instance->GetPos());
	return d2 < d1;
}

std::shared_ptr<Text>				Engine42::Engine::GetFontUI() { return _inst._fontUI; }

void                         Engine42::Engine::_RenderAll(void)
{
	if (_shaderFbo != nullptr)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
	}
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);  
	_renderers.sort(_sort);
    for (auto it = _framebuffers.begin(); it != _framebuffers.end(); it++)
         (*it)->genTexture();
	if (_shaderFbo != nullptr)
		glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
	else
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
    for (auto it = _renderers.begin(); it != _renderers.end(); it++)
         (*it)->Draw();
    if (_skybox != nullptr)
        _skybox->Draw();
    for (auto it = _UI.begin(); it != _UI.end(); it++)
         (*it)->Update();
	if (_shaderFbo != nullptr)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		_shaderFbo->use();
		_shaderFbo->setInt("screenTexture", 2);
		glBindVertexArray(_quadVao);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, _colorBuffer);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	_win->Swap();
}
void                          Engine42::Engine::_UpdateAll(void)
{
    std::list<std::shared_ptr<IGameObject>>::iterator  it;

	for (it = _gameObjs.begin(); it != _gameObjs.end(); it++)
	{
		(*it)->Update();
	}
}
void                       Engine42::Engine::ReloadShaders(void)
{
    std::for_each(_inst._renderers.begin(), _inst._renderers.end(), [] (std::shared_ptr<Renderer> x) -> void { 
        std::shared_ptr<Shader> shader = x->GetShader(); 
        if (shader)
            shader->Reload();
        });
}
void                       Engine42::Engine::_FixedUpdateAll(void) 
{
    std::list<std::shared_ptr<IGameObject>>::iterator  it;

	for (it = _gameObjs.begin(); it != _gameObjs.end(); it++)
	{
		(*it)->FixedUpdate();
	} 
}
