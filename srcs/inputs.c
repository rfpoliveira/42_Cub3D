/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:27:31 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/05/29 14:45:27 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

/**
	@brief changes the control bools letting us know a key is being pressed
 */
int	key_press(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		ft_exit(data);
	else if (keycode == XK_w || keycode == XK_Up)
		data->controls[0] = true;
	else if (keycode == XK_s || keycode == XK_Down)
		data->controls[1] = true;
	else if (keycode == XK_a)
		data->controls[2] = true;
	else if (keycode == XK_d)
		data->controls[3] = true;
	else if (keycode == XK_Left)
		data->controls[4] = true;
	else if (keycode == XK_Right)
		data->controls[5] = true;
	else if (keycode == XK_m)
	{
		if (data->controls[6] == true)
			data->controls[6] = false;
		else
			data->controls[6] = true;
	}
	else if (keycode == XK_space)
	{
		data->controls[7] = true;
		data->draw->gun_txt_idx = 6;
	}
	return (0);
}

/**
	@brief changes the control bools letting us 
	know a key as stopped being pressed
 */
int	key_release(int keycode, t_data *data)
{
	if (keycode == XK_w || keycode == XK_Up)
		data->controls[0] = false;
	else if (keycode == XK_s || keycode == XK_Down)
		data->controls[1] = false;
	else if (keycode == XK_a)
		data->controls[2] = false;
	else if (keycode == XK_d)
		data->controls[3] = false;
	else if (keycode == XK_Left)
		data->controls[4] = false;
	else if (keycode == XK_Right)
		data->controls[5] = false;
	else if (keycode == XK_space)
	{
		data->controls[7] = false;
		data->gun_animation = 0;
		data->shoot_flag = 0;
	}
	return (0);
}


/**
	@brief calculates movespeed and rotspeed to make the movement smoother
	then checks what controls are being pressed and moves in the intended way
	manipulating the direction vectors.
 */
