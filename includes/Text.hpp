/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Text.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 13:31:18 by jules             #+#    #+#             */
/*   Updated: 2019/09/02 12:30:34 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXT_HPP
# define TEXT_HPP

# include <ft2build.h>
# include FT_FREETYPE_H
# include <string>
# include "Shader.hpp"
# include <memory>
# include "glm.hpp"
# include <map>

struct Character {
    GLuint     TextureID;  // ID handle of the glyph texture
    glm::ivec2 Size;       // Size of glyph
    glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
    GLuint     Advance;    // Offset to advance to next glyph
};

class Text
{
	public:
		Text(const std::string font, FT_Library lib);
		virtual ~Text();

		void	RenderText(const std::string text, float x, float y, float scale, glm::vec4 color);

		void	UpdateProj();
	private:
		FT_Face			_face;
		std::shared_ptr<Shader>	_shader;
		GLuint			_vbo;
		GLuint			_vao;
		std::map<GLchar, Character> _characters;
		glm::mat4		_proj;
};

#endif
