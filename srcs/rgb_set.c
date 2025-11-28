/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 11:36:37 by jpatrici          #+#    #+#             */
/*   Updated: 2025/10/15 13:56:32 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

static int	rgb_parse(char *file)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (file[++i])
		if (file[i] == ',')
			count++;
	if (count != 2)
		return (0);
	return (1);
}

int	f_rgb_set(char *file, t_data **data, int x)
{
	char	*temp;
	char	*num;
	int		i;
	int		n;

	n = -1;
	i = 0;
	if (!rgb_parse(file))
		return (0);
	while (++n < 3 && file[x])
	{
		x += (i != 0) * (file[x] == ',');
		i = ft_strchrlen(&file[x], ',');
		temp = ft_substr(file, x, i);
		num = ft_strtrim(temp, " \t");
		free(temp);
		if (!(*num) || check_digit(num) == -1)
			return (free(num), 0);
		(*data)->f_rgb[n] = ft_atoi(num);
		if ((*data)->f_rgb[n] < 0 || (*data)->f_rgb[n] > 255)
			return (free(num), 0);
		x += i;
		free(num);
	}
	return (1);
}

int	c_rgb_set(char *file, t_data **data, int x)
{
	char	*temp;
	char	*num;
	int		i;
	int		n;

	n = -1;
	i = 0;
	if (!rgb_parse(file))
		return (0);
	while (++n < 3 && file[x])
	{
		x += (i != 0) * (file[x] == ',');
		i = ft_strchrlen(&file[x], ',');
		temp = ft_substr(file, x, i);
		num = ft_strtrim(temp, " \t");
		free(temp);
		if (!(*num) || check_digit(num) == -1)
			return (free(num), 0);
		(*data)->c_rgb[n] = ft_atoi(num);
		if ((*data)->c_rgb[n] < 0 || (*data)->c_rgb[n] > 255)
			return (free(num), 0);
		x += i;
		free(num);
	}
	return (1);
}

int	check_rgb(char *file, t_data **data)
{
	int	x;

	x = -1;
	while (file[++x])
	{
		if (skip_spaces(&file[x]) == -1)
			break ;
		x += skip_spaces(&file[x]);
		if (file[x] == 'F' && file[++x])
		{
			x += skip_spaces(&file[x]);
			if (!f_rgb_set(file, data, x))
				return (0);
		}
		if (file[x] == 'C' && file[++x])
		{
			x += skip_spaces(&file[x]);
			if (!c_rgb_set(file, data, x))
				return (0);
		}
	}
	return (1);
}

int	valid_rgb(char **map, t_data **data, int check, int size)
{
	int	y;
	int	x;

	y = -1;
	count_rgb(map, data, size);
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (skip_spaces(map[y]) != -1)
				x += skip_spaces(map[y]);
			if (!check && (map[y][x] == 'C' || map[y][x] == 'F'))
			{
				if (check_rgb(map[y], data))
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
