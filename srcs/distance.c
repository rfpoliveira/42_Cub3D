/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:19:56 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/09/05 14:01:53 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

void	put_values(t_data *data, int i, int j, t_enemy *tmp)
{
	tmp->pos_x = i;
	tmp->pos_y = j;
	tmp->distance = pow((data->pos_x - tmp->pos_x), 2)
		+ pow((data->pos_y - tmp->pos_y), 2);
}

void	position_n_distance(t_data *data)
{
	int		i;
	int		j;
	t_enemy	*tmp;

	if (data->numb_of_enemies <= 0)
		return ;
	tmp = NULL;
	i = -1;
	j = -1;
	tmp = data->enemies;
	while (++i < MAPWIDTH)
	{
		j = -1;
		while (++j < MAPHEIGHT)
		{
			if (data->worldmap[i][j] == 2)
			{
				put_values(data, i, j, tmp);
				tmp = tmp->next;
				if (!tmp)
					return ;
			}
		}
	}
}

void	alloc_enemy_list(t_data *data)
{
	int		i;
	t_enemy	*new;
	t_enemy	*current;

	i = 0;
	if (data->numb_of_enemies > 0)
	{
		current = malloc(sizeof(t_enemy));
		current->id = i;
		current->enemy_hp = 4;
		current->next = NULL;
		current->prev = NULL;
		data->enemies = current;
	}
	while (++i < data->numb_of_enemies)
	{
		new = malloc(sizeof(t_enemy));
		new->id = i;
		new->enemy_hp = 4;
		new->next = NULL;
		new->prev = current;
		current->next = new;
		current = current->next;
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
