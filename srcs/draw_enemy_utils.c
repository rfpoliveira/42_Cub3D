/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_enemy_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 13:44:49 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/09/24 11:41:27 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

void	calculate_variables(t_data *data, t_enemy_draw *tmp, t_enemy *current)
{
	tmp->sprite_x = (current->pos_x + 0.5) - data->pos_x;
	tmp->sprite_y = (current->pos_y + 0.5) - data->pos_y;
	tmp->inv = 1.0 / (data->plane_x * data->dir_vec_y
			- data->dir_vec_x * data->plane_y);
	tmp->trans_x = tmp->inv * (data->dir_vec_y * tmp->sprite_x
			- data->dir_vec_x * tmp->sprite_y);
	tmp->trans_y = tmp->inv * (-data->plane_y * tmp->sprite_x
			+ data->plane_x * tmp->sprite_y);
	tmp->sprite_screen_x = (int)((SCREENWIDTH / 2)
			* (1 + tmp->trans_x / tmp->trans_y));
	tmp->sprite_h = fabs((int)SCREENHEIGHT / tmp->trans_y);
	data->draw->start = -(tmp->sprite_h) / 2 + SCREENHEIGHT / 2;
	if (data->draw->start < 0)
		data->draw->start = 0;
	data->draw->end = tmp->sprite_h / 2 + SCREENHEIGHT / 2;
	if (data->draw->end >= SCREENHEIGHT)
		data->draw->end = SCREENHEIGHT - 1;
}

void	calculate_more_variables(t_enemy_draw *tmp)
{
	tmp->sprite_w = fabs((int)SCREENHEIGHT / tmp->trans_y);
	tmp->draw_start_x = -(tmp->sprite_w) / 2 + tmp->sprite_screen_x;
	if (tmp->draw_start_x < 0)
		tmp->draw_start_x = 0;
	tmp->draw_end_x = tmp->sprite_w / 2 + tmp->sprite_screen_x;
	if (tmp->draw_end_x >= SCREENWIDTH)
		tmp->draw_end_x = SCREENWIDTH - 1;
	tmp->vertical = tmp->draw_start_x - 1;
}

void	calculate_color(t_data *data, t_enemy_draw *tmp)
{
	tmp->d = tmp->y * 256 - SCREENHEIGHT * 128 + tmp->sprite_h * 128;
	tmp->texture_y = ((tmp->d * data->draw->tex_h) / tmp->sprite_h) / 256;
	tmp->color = *(uint32_t *)(data->draw->textures[4].addr
			+ tmp->texture_y * data->draw->textures[4].line_len
			+ tmp->texture_x * (data->draw->textures[4].bpp / 8));
}

void	mount_image(t_data *data, t_enemy_draw *tmp)
{
	tmp->y = data->draw->start - 1;
	while (++(tmp->y) < data->draw->end)
	{
		calculate_color(data, tmp);
		if (tmp->color != 0xFFFFFF)
			my_mlx_pixel_put(data->draw->img_buffer,
				tmp->vertical, tmp->y, tmp->color);
	}
}
