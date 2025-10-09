/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:15:39 by rpedrosa          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/10/09 12:07:33 by rpedrosa         ###   ########.fr       */
=======
/*   Updated: 2025/10/09 11:59:14 by rpedrosa         ###   ########.fr       */
>>>>>>> 603bf8935abc245840a7c57b1e28342a4a53ff5b
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# define TEX_NUMB 4
# define TEXTURE_W 64
# define TEXTURE_H 64
# define SCREENWIDTH 1080
# define SCREENHEIGHT 720
# define CNTLS_NUMB 6

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

typedef struct s_point
{
	int	y;
	int	x;
}	t_point;

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
	int		gun_txt_idx;
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

typedef struct s_data
{
	char		**worldmap;
	void		*mlx;
	void		*win;
	double		pos_x;
	double		pos_y;
	double		plane_x;
	double		plane_y;
	double		dir_vec_x;
	double		dir_vec_y;
	double		curr_time;
	double		old_time;
	double		delta_time;
	int			f_rgb[3];
	int			c_rgb[3];
	bool		controls[CNTLS_NUMB];
	t_calc_vars	*vars;
	t_draw_calc	*draw;
}	t_data;
/*============================================================================#
#                                 Functions                                   #
#============================================================================*/

//inicializacion
void	data_ini(char *file, t_data *data);
void	ini_texture(t_data *data);
char	get_player(t_data *data);
void	get_dir_vars(t_data *data, char p_dir);

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

//key_press_utils
void	press_5(t_data *data, double rot);
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
int		check_text(char **map, t_data **data, int size);
int		check_rgb(char *str, t_data **data);
int		valid_rgb(char **map, t_data **data, int check, int size);
int		map_size(char *file);
int		valid_file(char *file);
int		map_check(char *file, t_data **data);
char	**mapcpy(char **map);
int		fill(t_data *data);
char	**mapcpy(char **map);
void	parse_exit(t_data *data);
t_point	get_point(char **map, char c);
int		extension_finder(char *file);
void	free_map(char **map);
void	cpy_file(char ***map, char *file, int size);
void	set_text(char **map, t_data **data, int y, int x);
void	f_rgb_set(char *file, t_data **data, int x);
void	c_rgb_set(char *file, t_data **data, int x);
int		check_rgb(char *file, t_data **data);
int		ft_strchrlen(char *s, char c);
void	count_rgb(char **map, t_data **data, int size);
void	check_count(char *str, t_data **data);

#endif
