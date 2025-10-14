/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 13:11:02 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/10/14 16:05:04 by rpedrosa         ###   ########.fr       */
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

			trocar:
			oeste: y = -1 / planex = 0.66
			este:  y = 1 / planeX = -0.66
			sul: x = 1 /planey = 0.66
			norte: x = -1 / planey = -0.66
			
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
