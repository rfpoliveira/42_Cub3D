/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:31:45 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/09/24 11:34:52 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

void	free_lst(t_enemy *enemies)
{
	t_enemy	*tmp;

	tmp = NULL;
	while (enemies->next && enemies)
	{
		tmp = enemies->next;
		free(enemies);
		enemies = tmp;
	}
	free(enemies);
}
/**
	@brief can free all the memory and exit the program 
	anywhere it is called
 */

void	ft_free_util(t_data *data)
{
	if (data->buffer_z)
		free(data->buffer_z);
	if (data->draw->img_buffer)
		free(data->draw->img_buffer);
	if (data->draw->minimap)
		free(data->draw->minimap);
	if (data->vars)
		free(data->vars);
	if (data->draw)
		free(data->draw);
	if (data->drawing_vars)
		free(data->drawing_vars);
	if (data)
		free(data);
}

int	ft_exit(t_data *data)
{
	int	i;

	i = -1;
	if (data->draw->minimap->img)
		mlx_destroy_image(data->mlx, data->draw->minimap->img);
	while (++i < TEX_NUMB)
		if (data->draw->textures[i].img)
			mlx_destroy_image(data->mlx, data->draw->textures[i].img);
	if (data->draw->img_buffer->img)
		mlx_destroy_image(data->mlx, data->draw->img_buffer->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	if (data->numb_of_enemies > 0)
		free_lst(data->enemies);
	i = -1;
	if (data->worldmap)
	{
		while (++i < MAPWIDTH)
			free(data->worldmap[i]);
		free(data->worldmap);
	}
	ft_free_util(data);
	exit(0);
}
