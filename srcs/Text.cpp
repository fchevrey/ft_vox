#include "Text.hpp"
#include "vector"

Text::Text(const std::string font, FT_Library lib)
{
	if (FT_New_Face(lib, font.c_str(), 0, &_face))
		throw std::runtime_error(std::string("Could not open font ") + font);
	FT_Set_Pixel_Sizes(_face, 0, 48);
	_g = _face->glyph;
	std::vector<const char *>	shadersPath{"shaders/Text.vs.glsl", "shaders/Text.fs.glsl"};
	std::vector<GLenum> type{GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};
	_shader.reset(new Shader(shadersPath, type));

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)(sizeof(float) * 2));
}

Text::~Text() {}

void	Text::RenderText(const std::string text, float x, float y, float sx, float sy, glm::vec4 color) const
{
	float x2, y2, w, h;
	_shader->use();
	_shader->setVec4("color", color);
	_shader->setInt("tex", 0);
	for (auto it = text.begin(); it != text.end(); it++)
	{
		if (FT_Load_Char(_face, *it, FT_LOAD_RENDER))
			continue;

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, _g->bitmap.width, _g->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, _g->bitmap.buffer);
		
		x2 = x + _g->bitmap_left * sx;
		y2 = -y + _g->bitmap_top * sy;
		w = _g->bitmap.width * sx;
		h = _g->bitmap.rows * sy;

		GLfloat infos[] = {
			x2, -y2, 0, 0,
			x2 + w, -y2, 1, 0,
			x2, -y2 - h, 0, 1,
			x2 + w, -y2 - h , 1, 1
		};

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(infos), infos, GL_DYNAMIC_DRAW);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		x += (_g->advance.x / 64) * sx;
		y += (_g->advance.y / 64) * sy;
	}

}
