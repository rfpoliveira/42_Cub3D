/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:39:54 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/09/30 16:37:24 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

/**
	@brief calculates the camera_x and ray directions
	
	camera_x is the x coordenate on the camera plane(center of the screen
	is 0, right will get 1 and left will get -1)
	ray_dir x and y will be then calculated by adding the direction vector
	and a part of the plane vector. 
 */
void	calculate_ray_dir(t_data *data, int x)
{
	data->vars->camera_x = 2 * x / data->vars->win_w - 1;
	data->vars->ray_dirx = data->dir_vec_x + data->plane_x
		* data->vars->camera_x;
	data->vars->ray_diry = data->dir_vec_y + data->plane_y
		* data->vars->camera_x;
}

/**
	@brief this calculates the distance from the next line of the grid
	to the next of that
	
	if ray_dir is 0 the division is not possible so we set it to
	a very high value so we can calculate it  
 */
void	calculate_next(t_data *data)
{
	if (fabs(data->vars->ray_dirx) < 1e-9)
		data->vars->next_x = 1e30;
	else
		data->vars->next_x = fabs(1 / data->vars->ray_dirx);
	if (fabs(data->vars->ray_diry) < 1e-9)
		data->vars->next_y = 1e30;
	else
		data->vars->next_y = fabs(1 / data->vars->ray_diry);
}

/**
	@brief this calculates the distance from the player to the next
	x or y of the grid and stores a value in dir_step so we know
	the direction we are hitting the wall from
 */
void	calculate_side(t_data *data)
{
	t_calc_vars	*vars;

	vars = data->vars;
	if (vars->ray_dirx < 0)
	{
		vars->dir_stepx = -1;
		vars->side_x = (data->pos_x - vars->mapx) * vars->next_x;
	}
	else
	{
		vars->dir_stepx = 1;
		vars->side_x = (vars->mapx + 1.0 - data->pos_x) * vars->next_x;
	}
	if (vars->ray_diry < 0)
	{
		vars->dir_stepy = -1;
		vars->side_y = (data->pos_y - vars->mapy) * vars->next_y;
	}
	else
	{
		vars->dir_stepy = 1;
		vars->side_y = (vars->mapy + 1.0 - data->pos_y) * vars->next_y;
	}
}

/**
	@brief this is the DDA algorithm that will increment 
	side until we hit a wall 	double	wall_dist;
 */
void	check_walls(t_data *data)
{
	t_calc_vars	*vars;

	vars = data->vars;
	while (vars->hit == 0)
	{
		if (vars->side_x < vars->side_y)
		{
			vars->side_x += vars->next_x;
			vars->mapx += vars->dir_stepx;
			vars->side_hit = 0;
		}
		else
		{
			vars->side_y += vars->next_y;
			vars->mapy += vars->dir_stepy;
			vars->side_hit = 1;
		}
		if (data->worldmap[vars->mapx][vars->mapy] > '0')
			something_hit(data);
	}
}

/**
	@brief now that we hit a wall we calculate the distant of the wall
	to the plane and not the plane to avoid fisheye effect
 */
void	calculate_perpendicular(t_data *data)
{
	t_calc_vars	*vars;

	vars = data->vars;
	if (vars->side_hit == 0)
		vars->wall_dist = vars->side_x - vars->next_x;
	else
		vars->wall_dist = vars->side_y - vars->next_y;
}
