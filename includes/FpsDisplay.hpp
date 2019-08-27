/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FpsDisplay.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 15:29:20 by jules             #+#    #+#             */
/*   Updated: 2019/08/27 15:51:09 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FPSDISPLAY_HPP
# define FPSDISPLAY_HPP

# include "IGameObject.hpp"

class FpsDisplay : public Engine42::IGameObject
{
	public:
		FpsDisplay(void);
		virtual	~FpsDisplay();

		virtual void	Update(void);
		virtual void	FixedUpdate(void);
	private:
		int				_nbFrame;
		float			_lastTime;
		int				_fps;

};

#endif
