/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:27:31 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/10/15 14:48:03 by rpedrosa         ###   ########.fr       */
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
	else if (keycode == XK_space)
	{
		data->controls[6] = true;
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
		data->controls[6] = false;
		data->gun_animation = 0;
		data->shoot_flag = 0;
	}
	return (0);
}

void	press_4(t_data *data, double rot)
{
	double	old_dir;
	double	old_planex;

	old_dir = data->dir_vec_x;
	data->dir_vec_x = data->dir_vec_x * cos(-rot)
		- data->dir_vec_y * sin(-rot);
	data->dir_vec_y = old_dir * sin(-rot)
		+ data->dir_vec_y * cos(-rot);
	old_planex = data->plane_x;
	data->plane_x = data->plane_x * cos(-rot) - data->plane_y * sin(-rot);
	data->plane_y = old_planex * sin(-rot) + data->plane_y * cos(rot);
}

/**
	@brief calculates movespeed and rotspeed to make the movement smoother
	then checks what controls are being pressed and moves in the intended way
	manipulating the direction vectors.
 */
void	handle_inputs(t_data *data)
{
	double	movespeed;
	double	rotspeed;

	movespeed = 5.0 * data->delta_time;
	rotspeed = 3.0 * data->delta_time;
	if (data->controls[0])
		press_0(data, movespeed);
	if (data->controls[1])
		press_1(data, movespeed);
	if (data->controls[2])
		press_2(data, movespeed);
	if (data->controls[3])
		press_3(data, movespeed);
	if (data->controls[4])
		press_4(data, rotspeed);
	if (data->controls[5])
		press_5(data, rotspeed);
}
