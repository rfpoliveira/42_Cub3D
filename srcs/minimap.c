/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:02:37 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/09/04 17:46:09 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

void	ini_minimap(t_data *data)
{
	t_img *map;

	data->draw->minimap = malloc(sizeof(t_img));
	if (!data->draw->minimap)
		ft_exit(data);
	map = data->draw->minimap;
	map->img = mlx_new_image(data->mlx, data->minimap_w, data->minimap_h);
	map->addr = 
		mlx_get_data_addr(map->img, &map->bpp, &map->line_len, &map->endian);
	if (!(map->addr))
		ft_exit(data);
}

void	draw_player(t_data *data)
{
	int px;
	int py;
	double scale;
	int	i;
	int	j;
	
	i = -1;
	j = -1;
	scale = (double)MAPWIDTH / (double)data->minimap_w;
	px = (int)(floor(data->pos_x / scale));
	py = (int)(floor(data->pos_y / scale));
	while (++i < data->minimap_h / 20)
	{
		j = -1;
		while (++j < data->minimap_h / 20)
			my_mlx_pixel_put(data->draw->minimap, px + i, py + j, 0x00FF00);
	}
	
}

void	put_minimap_pixel(t_data *data, int i, int j, double scale)
{
	if (i * scale < MAPWIDTH && j * scale < MAPHEIGHT)
	{
		if (data->worldmap[(int)(floor(i * scale))][(int)floor(j * scale)] == 0)
			my_mlx_pixel_put(data->draw->minimap, i, j, 0xFFFFFF);
		else if (data->worldmap[(int)(floor(i * scale))]
		[(int)floor(j * scale)] == 2)
			my_mlx_pixel_put(data->draw->minimap, i, j, 0xFF0000);
		else
			my_mlx_pixel_put(data->draw->minimap, i, j, 0x000000);
	}
}

void	draw_minimap(t_data *data)
{
	int i;
	int j;
	double scale;

	scale = (double)MAPWIDTH / (double)data->minimap_w;
	i = -1;
	j = -1;
	while (++i < data->minimap_w)
	{
		j = -1;
		while (++j < data->minimap_h)
			put_minimap_pixel(data, i, j, scale);
	}
	draw_player(data);
	mlx_put_image_to_window(data->mlx, data->win, data->draw->minimap->img, 
		data->draw->minimap_startx, data->draw->minimap_starty);
}
