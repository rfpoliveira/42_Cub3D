/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 13:11:02 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/09/04 18:01:04 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

/**
	@brief check if we just hitted a wall or a enemy
    if it was an enemy call the functions to take out 
    hp or the enemy if he died
 */

void	something_hit(t_data *data)
{
	int				id_hit;
	t_calc_vars		*vars;

	vars = data->vars;
	if (data->worldmap[vars->mapx][vars->mapy] == 1)
		vars->hit = 1;
	if (data->controls[7] && data->worldmap[vars->mapx][vars->mapy] == 2
	&& (vars->camera_x > -0.1 && vars->camera_x < 0.1)
	&& data->shoot_flag == 0)
	{
		id_hit = enemy_hit(data, vars->mapx, vars->mapy);
		if (id_hit != -1)
			take_enemy_out(data, id_hit);
	}
}

void	ene_drawing_ini(t_data *data)
{
	data->drawing_vars = malloc(sizeof(t_enemy_draw));
	data->drawing_vars->sprite_x = 0;
	data->drawing_vars->sprite_y = 0;
	data->drawing_vars->trans_x = 0;
	data->drawing_vars->trans_y = 0;
	data->drawing_vars->inv = 0;
	data->drawing_vars->sprite_screen_x = 0;
	data->drawing_vars->sprite_h = 0;
	data->drawing_vars->sprite_w = 0;
	data->drawing_vars->draw_start_x = 0;
	data->drawing_vars->draw_end_x = 0;
	data->drawing_vars->vertical = 0;
	data->drawing_vars->texture_x = 0;
	data->drawing_vars->texture_y = 0;
	data->drawing_vars->y = 0;
	data->drawing_vars->d = 0;
	data->drawing_vars->color = 0;
}
