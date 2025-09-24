/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:15:39 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/09/24 11:35:39 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# define TEX_NUMB 7
# define TEXTURE_W 64
# define TEXTURE_H 64
# define MAPWIDTH 24
# define MAPHEIGHT 24
# define SCREENWIDTH 640
# define SCREENHEIGHT 320
# define CNTLS_NUMB 8

/*============================================================================#
#                                 Libraries                                   #
#============================================================================*/

# include <math.h>
# include <stdint.h>
# include <sys/time.h>
# include <X11/keysym.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <stdbool.h>

/*============================================================================#
#                                 Structs                                     #
#============================================================================*/

typedef struct s_enemy
{
	int					id;
	int					enemy_hp;
	double				pos_x;
	double				pos_y;
	double				distance;
	struct s_enemy		*next;
	struct s_enemy		*prev;
}	t_enemy;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		line_len;
	int		bpp;
	int		endian;
}	t_img;

typedef struct s_draw_calc
{
	int		line_h;
	int		start;
	int		end;
	int		tex_w;
	int		tex_h;
	int		minimap_startx;
	int		minimap_starty;
	int		gun_txt_idx;
	t_img	*minimap;
	t_img	*img_buffer;
	t_img	textures[TEX_NUMB];
}	t_draw_calc;

typedef struct s_calc_vars
{
	double	camera_x;
	double	win_w;
	double	win_h;
	double	ray_dirx;
	double	ray_diry;
	int		mapx;
	int		mapy;
	double	side_x;
	double	side_y;
	double	next_x;
	double	next_y;
	int		dir_stepx;
	int		dir_stepy;
	int		hit;
	int		side_hit;
	double	wall_dist;
	double	wall_x;
	int		texture_x;
}	t_calc_vars;

typedef struct s_enemy_draw
{
	double		sprite_x;
	double		sprite_y;
	double		trans_x;
	double		trans_y;
	double		inv;
	int			sprite_screen_x;
	int			sprite_h;
	int			sprite_w;
	int			draw_start_x;
	int			draw_end_x;
	int			vertical;
	int			texture_x;
	int			texture_y;
	int			y;
	int			d;
	uint32_t	color;
}	t_enemy_draw;

typedef struct s_data
{
	char	**worldMap;
	void	*mlx;
	void	*win;
	double	pos_X;
	double	pos_Y;
	double	plane_X;
	double	plane_Y;
	double	dir_vec_X;
	double	dir_vec_Y;
	double	curr_time;
	double	old_time;
	double	delta_time;
	int		f_rgb[3];
	int		c_rgb[3];
	int		gun_animation;
	int		shoot_flag;
	t_enemy *enemies;
	int		numb_of_enemies;
	double	*buffer_z;
	bool	controls[cntls_numb];
	t_calc_vars *vars;
	t_draw_calc *draw;
}	t_data;
/*============================================================================#
#                                 Functions                                   #
#============================================================================*/

//inicializacion
void	data_ini(char *file, t_data *data);
void	ini_texture(t_data *data);

//inputs
void	handle_inputs(t_data *data);
int		key_release(int keycode, t_data *data);
int		key_press(int keycode, t_data *data);

//calculations
void	raycaster(t_data *data);
void	calculate_ray_dir(t_data *data, int x);
void	calculate_perpendicular(t_data *data);
void	check_walls(t_data *data);
void	calculate_side(t_data *data);
void	calculate_next(t_data *data);
void	calculate_lines(t_data *data);
void	reset_vars(t_data *data);
void	something_hit(t_data *data);

//draw
void	calculate_texture_x(t_data *data, int x);
void	clear_img(t_data *data, int ceiling_color, int floor_color);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	calculate_variables(t_data *data, t_enemy_draw *tmp, t_enemy *current);
void	calculate_more_variables(t_enemy_draw *tmp);
void	calculate_color(t_data *data, t_enemy_draw *tmp);
void	mount_image(t_data *data, t_enemy_draw *tmp);
void	position_n_distance(t_data *data);
void	alloc_enemy_list(t_data *data);
void	enemies_ini(t_data *data);
void	ene_drawing_ini(t_data *data);

//minimap
void	ini_minimap(t_data *data);
void	draw_minimap(t_data *data);

//combat
void	draw_gun(t_data *data);
void	enemies_ini(t_data *data);
int		enemy_hit(t_data *data, int mapx, int mapy);
void	draw_enemies(t_data *data);
void	order_enemies(t_data *data);
void	enemy_count(t_data *data);
void	take_enemy_out(t_data *data, int enemy_dead);

//key_press_utils
void	press_4(t_data *data, double rot);
void	press_3(t_data *data, double movespeed);
void	press_2(t_data *data, double movespeed);
void	press_1(t_data *data, double movespeed);
void	press_0(t_data *data, double movespeed);

//fps
void	fps_counter(t_data *data);

//memory
int		ft_exit(t_data *data);

//parsing
int		skip_spaces(char *str);
int		check_digit(char *str);
int		check_rgb(char *str, t_data **data);
int		valid_rgb(char **map, t_data **data);
int		map_size(char *file);
int		valid_file(char *file);
int		map_check(char *file, t_data **data);
char	**mapcpy(char **map);
int		fill(t_data *data);
char	**mapcpy(char **map);
void	parse_exit(t_data *data);

#endif
