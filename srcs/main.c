/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:22:01 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/06/04 11:18:28 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

/**
	@brief this is the loop that produces everyframe
	
	clear_img clear the screen ready to put the new frame in
	handle_inputs will check if any keys being pressed
	raycaster will generate the correct frame
	we put it in the window
	then calculate and display the fps
 */
int	game_loop(t_data *data)
{
		clear_img(data, 0x00FFDD, 0x808080);
		handle_inputs(data);
		raycaster(data);
		draw_enemies(data);
		draw_gun(data);
		mlx_put_image_to_window(data->mlx, data->win, data->draw->img_buffer->img, 0, 0);
		if (data->controls[6] == true)
			draw_minimap(data);
		fps_counter(data);
		return (0);
}

int main (void)
{
	t_data *data;
	
	data = malloc(sizeof(t_data));
	if (!data)
		ft_exit(data);
	data_ini(data);
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 3, 1L << 1, key_release, data);
	mlx_hook(data->win, 17, 1L << 17, ft_exit, data);
	mlx_loop_hook(data->mlx, &game_loop, data);
	mlx_loop(data->mlx);
}

