/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 16:16:52 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/09/24 11:42:59 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

void	press_0(t_data *data, double movespeed)
{
	int	worldMapx;
	int	worldMapy;

	worldMapx = (int)(data->pos_x + data->dir_vec_x * movespeed);
	worldMapy = (int)(data->pos_y + data->dir_vec_y * movespeed);
	if (data->worldMap[(int)(worldMapx)][(int)data->pos_y] == 0 &&
		data->worldMap[(int)(worldMapx + 0.1)][(int)(data->pos_y + 0.1)] == 0 &&
		data->worldMap[(int)(worldMapx - 0.1)][(int)(data->pos_y + 0.1)] == 0)
		data->pos_x += data->dir_vec_x * movespeed;
	if (data->worldMap[(int)(data->pos_x)][(int)worldMapy] == 0 &&
		data->worldMap[(int)(data->pos_x + 0.1)][(int)(worldMapy + 0.1)] == 0 &&
		data->worldMap[(int)(data->pos_x - 0.1)][(int)(worldMapy - 0.1)] == 0)
		data->pos_y += data->dir_vec_y * movespeed;
}

void	press_1(t_data *data, double movespeed)
{
	int	worldMapx;
	int	worldMapy;

	worldMapx = (int)(data->pos_x - data->dir_vec_x * movespeed);
	worldMapy = (int)(data->pos_y - data->dir_vec_y * movespeed);
	if (data->worldMap[(int)(worldMapx)][(int)data->pos_y] == 0 &&
	data->worldMap[(int)(worldMapx + 0.1)][(int)(data->pos_y + 0.1)] == 0 &&
	data->worldMap[(int)(worldMapx - 0.1)][(int)(data->pos_y - 0.1)] == 0)
		data->pos_x += -data->dir_vec_x * movespeed;
	if (data->worldMap[(int)(data->pos_x)][(int)(worldMapy)] == 0 &&
	data->worldMap[(int)((data->pos_x) + 0.1)][(int)(worldMapy + 0.1)] == 0 &&
	data->worldMap[(int)((data->pos_x) - 0.1)][(int)(worldMapy - 0.1)] == 0)
		data->pos_y += -data->dir_vec_y * movespeed;
}

void	press_2(t_data *data, double movespeed)
{
	int	worldMapx;
	int	worldMapy;

	worldMapx = (int)(data->pos_x + (-data->dir_vec_y) * movespeed);
	worldMapy = (int)(data->pos_y + data->dir_vec_x * movespeed);
	if (data->worldMap[(int)(worldMapx)][(int)data->pos_y] == 0 &&
	data->worldMap[(int)(worldMapx + 0.1)][(int)(data->pos_y + 0.1)] == 0 &&
	data->worldMap[(int)(worldMapx - 0.1)][(int)(data->pos_y - 0.1)] == 0)
		data->pos_x += (-data->dir_vec_y) * movespeed;
	if (data->worldMap[(int)(data->pos_x)][(int)(worldMapy)] == 0 &&
	data->worldMap[(int)((data->pos_x) + 0.1)][(int)(worldMapy + 0.1)] == 0 &&
	data->worldMap[(int)((data->pos_x) - 0.1)][(int)(worldMapy - 0.1)] == 0)
		data->pos_y += data->dir_vec_x * movespeed;
}

void	press_3(t_data *data, double movespeed)
{
	int	worldMapx;
	int	worldMapy;

	worldMapx = (int)(data->pos_x + data->dir_vec_y * movespeed);
	worldMapy = (int)(data->pos_y + (-data->dir_vec_y) * movespeed);
	if (data->worldMap[(int)(worldMapx)][(int)data->pos_y] == 0 &&
	data->worldMap[(int)(worldMapx + 0.1)][(int)(data->pos_y + 0.1)] == 0 &&
	data->worldMap[(int)(worldMapx - 0.1)][(int)(data->pos_y - 0.1)] == 0)
		data->pos_x += data->dir_vec_y * movespeed;
	if (data->worldMap[(int)(data->pos_x)][(int)(worldMapy)] == 0 &&
	data->worldMap[(int)(data->pos_x + 0.1)][(int)(worldMapy + 0.1)] == 0 &&
	data->worldMap[(int)((data->pos_x - 0.1))][(int)(worldMapy - 0.1)] == 0)
		data->pos_y += -(data->dir_vec_x) * movespeed;
}

void	press_4(t_data *data, double rot)
{
	double	old_dir;
	double	old_planex;

	old_dir = data->dir_vec_x;
	data->dir_vec_x = data->dir_vec_x * cos(rot) - data->dir_vec_y * sin(rot);
	data->dir_vec_y = old_dir * sin(rot) + data->dir_vec_y * cos(rot);
	old_planex = data->plane_x;
	data->plane_x = data->plane_x * cos(rot) - data->plane_y * sin(rot);
	data->plane_y = old_planex * sin(rot) + data->plane_y * cos(rot);
}
