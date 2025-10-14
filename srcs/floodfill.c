/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:26:20 by jpatrici          #+#    #+#             */
/*   Updated: 2025/10/14 14:38:00 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

t_point	get_point(char **map, char c)
{
	t_point	p;
	int		y;
	int		x;

	y = -1;
	p.y = y;
	while (map[++y])
	{
		x = -1;
		p.x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == c)
			{
				p.y = y;
				p.x = x;
				return (p);
			}
		}
	}
	if (c == '\0' && map[y - 1][x] == '\0')
	{
		p.x = x - 1;
		p.y = y;
	}
	return (p);
}

int	col_len(char **map, int x)
{
	int	i;
	int	j;
	t_point	p;

	p = get_point(map, '\0');
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j] && j != x)
		{
			if (x > p.x && i == p.y - 1)
				return (i);	
		}
	}
	return (i);
}

void	floodfill(char **map, int col, int row)
{
	t_point	size;

	size.x = ft_strlen(map[col]);
	size.y = col_len(map, size.x);
	if (col < 0 || row < 0 || col > size.y -1|| row > size.x -1)
		return ;
	if (map[col][row] == '3' || map[col][row] == '1'
		|| map[col][row] == '\t' || map[col][row] == ' ')
		return ;
	map[col][row] = '3';
	floodfill(map, col + 1, row);
	floodfill(map, col - 1, row);
	floodfill(map, col, row + 1);
	floodfill(map, col, row - 1);
}

int	check_fill(char **map)
{
	int	x;
	int	y;

	y = -1;
	while (map[++y])
	{
	x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == '3')
			{
				if (ft_strchrlen(map[y], map[y][x]) > ft_strlen(map[y - 1])
					|| ft_strchrlen(map[y], map[y][x]) > ft_strlen(map[y + 1]))
					return (0);
				else if (
					(map[y - 1][x] != '1' && map[y - 1][x] != '3')
					|| (map[y + 1][x] != '1' && map[y + 1][x] != '3')
					||(map[y][x - 1] != '1' && map[y][x - 1] != '3')
					|| (map[y][x + 1] != '1' && map[y][x + 1] != '3'))
					return (0);
			}
		}
	}
	return (matrix_free(map), 1);
}

int	fill(t_data *data)
{
	t_point	start;
	char	**temp;

	start = get_point(data->worldmap, 'N');
	if (start.x == -1)
		start = get_point(data->worldmap, 'S');
	if (start.x == -1)
		start = get_point(data->worldmap, 'E');
	if (start.x == -1)
		start = get_point(data->worldmap, 'W');
	if (start.x == -1)
		parse_exit(data);
	temp = NULL;
	temp = mapcpy(data->worldmap);
	if (!temp)
		parse_exit(data);
	floodfill(temp, start.y, start.x);
	if (check_fill(temp))
		return (1);
	return (0);
}
