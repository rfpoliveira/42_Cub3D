/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 13:11:02 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/10/14 19:01:10 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

void	rgb_to_hex(t_data *data)
{
	data->c_hex = (data->c_rgb[0] << 16) | (data->c_rgb[1] << 8) | data->c_rgb[2];
	data->f_hex = (data->f_rgb[0] << 16) | (data->f_rgb[1] << 8) | data->f_rgb[2];
}

/*dirs: norte: y = -1 / planex = 0.66
			sul:  y = 1 / planeX = -0.66
			este: x = 1 /planey = 0.66
			oeste: x = -1 / planey = -0.66
*/

void get_dir_vars(t_data *data, char p_dir)
{
	if (p_dir == 'W' || p_dir == 'E')
		data->dir_vec_x = 0;
	else if (p_dir == 'S')
		data->dir_vec_x = 1;
	else
		data->dir_vec_x = -1;
	if (p_dir == 'N' || p_dir == 'S')
		data->dir_vec_y = 0;
	else if (p_dir == 'W')
		data->dir_vec_y = 1;
	else
		data->dir_vec_y = -1;
	if (p_dir == 'S' || p_dir == 'N')
		data->plane_x = 0;
	else if (p_dir == 'W')
		data->plane_x = -0.66;
	else
		data->plane_x = 0.66;
	if (p_dir == 'W' || p_dir == 'E')
		data->plane_y = 0;
	else if (p_dir == 'N')
		data->plane_y = -0.66;
	else
		data->plane_y = 0.66;
}

char	get_player(t_data *data)
{
	t_point player;
	char	dir;
	
	player = get_point(data->worldmap, 'N');
	dir = 'N';
	if (player.x == -1)
	{
		player = get_point(data->worldmap, 'S');
		dir = 'S';
	}
	if (player.x == -1)
	{
		player = get_point(data->worldmap, 'W');
		dir = 'W';
	}
	if (player.x == -1)
	{
		player = get_point(data->worldmap, 'E');
		dir = 'E';
	}
	data->pos_x = player.y + 0.5;
	data->pos_y = player.x + 0.5;
	data->worldmap[player.y][player.x] = '0';
	return (dir);
}

/**
	@brief check if we just hitted a wall or a enemy
    if it was an enemy call the functions to take out 
    hp or the enemy if he died
 */

void	something_hit(t_data *data)
{
	int				id_hit;
	t_calc_vars		*vars;

	id_hit = 0;
	vars = data->vars;
	if (data->worldmap[vars->mapx][vars->mapy] == '1')
		vars->hit = 1;
	if (data->controls[6] && data->worldmap[vars->mapx][vars->mapy] == '2'
	&& (vars->camera_x > -0.1 && vars->camera_x < 0.1)
	&& data->shoot_flag == 0)
	{
		id_hit = enemy_hit(data, vars->mapx, vars->mapy);
		if (id_hit != -1)
			take_enemy_out(data, id_hit);
	}
}

void	ene_drawing_ini(t_data *data)
{
	data->drawing_vars = malloc(sizeof(t_enemy_draw));
	data->drawing_vars->sprite_x = 0;
	data->drawing_vars->sprite_y = 0;
	data->drawing_vars->trans_x = 0;
	data->drawing_vars->trans_y = 0;
	data->drawing_vars->inv = 0;
	data->drawing_vars->sprite_screen_x = 0;
	data->drawing_vars->sprite_h = 0;
	data->drawing_vars->sprite_w = 0;
	data->drawing_vars->draw_start_x = 0;
	data->drawing_vars->draw_end_x = 0;
	data->drawing_vars->vertical = 0;
	data->drawing_vars->texture_x = 0;
	data->drawing_vars->texture_y = 0;
	data->drawing_vars->y = 0;
	data->drawing_vars->d = 0;
	data->drawing_vars->color = 0;
}
