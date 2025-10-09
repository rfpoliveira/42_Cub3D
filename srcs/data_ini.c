/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_ini.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:08:51 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/10/09 16:47:22 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

/**
	@brief inicializes all the control to the default (not being pressed)
 */
static void	controls_ini(t_data *data)
{
	int	i;

	i = -1;
	while (++i < (int)CNTLS_NUMB)
		data->controls[i] = false;
}

/** 
	@brief inializes a couple variables we need to the raycasting algorithm

	pos X and Y are the inicial positions
	curr and old time are to calculate fps
	win_w and h are the windowns dimensions
	delta_time is the time of the last frame to make sure the movement 
	is independent of the fps
	dir_vec_x and Y are the direction vectors
	plane X and Y is the pov (screen)
	side_x and Y are TODO
*/

static void	vars_ini(t_data *data)
{
	char p_dir;

	p_dir = get_player(data);
	data->curr_time = 0;
	data->old_time = 0;
	data->vars->win_w = (int)SCREENWIDTH;
	data->vars->win_h = (int)SCREENHEIGHT;
	data->delta_time = 0;
	get_dir_vars(data, p_dir);
	data->vars->side_x = 0;
	data->vars->side_y = 0;
}

/**
	@brief inicializes some variables we need to draw the frames

	the img_buffer will store every pixel we get from the raycasting
	end and start are the pixel we start and end to form the line with
	the raycasting line_h is the height of that line
	tex_h and tex_w are the dimensions in pixel of the textures
 */
static void	draw_ini(t_data *data)
{
	data->draw->img_buffer->img = mlx_new_image(data->mlx,
	data->vars->win_w, data->vars->win_h);
	if (!(data->draw->img_buffer->img))
		ft_exit(data);
	data->draw->img_buffer->addr = mlx_get_data_addr(
		data->draw->img_buffer->img,
		&data->draw->img_buffer->bpp,
		&data->draw->img_buffer->line_len,
		&data->draw->img_buffer->endian);
	if (!(data->draw->img_buffer->addr))
		ft_exit(data);
	data->draw->end = 0;
	data->draw->start = 0;
	data->draw->line_h = 0;
	data->draw->tex_h = 64;
	data->draw->tex_w = 64;
}
static void	window_ini(t_data *data)
{
	data->win = mlx_new_window(data->mlx, 
							(int)SCREENWIDTH, 
							(int)SCREENHEIGHT, 
							"Cub3d da Nasa");
	if (!(data->win))
		ft_exit(data);
}
/**
	@brief inicicializes the main data struct will helper functions
 */

void	data_ini(char *file, t_data *data)
{
	data->mlx = mlx_init();
	if (!(data->mlx))
		ft_exit(data);
	data->draw = ft_calloc(sizeof(t_draw_calc), 1);
	if (!map_check(file, &data))
		parse_exit(data);
	window_ini(data);
	data->vars = malloc(sizeof(t_calc_vars));
	if (!data->vars || !data->draw)
		ft_exit(data);
	data->draw->img_buffer = malloc(sizeof(t_img));
	if (!data->draw->img_buffer)
		ft_exit(data);
	vars_ini(data);
	controls_ini(data);
	draw_ini(data);
	ini_texture(data);
}
