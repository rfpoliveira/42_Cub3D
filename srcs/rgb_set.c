/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpatrici <jpatrici@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 11:36:37 by jpatrici          #+#    #+#             */
/*   Updated: 2025/09/24 13:58:35 by jpatrici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

void	f_rgb_set(char *file, t_data **data, int x)
{
	char *temp;

	temp = ft_substr(file, x, check_digit(&file[x]));
	(*data)->f_rgb[0] = ft_atoi(temp);
	free(temp);
	x += check_digit(&file[x]);
	x += skip_spaces(&file[x]);
	if (file[x] == ',')
		x++;
	x += skip_spaces(&file[x]);
	temp = ft_substr(file, x, check_digit(&file[x]));
	(*data)->f_rgb[1] = ft_atoi(temp);
	free(temp);
	x += check_digit(&file[x]);
	x += skip_spaces(&file[x]);
	if (file[x] == ',')
		x++;
	x += skip_spaces(&file[x]);
	temp = ft_substr(file, x, check_digit(&file[x]));
	(*data)->f_rgb[2] = ft_atoi(temp);
	free(temp);
}

void	c_rgb_set(char *file, t_data **data, int x)
{
	char *temp;

	temp = ft_substr(file, x, check_digit(&file[x]));
	(*data)->c_rgb[0] = ft_atoi(temp);
	free(temp);
	x += check_digit(&file[x]);
	x += skip_spaces(&file[x]);
	if (file[x] == ',')
		x++;
	x += skip_spaces(&file[x]);
	temp = ft_substr(file, x, check_digit(&file[x]));
	(*data)->c_rgb[1] = ft_atoi(temp);
	free(temp);
	x += check_digit(&file[x]);
	x += skip_spaces(&file[x]);
	if (file[x] == ',')
		x++;
	x += skip_spaces(&file[x]);
	temp = ft_substr(file, x, check_digit(&file[x]));
	(*data)->c_rgb[2] = ft_atoi(temp);
	free(temp);
}

int	check_rgb(char *file, t_data **data)
{
	int	x;
	int	n;

	x = -1;
	n = 0;
	while (file[++x])
	{
		if (skip_spaces(&file[x]) == -1)
			break ;
		x += skip_spaces(&file[x]);
		if (file[x] == 'F' && file[++x])
		{
			x += skip_spaces(&file[x]);
			f_rgb_set(file, data, x);
		}
		if (file[x] == 'C' && file[++x])
		{
			x += skip_spaces(&file[x]);
			c_rgb_set(file, data, x);
		}
		if (file[x] == ',')
			n++;
	}
	return (n < 4);
}

int	valid_rgb(char **map, t_data **data, int check)
{
	int	y;
	int	x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (skip_spaces(map[y]) != -1)
				x += skip_spaces(map[y]);
			if (!check && (map[y][x] == 'C' || map[y][x] == 'F'))
			{
				check_rgb(map[y], data);
				check++;
				break ;
			}
			else if (check && (map[y][x] == 'C' || map[y][x] == 'F'))
				return (check_rgb(map[y], data));
			else
				break ;
		}
	}
	return (0);
}

int	ft_strchrlen(char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}
