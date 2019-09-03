/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FpsDisplay.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 15:29:20 by jules             #+#    #+#             */
/*   Updated: 2019/09/03 13:11:49 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FPSDISPLAY_HPP
# define FPSDISPLAY_HPP

# include "IGameObject.hpp"
# include "glm.hpp"

class FpsDisplay : public Engine42::IGameObject
{
	public:
		FpsDisplay(void);
		virtual	~FpsDisplay();

		virtual void	Update(void);
		virtual void	FixedUpdate(void);
	private:
		float			_speed;
		glm::vec3		_lastPos;
		int				_nbFrame;
		float			_lastTime;
		int				_fps;

};

#endif
