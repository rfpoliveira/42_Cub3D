
#ifndef CUBE_H
# define CUBE_H

# define tex_numb 7
# define texture_w 64
# define texture_h 64
# define mapWidth 24
# define mapHeight 24
# define screenWidth 640
# define screenHeight 320
# define cntls_numb 8
# define minimap_player_size (minimap_h / 20)
# define minimap_w (screenWidth / 8)
# define minimap_h (screenHeight / 8 * (screenWidth / screenHeight))

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
	int	id;
	int	enemy_hp;
	double pos_x;
	double pos_y;
	double distance;
	struct s_enemy *next;
	struct s_enemy *prev;
}	t_enemy;

typedef	struct	s_img
{
	void	*img;
	char	*addr;
	int		line_len;
	int		bpp;
	int		endian;
}	t_img;

typedef struct s_draw_calc
{
	int	line_h;
	int start;
	int	end;
	int tex_w;
	int tex_h;
	int	minimap_startx;
	int minimap_starty;
	int gun_txt_idx;
	t_img *minimap;
	t_img *img_buffer;
	t_img textures[tex_numb];
}	t_draw_calc;

typedef struct s_calc_vars
{
	double	camera_X;
	double	win_w;
	double	win_h;
	double	ray_DirX;
	double	ray_DirY;
	int		mapX;
	int		mapY;
	double	side_X;
	double	side_Y;
	double	next_X;
	double	next_Y;
	int		dir_stepX;
	int		dir_stepY;
	int		hit;
	int		side_hit;
	double	wall_dist;
	double	wall_X;
	int	texture_X;
}	t_calc_vars;

typedef struct s_data
{
	int **worldMap;
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
	int gun_animation;
	int	shoot_flag;
	t_enemy *enemies;
	int numb_of_enemies;
	double	*buffer_z;
	bool	controls[cntls_numb];
	t_calc_vars *vars;
	t_draw_calc *draw;
}	t_data;
/*============================================================================#
#                                 Functions                                   #
#============================================================================*/

//inicializacion
void	data_ini(t_data *data);
void	ini_texture(t_data *data);

//inputs
void	handle_inputs(t_data *data);
int	key_release(int keycode, t_data *data);
int	key_press(int keycode, t_data *data);

//calculations
void	raycaster(t_data *data);
void	calculate_ray_Dir(t_data *data, int x);
void	calculate_perpendicular(t_data *data);
void	check_walls(t_data *data);
void	calculate_side(t_data *data);
void	calculate_next(t_data *data);
void	calculate_lines(t_data *data);
void	reset_vars(t_data *data);

//draw
void	calculate_texture_X(t_data *data, int x);
void	clear_img(t_data *data, int ceiling_color, int floor_color);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

//minimap
void	ini_minimap(t_data *data);
void	draw_minimap(t_data *data);

//combat
void	draw_gun(t_data *data);
void	enemies_ini(t_data *data);
int		enemy_hit(t_data *data, int mapX, int mapY);
void	draw_enemies(t_data *data);
void	order_enemies(t_data *data);
void	enemy_count(t_data *data);
void	take_enemy_out(t_data *data, int enemy_dead);

//fps
void	fps_counter(t_data *data);

//memory
int		ft_exit(t_data *data);



#endif
