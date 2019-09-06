#include "FpsDisplay.hpp"
#include "glm.hpp"
#include <string>
#include "Engine.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "cmath"

FpsDisplay::FpsDisplay() : _nbFrame(0), _lastTime(0.0f), _fps(0.0f) {}

FpsDisplay::~FpsDisplay() {}

void	FpsDisplay::Update(void)
{
	if ((((float)SDL_GetTicks()) / 1000) - _lastTime >= 1.0f)
	{
		_fps = _nbFrame;
		_nbFrame = 0;
		_lastTime += 1.0f;
	}
	_nbFrame++;
	Engine42::Engine::GetFontUI()->RenderText(std::string("FPS: ") + std::to_string(_fps), 10.0f, SdlWindow::GetMain()->GetHeight() - 24, 1.0f, glm::vec4(1.0f)); 
	Engine42::Engine::GetFontUI()->RenderText(std::string("x: ") + std::to_string(Camera::instance->GetPos().x) + std::string(" y: ") + std::to_string(Camera::instance->GetPos().y) + std::string(" z: ") + std::to_string(Camera::instance->GetPos().z) , 10.0f, SdlWindow::GetMain()->GetHeight() - 48, 1.0f, glm::vec4(1.0f)); 
	Engine42::Engine::GetFontUI()->RenderText(std::string("Speed: ") + std::to_string(static_cast<int>(ceil(_speed))), 10.0f, SdlWindow::GetMain()->GetHeight() - 72, 1.0f, glm::vec4(1.0f)); 
}

void	FpsDisplay::FixedUpdate()
{
	_speed = glm::length(Camera::instance->GetPos() - _lastPos) / Engine42::Time::GetFixedDeltaTime();
	_lastPos = Camera::instance->GetPos();
}
