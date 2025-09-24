/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:10:01 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/09/24 11:40:46 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

int	enemy_hit(t_data *data, int mapx, int mapy)
{
	t_enemy	*current;

	current = data->enemies;
	while (current != NULL)
	{
		if (current->pos_x == mapx
			&& current->pos_y == mapy)
		{
			current->enemy_hp--;
			data->shoot_flag = 1;
			if (current->enemy_hp <= 0)
				return (current->id);
			else
				return (-1);
		}
		current = current->next;
	}
	return (-1);
}

void	pixel_to_img(t_data *data, t_enemy_draw *tmp)
{
	while (++(tmp->vertical) < tmp->draw_end_x)
	{
		tmp->texture_x = (int)(256 * (tmp->vertical - (-(tmp->sprite_w) / 2
						+ tmp->sprite_screen_x))
				* data->draw->tex_w / tmp->sprite_w) / 256;
		if (tmp->trans_y > 0 && tmp->vertical > 0
			&& tmp->vertical < SCREENWIDTH
			&& tmp->trans_y < data->buffer_z[tmp->vertical])
			mount_image(data, tmp);
	}
}

void	draw_enemies(t_data *data)
{
	t_enemy			*current;
	t_enemy_draw	*tmp;

	if (data->numb_of_enemies <= 0)
		return ;
	tmp = data->drawing_vars;
	data->draw->tex_h = 64;
	data->draw->tex_w = 64;
	position_n_distance(data);
	order_enemies(data);
	current = data->enemies;
	while (current != NULL)
	{
		calculate_variables(data, tmp, current);
		calculate_more_variables(tmp);
		pixel_to_img(data, tmp);
		current = current->next;
	}
}
