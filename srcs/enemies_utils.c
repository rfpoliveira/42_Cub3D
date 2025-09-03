/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:14:08 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/06/06 12:24:29 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

void order_enemies(t_data *data)
{
	t_enemy *current;
	t_enemy *prev;
	t_enemy *next;
	int swapped;

	if (data->numb_of_enemies <= 0)
		return ;
 
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = data->enemies;
		prev = NULL;

		while(current->next)
		{
			if (current->distance < current->next->distance)
			{
				next = current->next;
				current->next = next->next;
				next->next = current;
				if (prev == NULL)
					data->enemies = next;
				else
					prev->next = next;
				swapped = 1;
				current = next;
			}
			prev = current;
			current = current->next;
		}
	}
}

void	enemy_count(t_data *data)
{
	int i;
	int	j;
	int count;

	i = -1;
	j = -1;
	count = 0;
	while (++i < mapWidth)
	{
		j = -1;
		while (++j < mapHeight)
		{
			if (data->worldMap[i][j] == 2)
				count++;	
		}
	}
	data->numb_of_enemies = count;
}

void	take_enemy_out(t_data *data, int enemy_dead)
{
	t_enemy *current;
	t_enemy *tmp;

	current = data->enemies;
	tmp = current;
	while(current != NULL)
	{
		if (current->id == enemy_dead)
		{
			tmp->next = current->next;
			data->worldMap[(int)(current->pos_x)][(int)(current->pos_y)] = 0;
			data->numb_of_enemies--;
			if (current == data->enemies)
				data->enemies = data->enemies->next;
			free(current);
			current = NULL;
			return ;
		}
		tmp = current;
		current = current->next;
	}
}