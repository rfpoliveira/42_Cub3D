/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:54:24 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/10/16 17:00:20 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

int	collision_x(t_data *data, double x)
{
	double  old_y;
	double  rad;

	rad = 0.2;
	old_y = data->pos_y;
	if (data->worldmap[(int)(x + rad)][(int)old_y] != '0' || \
data->worldmap[(int)(x - rad)][(int)old_y] != '0' || \
data->worldmap[(int)x][(int)(old_y + rad)] != '0' || \
data->worldmap[(int)x][(int)(old_y - rad)] != '0' || \
data->worldmap[(int)(x + rad)][(int)(old_y - rad)] != '0' || \
data->worldmap[(int)(x - rad)][(int)(old_y + rad)] != '0' || \
data->worldmap[(int)(x + rad)][(int)(old_y - rad)] != '0' || \
data->worldmap[(int)(x - rad)][(int)(old_y - rad)] != '0')
		return (1);
	return (0);
}

int collision_y(t_data *data, double y)
{
	double  old_x;
	double  rad;

	rad = 0.2;
	old_x = data->pos_x;
	if (data->worldmap[(int)(old_x + rad)][(int)y] != '0' || \
data->worldmap[(int)(old_x - rad)][(int)y] != '0' || \
data->worldmap[(int)old_x][(int)(y + rad)] != '0' || \
data->worldmap[(int)old_x][(int)(y - rad)] != '0' || \
data->worldmap[(int)(old_x + rad)][(int)(y + rad)] != '0' || \
data->worldmap[(int)(old_x - rad)][(int)(y + rad)] != '0' || \
data->worldmap[(int)(old_x + rad)][(int)(y - rad)] != '0' || \
data->worldmap[(int)(old_x - rad)][(int)(y - rad)] != '0')
		return (1);
	return (0);
}