/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:10:01 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/06/04 17:21:59 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

static void	position_n_distance(t_data *data)
{
	int i;
	int	j;
	t_enemy *tmp;

	i = -1;
	j = -1;
	tmp = data->enemies;
	while (++i < mapWidth)
	{
		j = -1;
		while (++j < mapHeight)
		{
			if (data->worldMap[i][j] == 2)
			{
				tmp->pos_x = (double)i + 0.5;
				tmp->pos_y = (double)j + 0.5;
				tmp->distance = 
					sqrt(pow((data->pos_X - tmp->pos_x), 2) +
                	pow(data->pos_Y - tmp->pos_y, 2));
				tmp = tmp->next;
			}	
		}
	} 
}

static void	alloc_enemy_list(t_data *data)
{
	int i;
	t_enemy *new;
	t_enemy *current;
	
	i = -1;
	current = NULL;
	new = NULL;
	data->enemies = NULL;
	while (++i < data->numb_of_enemies)
	{
		new = malloc(sizeof(t_enemy));
		new->id = i;
		new->enemy_hp = 4;
		new->next = NULL;
		new->prev = NULL;
		if (current == NULL)
		{
			current = new;
			data->enemies = new;
		}
		else
		{
			current->next = new;
			new->prev = current;
			current = current->next;
		}
	}
}

void	enemies_ini(t_data *data)
{
	data->draw->gun_txt_idx = 5;
	data->gun_animation = 0;
	data->shoot_flag = 0;
	enemy_count(data);
	alloc_enemy_list(data);
	position_n_distance(data);
	order_enemies(data);
}

int	enemy_hit(t_data *data, int mapX, int mapY)
{
	t_enemy *current;

	current = data->enemies;
	while (current->next != NULL)
	{
		if (current->pos_x == mapX 
			&& current->pos_y == mapY)
		{
			current->enemy_hp--;
			data->shoot_flag = 1;
			if (current->enemy_hp == 0)
				return  (0);
			else
				return (1);
			current = current->next;
		}
	}
	return (1);
}

void draw_enemies(t_data *data)
{
	t_enemy *current;
	double	sprite_X;
	double	sprite_Y;
	double	trans_x;
	double	trans_y;
	double	inv;
	int sprite_screen_x;
	int sprite_h;
	int sprite_w;
	int draw_start_x;
	int draw_end_x;
	int vertical;
	int texture_x;
	int texture_y;
	int y;
	int d;
	uint32_t color;
	
	data->draw->tex_h = 64;
	data->draw->tex_w = 64;
	current = data->enemies; 
	while (current != NULL)
	{
		sprite_X = (current->pos_x + 0.5) - data->pos_X;
		sprite_Y = (current->pos_y + 0.5) - data->pos_Y;
		inv = 1.0 / (data->plane_X * data->dir_vec_Y - data->dir_vec_X * data->plane_Y);
		trans_x = inv * (data->dir_vec_Y * sprite_X - data->dir_vec_X * sprite_Y);
		trans_y = inv * (-data->plane_Y * sprite_X + data->plane_X * sprite_Y);
		sprite_screen_x = (int)((screenWidth / 2) * (1 + trans_x / trans_y));
		sprite_h = fabs((int)screenHeight / trans_y);
		data->draw->start = -sprite_h / 2 + screenHeight / 2;
		if(data->draw->start < 0) 
			data->draw->start = 0;
		data->draw->end = sprite_h / 2 + screenHeight / 2;
		if (data->draw->end >= screenHeight) 
			data->draw->end = screenHeight - 1;
		sprite_w = fabs((int)screenHeight / trans_y);
		draw_start_x = -sprite_w / 2 + sprite_screen_x;
      	if(draw_start_x < 0) 
			draw_start_x = 0;
		draw_end_x = sprite_w / 2 + sprite_screen_x;
		if (draw_end_x >= screenWidth)
			draw_end_x = screenWidth - 1;
		vertical = draw_start_x - 1;
		while (++vertical < draw_end_x)
		{
			texture_x = (int)(256 * (vertical - (-sprite_w / 2 + sprite_screen_x) * data->draw->tex_w / sprite_w) / 256);
			if (trans_y > 0 && vertical > 0 && vertical < screenWidth && trans_y < data->buffer_z[vertical])
			{
				y = data->draw->start - 1;
				while(++y < data->draw->end)
				{
					d = y * 256 - screenHeight * 128 + sprite_h * 128;
					texture_y = ((d * data->draw->tex_h) / sprite_h) / 256;
					color = *(uint32_t*)(data->draw->textures[4].addr +
                        texture_y * data->draw->textures[4].line_len +
                        texture_x * (data->draw->textures[4].bpp / 8));
					if (color != 0xFFFFFF)
						my_mlx_pixel_put(data->draw->img_buffer, vertical, y, color);
				}
			}
		}
		current = current->next;
	}
}
