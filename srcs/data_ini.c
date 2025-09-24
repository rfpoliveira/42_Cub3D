/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_ini.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:08:51 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/09/24 11:33:13 by rpedrosa         ###   ########.fr       */
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
/*direcoes: norte: y = -1 / planex = 0.66
			sul:  y = 1 / planeX = -0.66
			este: x = 1 /planey = 0.66
			oeste: x = -1 / planey = -0.66
*/
static void	vars_ini(t_data *data)
{
	data->pos_x = 22;
	data->pos_y = 12;
	data->curr_time = 0;
	data->old_time = 0;
	data->vars->win_w = (int)SCREENWIDTH;
	data->vars->win_h = (int)SCREENHEIGHT;
	data->delta_time = 0;
	data->dir_vec_x = -1;
	data->dir_vec_y = 0;
	data->plane_x = 0;
	data->plane_y = 0.66;
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
	data->minimap_w = (SCREENWIDTH / 8);
	data->minimap_h = (SCREENHEIGHT / 8 * (SCREENWIDTH / SCREENHEIGHT));
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
	data->draw->minimap_startx = (int)SCREENWIDTH / 20;
	data->draw->minimap_starty = (int)SCREENHEIGHT - (int)SCREENHEIGHT
		/ 20 - data->minimap_h;
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
	if (!map_check(file, &data))
		parse_exit(data);
	/*int	i;*/
	/*i = -1;*/
	/*while (data->worldMap[++i])*/
	/*	printf("mapa: %s", data->worldMap[i]);*/
	exit(0);
	data->mlx = mlx_init();
	if (!(data->mlx))
		ft_exit(data);
	window_ini(data);
	data->vars = malloc(sizeof(t_calc_vars));
	data->draw = malloc(sizeof(t_draw_calc));
	if (!data->vars || !data->draw)
		ft_exit(data);
	data->draw->img_buffer = malloc(sizeof(t_img));
	if (!data->draw->img_buffer)
		ft_exit(data);
	data->buffer_z = malloc(sizeof(double) * SCREENWIDTH);
	vars_ini(data);
	controls_ini(data);
	draw_ini(data);
	ini_texture(data);
	ini_minimap(data);
	enemies_ini(data);
	ene_drawing_ini(data);
}
