/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:31:45 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/05/29 11:55:38 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

/**
	@brief can free all the memory and exit the program 
	anywhere it is called
 */

int	ft_exit(t_data *data)
{
	int i;

	i = -1;
	while(++i < 4)
		mlx_destroy_image(data->mlx, data->draw->textures[i].img);
	if (data->draw->img_buffer->img)
		mlx_destroy_image(data->mlx, data->draw->img_buffer->img);
	if (data->draw->minimap)
		
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	i = -1;
	if (data->worldMap)
	{
		while (++i < mapWidth)
			free(data->worldMap[i]);
		free(data->worldMap);
	}
	if (data->draw->img_buffer)
		free(data->draw->img_buffer);
	if (data->draw->minimap)
		free(data->draw->minimap);
	if (data->enemies)
		free(data->enemies);
	if (data->vars)
		free(data->vars);
	if (data->draw)
		free(data->draw);
	if (data)
		free(data);
	exit(0);
}
