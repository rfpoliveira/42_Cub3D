/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:32:17 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/05/29 14:45:44 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

void	draw_gun(t_data *data)
{
	int i;
	int j;
	t_img gun;
	uint32_t color;

	i = -1;
	j = -1;

 	if (data->controls[7])
	{
		data->gun_animation++;
		if (data->draw->gun_txt_idx == 6)
		{
			if (data->gun_animation >= 30)
			{
				data->draw->gun_txt_idx = 5;
				data->gun_animation = 0;
			}
		}
	}
	else if (!data->controls[7] && data->draw->gun_txt_idx == 6)
	{
		data->gun_animation++;
		if (data->gun_animation >= 30)
		{
			data->draw->gun_txt_idx = 5;
			data->gun_animation = 0;
		}
	}
	gun = data->draw->textures[data->draw->gun_txt_idx];
	while (++i < 256)
	{
		j = -1;
		while (++j < 256)
		{
		color = *(uint32_t*)(gun.addr + (j * gun.line_len + i * (gun.bpp / 8)));
		if (color != 0xFFFFFF)
			my_mlx_pixel_put(data->draw->img_buffer, i + (screenWidth / 2 - 128), j + (screenHeight - 256), color); 
		}
	}
}

/**
	@brief now we calculate the height of the wall considering the window
	calculates the beggining and ending pixels as well to use later
 */
void	calculate_lines(t_data *data)
{
	t_draw_calc *draw;
	t_calc_vars *vars;
	
	draw = data->draw;
	vars = data->vars;
	draw->line_h = (int)(vars->win_h / vars->wall_dist);
	draw->start = -draw->line_h / 2 + vars->win_h / 2;
	if (draw->start < 0)
		draw->start = 0;
	draw->end = draw->line_h / 2 + vars->win_h / 2;
	if (draw->end >= vars->win_h)
		draw->end = vars->win_h - 1;
}

/**
	@brief this function copies the correct pixels from the textures to the buffer
 */
void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;

	 if (x < 0 || x >= (int)screenWidth || y < 0 || y >= (int)screenHeight)
        return;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

/**
	@brief clears every pixel making it the default color
 */

void	clear_img(t_data *data, int ceiling_color, int floor_color)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while (++i < data->vars->win_w)
	{
		j = -1;
		while (++j < data->vars->win_h / 2)
			my_mlx_pixel_put(data->draw->img_buffer, i, j, ceiling_color);
		while (++j < data->vars->win_h)
			my_mlx_pixel_put(data->draw->img_buffer, i, j, floor_color);
	}
}