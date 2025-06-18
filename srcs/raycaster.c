/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:02:23 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/06/04 16:16:37 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

/**
	@brief  resets in each raycasting loop iteration
	the need variables to ensure there is a correct
	calculation everytime
 */
void	reset_vars(t_data *data)
{
		data->vars->hit = 0;
		data->vars->mapX = (int)data->pos_X;
		data->vars->mapY = (int)data->pos_Y;
		data->vars->camera_X = 0;
		data->vars->ray_DirX = 0;
		data->vars->ray_DirY = 0;
		data->vars->next_X = 0;
		data->vars->next_Y = 0;
		data->vars->dir_stepX = 0;
		data->vars->dir_stepY = 0;
		data->vars->side_hit = 0;
		data->vars->wall_dist = 0;
		data->vars->side_X = 0;
		data->vars->side_Y = 0;
}
/**
	@brief main raycasting loop calling many helper functions
	to make all the needed calculacions 
 */
void	raycaster(t_data *data)
{
	int x;

	x = -1;
	while (++x < screenWidth)
	{
		reset_vars(data);
		calculate_ray_Dir(data, x);
		calculate_next(data);
		calculate_side(data);
		check_walls(data);
		calculate_perpendicular(data);
		data->buffer_z[x] = data->vars->wall_dist;
		calculate_lines(data);
		calculate_texture_X(data, x);
	}
}
