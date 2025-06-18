/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:14:08 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/06/04 11:19:21 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

void order_enemies(t_data *data)
{
	t_enemy *current;
	t_enemy *tmp;

	current = data->enemies;
	tmp = NULL;
	while(current->next)
	{
		if (current->distance < current->next->distance)
		{
			tmp = current;
			current = current->next;
			tmp->next = current->next;
			current->prev = tmp->prev;
			tmp->prev = current;
			if (current->next)
				current->next->prev = tmp;
			current->next = tmp;
		}
		else
			current = current->next;
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