void	handle_inputs(t_data *data)
{
	double movespeed = 5.0 * data->delta_time;
	double rotspeed = 3.0 * data->delta_time;
	double	old_Dir;
	double	old_PlaneX;
	
	if (data->controls[0])
	{
		if (data->worldMap[(int)(data->pos_X + data->dir_vec_X * movespeed)][(int)data->pos_Y] == 0
			&& data->worldMap[(int)((data->pos_X + data->dir_vec_X * movespeed) + 0.1)][(int)(data->pos_Y + 0.1)] == 0
			&& data->worldMap[(int)((data->pos_X + data->dir_vec_X * movespeed) - 0.1)][(int)(data->pos_Y + 0.1)] == 0)
			data->pos_X += data->dir_vec_X * movespeed;
		if (data->worldMap[(int)(data->pos_X)][(int)(data->pos_Y + data->dir_vec_Y * movespeed)] == 0
			&& data->worldMap[(int)((data->pos_X) + 0.1)][(int)((data->pos_Y + data->dir_vec_Y * movespeed) + 0.1)] == 0
			&& data->worldMap[(int)((data->pos_X) - 0.1)][(int)((data->pos_Y + data->dir_vec_Y * movespeed) - 0.1)] == 0)
			data->pos_Y += data->dir_vec_Y * movespeed;
	}
	if (data->controls[1])
	{
		if (data->worldMap[(int)(data->pos_X - data->dir_vec_X * movespeed)][(int)data->pos_Y] == 0
			&& data->worldMap[(int)((data->pos_X - data->dir_vec_X * movespeed) + 0.1)][(int)(data->pos_Y + 0.1)] == 0
			&& data->worldMap[(int)((data->pos_X - data->dir_vec_X * movespeed) - 0.1)][(int)(data->pos_Y - 0.1)] == 0)
			data->pos_X += -data->dir_vec_X * movespeed;
		if (data->worldMap[(int)(data->pos_X)][(int)(data->pos_Y - data->dir_vec_Y * movespeed)] == 0
			&& data->worldMap[(int)((data->pos_X) + 0.1)][(int)((data->pos_Y - data->dir_vec_Y * movespeed) + 0.1)] == 0
			&& data->worldMap[(int)((data->pos_X) - 0.1)][(int)((data->pos_Y - data->dir_vec_Y * movespeed) - 0.1)] == 0)
			data->pos_Y += -data->dir_vec_Y * movespeed;
	}
	if (data->controls[2])
	{
		if (data->worldMap[(int)(data->pos_X + (-data->dir_vec_Y) * movespeed)][(int)data->pos_Y] == 0
			&& data->worldMap[(int)((data->pos_X + (-data->dir_vec_Y) * movespeed) + 0.1)][(int)(data->pos_Y + 0.1)] == 0
			&& data->worldMap[(int)((data->pos_X + (-data->dir_vec_Y) * movespeed) - 0.1)][(int)(data->pos_Y - 0.1)] == 0)
			data->pos_X += (-data->dir_vec_Y) * movespeed;
		if (data->worldMap[(int)(data->pos_X)][(int)(data->pos_Y + data->dir_vec_X * movespeed)] == 0
			&& data->worldMap[(int)((data->pos_X) + 0.1)][(int)((data->pos_Y + data->dir_vec_X * movespeed) + 0.1)] == 0
			&& data->worldMap[(int)((data->pos_X) - 0.1)][(int)((data->pos_Y + data->dir_vec_X * movespeed) - 0.1)] == 0)
			data->pos_Y += data->dir_vec_X * movespeed;
	}
	if (data->controls[3])
	{
		if (data->worldMap[(int)(data->pos_X + data->dir_vec_Y * movespeed)][(int)data->pos_Y] == 0
			&& data->worldMap[(int)((data->pos_X + data->dir_vec_Y * movespeed) + 0.1)][(int)(data->pos_Y + 0.1)] == 0
			&& data->worldMap[(int)((data->pos_X + data->dir_vec_Y * movespeed) - 0.1)][(int)(data->pos_Y - 0.1)] == 0)
			data->pos_X += data->dir_vec_Y * movespeed;
		if (data->worldMap[(int)(data->pos_X)][(int)(data->pos_Y + (-data->dir_vec_Y) * movespeed)] == 0
			&& data->worldMap[(int)((data->pos_X) + 0.1)][(int)((data->pos_Y + (-data->dir_vec_Y) * movespeed) + 0.1)] == 0
			&& data->worldMap[(int)((data->pos_X) - 0.1)][(int)((data->pos_Y + (-data->dir_vec_Y) * movespeed) - 0.1)] == 0)
			data->pos_Y += -(data->dir_vec_X) * movespeed;
	}
	if(data->controls[4])
	{
		old_Dir = data->dir_vec_X;
		data->dir_vec_X = data->dir_vec_X * cos(rotspeed) - data->dir_vec_Y * sin(rotspeed);
		data->dir_vec_Y = old_Dir * sin(rotspeed) + data->dir_vec_Y * cos(rotspeed);
		old_PlaneX = data->plane_X;
		data->plane_X = data->plane_X * cos(rotspeed) - data->plane_Y * sin(rotspeed);
		data->plane_Y = old_PlaneX * sin(rotspeed) + data->plane_Y * cos(rotspeed);
	}
	if(data->controls[5])
	{
		old_Dir = data->dir_vec_X;
		data->dir_vec_X = data->dir_vec_X * cos(-rotspeed) - data->dir_vec_Y * sin(-rotspeed);
		data->dir_vec_Y = old_Dir * sin(-rotspeed) + data->dir_vec_Y * cos(-rotspeed);
		old_PlaneX = data->plane_X;
		data->plane_X = data->plane_X * cos(-rotspeed) - data->plane_Y * sin(-rotspeed);
		data->plane_Y = old_PlaneX * sin(-rotspeed) + data->plane_Y * cos(rotspeed);
	}
}
