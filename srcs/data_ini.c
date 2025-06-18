/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_ini.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:08:51 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/06/04 16:15:15 by rpedrosa         ###   ########.fr       */
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
	while (++i < (int)cntls_numb)
		data->controls[i] = false;
}

/** 
	@brief inializes a couple variables we need to the raycasting algorithm

	pos X and Y are the inicial positions
	curr and old time are to calculate fps
	win_w and h are the windowns dimensions
	delta_time is the time of the last frame to make sure the movement 
	is independent of the fps
	dir_vec_X and Y are the direction vectors
	plane X and Y is the pov (screen)
	side_X and Y are TODO
*/

/*direcoes: norte: y = -1 / planex = 0.66
			sul:  y = 1 / planeX = -0.66
			este: x = 1 /planey = 0.66
			oeste: x = -1 / planey = -0.66
*/
static void	vars_ini(t_data *data)
{
	data->pos_X = 22;
	data->pos_Y = 12;
	data->curr_time = 0;
	data->old_time = 0;
	data->vars->win_w = (int)screenWidth;
	data->vars->win_h = (int)screenHeight;
	data->delta_time = 0;
	data->dir_vec_X = 0;
	data->dir_vec_Y = -1;
	data->plane_X = -0.66;
	data->plane_Y = 0;
	data->vars->side_X = 0;
	data->vars->side_Y = 0;
}

/**
	@brief inicializes some variables we need to draw the frames

	the img_buffer will store every pixel we get from the raycasting
	end and start are the pixel we start and end to form the line with the raycasting
	line_h is the height of that line
	tex_h and tex_w are the dimensions in pixel of the textures
 */
static void	draw_ini(t_data *data)
{
	data->draw->img_buffer->img = mlx_new_image(data->mlx, data->vars->win_w, data->vars->win_h);
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
	data->draw->minimap_startx = (int)screenWidth / 20;
	data->draw->minimap_starty = (int)screenHeight - (int)screenHeight / 20 - (int)minimap_h;
}
static void	window_ini(t_data *data)
{
	data->win = mlx_new_window(data->mlx, (int)screenWidth, (int)screenHeight, "Cub3d da Nasa");
	if (!(data->win))
		ft_exit(data);
}
/**
	@brief inicicializes the main data struct will helper functions
 */

void	data_ini(t_data *data)
{
	int worldMap[mapWidth][mapHeight]=
	{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,2,0,0,0,0,0,0,0,1},
	{1,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,0,0,0,2,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	data->worldMap = malloc(sizeof(int *) * mapWidth);
	for (int i = 0; i < mapWidth; i++) 
	{
    	data->worldMap[i] = malloc(sizeof(int) * mapHeight);
    	for (int j = 0; j < mapHeight; j++) {
       		data->worldMap[i][j] = worldMap[i][j];
    }
	}
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
	data->buffer_z = malloc(sizeof(double) * screenWidth);
	vars_ini(data);
	controls_ini(data);
	draw_ini(data);
	ini_texture(data);
	ini_minimap(data);
	enemies_ini(data);
}
