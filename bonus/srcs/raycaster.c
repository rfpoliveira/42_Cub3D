/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:02:23 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/09/24 15:56:35 by rpedrosa         ###   ########.fr       */
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
	data->vars->mapx = (int)data->pos_x;
	data->vars->mapy = (int)data->pos_y;
	data->vars->camera_x = 0;
	data->vars->ray_dirx = 0;
	data->vars->ray_diry = 0;
	data->vars->next_x = 0;
	data->vars->next_y = 0;
	data->vars->dir_stepx = 0;
	data->vars->dir_stepy = 0;
	data->vars->side_hit = 0;
	data->vars->wall_dist = 0;
	data->vars->side_x = 0;
	data->vars->side_y = 0;
}

/**
	@brief main raycasting loop calling many helper functions
	to make all the needed calculacions 
 */
void	raycaster(t_data *data)
{
	int	x;

	x = -1;
	while (++x < SCREENWIDTH)
	{
		reset_vars(data);
		calculate_ray_dir(data, x);
		calculate_next(data);
		calculate_side(data);
		check_walls(data);
		calculate_perpendicular(data);
		data->buffer_z[x] = data->vars->wall_dist;
		calculate_lines(data);
		calculate_texture_x(data, x);
	}
}
