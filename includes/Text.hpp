/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Text.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 13:31:18 by jules             #+#    #+#             */
/*   Updated: 2019/08/26 15:22:36 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXT_HPP
# define TEXT_HPP

# include <ft2build.h>
# include FT_FREETYPE_H
# include <string>
# include "Shader.hpp"
# include "glm.hpp"

class Text
{
	public:
		Text(const std::string font, FT_Library lib);
		virtual ~Text();

		void	RenderText(const std::string text, float x, float y, float sx, float sy, glm::vec4 color) const;

	private:
		FT_Face			_face;
		FT_GlyphSlot	_g;
		std::shared_ptr<Shader>	_shader;
		GLuint			_vbo;
		GLuint			_texture;
};

#endif
