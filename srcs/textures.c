/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:12:08 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/06/04 11:33:07 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

/**
	@brief selects the texture we want to put on the wall depending on
	geographical orientation then get the color of the exact pixel we want
	from that texture and puts in the buffer
 */
static void	texture_selector_walls(t_data *data, double step, double pos_tex, int x)
{
	int y;
	int texture_idx;
	uint32_t color;
	int	tex_Y;
	
	y = data->draw->start - 1;
	while (++y < data->draw->end)
	{
		tex_Y = (int)pos_tex & ((int)texture_h - 1);
 		if (data->worldMap[data->vars->mapX][data->vars->mapY] != 1)
			return ;
		if (data->vars->side_hit == 0 && data->vars->dir_stepX == -1)
			texture_idx = 0;
		else if (data->vars->side_hit == 0 && data->vars->dir_stepX == 1)
			texture_idx = 1;
		else if (data->vars->side_hit == 1 && data->vars->dir_stepY == -1)
			texture_idx = 2;
		else if (data->vars->side_hit == 1 && data->vars->dir_stepY == 1)
			texture_idx = 3;
		color = *(uint32_t*)(data->draw->textures[texture_idx].addr +
			tex_Y * data->draw->textures[texture_idx].line_len +
			data->vars->texture_X * (data->draw->textures[texture_idx].bpp / 8));
		pos_tex += step;
		my_mlx_pixel_put(data->draw->img_buffer, x, y, color);
	}
}
/**
	@brief calculates the correct piece of texture we need to input in place with the
	right height considering distance and the window
 */
void	calculate_texture_X(t_data *data, int x)
{
	double	step;
	double	pos_tex;

	if (data->vars->side_hit == 0)
		data->vars->wall_X = data->pos_Y + data->vars->wall_dist * data->vars->ray_DirY;
	else
		data->vars->wall_X = data->pos_X + data->vars->wall_dist * data->vars->ray_DirX;
	data->vars->wall_X -= floor(data->vars->wall_X);
	data->vars->texture_X = (int)(data->vars->wall_X * (double)texture_w);
	if (data->vars->side_hit == 0 && data->vars->ray_DirX > 0)
		data->vars->texture_X = texture_w - data->vars->texture_X - 1;
	if (data->vars->side_hit == 1 && data->vars->ray_DirY < 0)
		data->vars->texture_X = texture_w - data->vars->texture_X - 1;
	step = 1.0 * texture_h / data->draw->line_h;
	pos_tex = (data->draw->start - data->vars->win_h / 2 + data->draw->line_h / 2) * step;
	texture_selector_walls(data, step, pos_tex, x);
}

/**
	@brief inicializes all the textures to images in memory
 */
static void	texture_to_image(t_data *data)
{
	data->draw->textures[0].img = mlx_xpm_file_to_image(data->mlx, "textures/bluestone.xpm", &data->draw->tex_w, &data->draw->tex_h);
	if (!(data->draw->textures[0].img))
		ft_exit(data);
	data->draw->textures[1].img = mlx_xpm_file_to_image(data->mlx, "textures/colorstone.xpm", &data->draw->tex_w, &data->draw->tex_h);
	if (!(data->draw->textures[1].img))
		ft_exit(data);
	data->draw->textures[2].img = mlx_xpm_file_to_image(data->mlx, "textures/greystone.xpm", &data->draw->tex_w, &data->draw->tex_h);
	if (!(data->draw->textures[2].img))
		ft_exit(data);
	data->draw->textures[3].img = mlx_xpm_file_to_image(data->mlx, "textures/mossy.xpm", &data->draw->tex_w, &data->draw->tex_h);
	if (!(data->draw->textures[3].img))
		ft_exit(data);
	data->draw->textures[4].img = mlx_xpm_file_to_image(data->mlx, "textures/demon.xpm", &data->draw->tex_w, &data->draw->tex_h);
	if (!(data->draw->textures[4].img))
		ft_exit(data);
	data->draw->textures[5].img = mlx_xpm_file_to_image(data->mlx, "textures/gun.xpm", &data->draw->tex_w, &data->draw->tex_h);
	if (!(data->draw->textures[5].img))
		ft_exit(data);	
	data->draw->textures[6].img = mlx_xpm_file_to_image(data->mlx, "textures/shoot_gun.xpm", &data->draw->tex_w, &data->draw->tex_h);
	if (!(data->draw->textures[6].img))
		ft_exit(data);	
}

/**
	@brief inicializes all the textures to images 
	and gets the information we need to get the pixels we want to
	draw
 */
void	ini_texture(t_data *data)
{
	int	i;
	t_draw_calc *img;

	i = -1;
	img = data->draw;
	texture_to_image(data);
	while(++i < (int)tex_numb)
	{
		img->textures[i].addr = mlx_get_data_addr(
			img->textures[i].img, 
			&img->textures[i].bpp, 
			&img->textures[i].line_len, 
			&img->textures[i].endian);
		if (!(img->textures[i].addr))
			ft_exit(data);
	}
}