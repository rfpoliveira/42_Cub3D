/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 13:11:02 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/10/09 16:10:26 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

/*dirs: norte: y = -1 / planex = 0.66
			sul:  y = 1 / planeX = -0.66
			este: x = 1 /planey = 0.66
			oeste: x = -1 / planey = -0.66
*/

void get_dir_vars(t_data *data, char p_dir)
{
	if (p_dir == 'N' || p_dir == 'S')
		data->dir_vec_x = 0;
	else if (p_dir == 'E')
		data->dir_vec_x = 1;
	else
		data->dir_vec_x = -1;
	if (p_dir == 'E' || p_dir == 'W')
		data->dir_vec_y = 0;
	else if (p_dir == 'S')
		data->dir_vec_y = 1;
	else
		data->dir_vec_y = -1;
	if (p_dir == 'E' || p_dir == 'W')
		data->plane_x = 0;
	else if (p_dir == 'S')
		data->plane_x = -0.66;
	else
		data->plane_x = 0.66;
	if (p_dir == 'N' || p_dir == 'S')
		data->plane_y = 0;
	else if (p_dir == 'W')
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
