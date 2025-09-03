/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:39:54 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/06/06 11:30:37 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

/**
	@brief calculates the camera_X and ray directions
	
	camera_X is the x coordenate on the camera plane(center of the screen
	is 0, right will get 1 and left will get -1)
	ray_dir x and y will be then calculated by adding the direction vector
	and a part of the plane vector. 
 */
void	calculate_ray_Dir(t_data *data, int x)
{
	data->vars->camera_X = 2 * x / data->vars->win_w - 1;
	data->vars->ray_DirX = data->dir_vec_X + data->plane_X * data->vars->camera_X;
	data->vars->ray_DirY = data->dir_vec_Y + data->plane_Y * data->vars->camera_X;
}

/**
	@brief this calculates the distance from the next line of the grid
	to the next of that
	
	if ray_dir is 0 the division is not possible so we set it to
	a very high value so we can calculate it  
 */
void	calculate_next(t_data *data)
{
	if (fabs(data->vars->ray_DirX) < 1e-9)
		data->vars->next_X = 1e30;
	else
		data->vars->next_X = fabs(1 / data->vars->ray_DirX);
	if (fabs(data->vars->ray_DirY) < 1e-9)
		data->vars->next_Y = 1e30;
	else
		data->vars->next_Y = fabs(1 / data->vars->ray_DirY);
}
/**
	@brief this calculates the distance from the player to the next
	x or y of the grid and stores a value in dir_step so we know
	the direction we are hitting the wall from
 */
void	calculate_side(t_data *data)
{
	t_calc_vars *vars;

	vars = data->vars;
	if (vars->ray_DirX < 0)
	{
	  vars->dir_stepX = -1;
	  vars->side_X = (data->pos_X - vars->mapX) * vars->next_X;
	}
	else
	{
	  vars->dir_stepX = 1;
	  vars->side_X = (vars->mapX + 1.0 - data->pos_X) * vars->next_X;
	}
	if (vars->ray_DirY < 0)
	{
	  vars->dir_stepY = -1;
	  vars->side_Y = (data->pos_Y - vars->mapY) * vars->next_Y;
	}
	else
	{
	  vars->dir_stepY = 1;
	  vars->side_Y = (vars->mapY + 1.0 - data->pos_Y) * vars->next_Y;
	}
}

/**
	@brief this is the DDA algorithm that will increment 
	side until we hit a wall 	double	wall_dist;
 */
void	check_walls(t_data *data)
{
	t_calc_vars *vars;
	int id_hit;

	vars = data->vars;
	while(vars->hit == 0)
	{
		if (vars->side_X < vars->side_Y)
		{
			vars->side_X += vars->next_X;
			vars->mapX += vars->dir_stepX;
			vars->side_hit = 0;
		}
		else
		{
			vars->side_Y += vars->next_Y;
			vars->mapY += vars->dir_stepY;
			vars->side_hit = 1;
		}
		if (data->worldMap[vars->mapX][vars->mapY] > 0)
		{
			if (data->worldMap[vars->mapX][vars->mapY] == 1)
				vars->hit = 1;
			if (data->controls[7] && data->worldMap[vars->mapX][vars->mapY] == 2 
			&& (data->vars->camera_X > -0.1 && data->vars->camera_X < 0.1) && data->shoot_flag == 0)
			{
				id_hit = enemy_hit(data, vars->mapX, vars->mapY);
				if (id_hit != -1)
					take_enemy_out(data, id_hit);
			}
		}
	}
}
/**
	@brief now that we hit a wall we calculate the distant of the wall
	to the plane and not the plane to avoid fisheye effect
 */
void	calculate_perpendicular(t_data *data)
{
	t_calc_vars *vars;

	vars = data->vars;
	if (vars->side_hit == 0)
		vars->wall_dist = vars->side_X - vars->next_X;
	else
		vars->wall_dist = vars->side_Y - vars->next_Y;
}
