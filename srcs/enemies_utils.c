/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:14:08 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/09/24 11:56:00 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

void	enemies_swap(t_data *dt, t_enemy **curr, t_enemy **prv, t_enemy **nxt)
{
	*nxt = (*curr)->next;
	(*curr)->next = (*nxt)->next;
	(*nxt)->next = *curr;
	if (*prv == NULL)
		dt->enemies = *nxt;
	else
		(*prv)->next = *nxt;
	*curr = *nxt;
}

void	order_enemies(t_data *data)
{
	t_enemy	*curr;
	t_enemy	*prev;
	t_enemy	*next;
	int		swapped;

	if (data->numb_of_enemies <= 0)
		return ;
	next = NULL;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		curr = data->enemies;
		prev = NULL;
		while (curr->next)
		{
			if (curr->distance < curr->next->distance)
			{
				enemies_swap(data, &curr, &prev, &next);
				swapped = 1;
			}
			prev = curr;
			curr = curr->next;
		}
	}
}

void	enemy_count(t_data *data)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	j = -1;
	count = 0;
	while (data->worldMap[++i])
	{
		j = -1;
		while (data->worldMap[i][++j])
		{
			if (data->worldMap[i][j] == 2)
				count++;
		}
	}
	data->numb_of_enemies = count;
}

void	take_enemy_out(t_data *data, int enemy_dead)
{
	t_enemy	*current;
	t_enemy	*tmp;

	current = data->enemies;
	tmp = current;
	while (current != NULL)
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
