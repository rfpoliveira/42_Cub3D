/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_counter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:05:27 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/05/23 14:19:33 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

/**
	@brief counts the fps and displays it on screen 
 */
void	fps_counter(t_data *data)
{
	double frametime;
	char *display;
	char *buff;

	frametime = 0;
	struct	timeval tv;
	gettimeofday(&tv, NULL);
	data->old_time = data->curr_time;
	data->curr_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	frametime = (data->curr_time - data->old_time) / 1000.0;
	data->delta_time = frametime;
	frametime = 1.0 / frametime;
	buff = ft_itoa((int)frametime);
	display = ft_strjoin("FPS: ", buff);
	mlx_string_put(data->mlx, data->win, 10, 10, 0xFFFFFF, display);
	free(buff);
	free(display);
}