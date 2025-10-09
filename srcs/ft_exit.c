/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:31:45 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/10/09 16:35:06 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

/**
	@brief can free all the memory and exit the program 
	anywhere it is called
 */

void	ft_free_util(t_data *data)
{
	int i;

	i = -1;
	while(++i < TEX_NUMB)
		mlx_destroy_image(data->mlx, data->draw->textures[i].img);
	if (data->draw->img_buffer->img)
		mlx_destroy_image(data->mlx, data->draw->img_buffer->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}

int	ft_exit(t_data *data)
{
	if (data->worldmap)
		matrix_free(data->worldmap);
	ft_free_util(data);
	if (data->draw->img_buffer)
		free(data->draw->img_buffer);
	if (data->vars)
		free(data->vars);
	if (data->draw)
		free(data->draw);
	if (data)
		free(data);
	exit(0);
}
