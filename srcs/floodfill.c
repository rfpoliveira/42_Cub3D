/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpatrici <jpatrici@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:26:20 by jpatrici          #+#    #+#             */
/*   Updated: 2025/09/01 18:02:46 by jpatrici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

typedef struct s_point
{
	int	y;
	int	x;
}	t_point;

t_point	get_point(char **map, char c)
{
	t_point	p;
	int		y;
	int		x;

	y = -1;
	p.y	 = y;
	while (map[++y])
	{
		x = -1;
		p.x = -1;
		while(map[y][++x])
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
	if (col < 0 || row < 0 || col > size.y || row > size.x)
		return ;
	if (map[col][row] == '2' || map[col][row] == '1')
		return ;
	map[col][row] = '2';
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
			if (map[y][x] == '2' && (map[y - 1][x] != '1' || map[y][x - 1] != '1'
				|| map[y + 1][x] != '1' || map[y][x + 1] != '1'
				|| map[y - 1][x] != '2' || map[y][x - 1] != '2'
				|| map[y + 1][x] != '2' || map[y][x + 1] != '2'
				|| map[y - 1][x] != 'N' || map[y][x - 1] != 'N'
				|| map[y + 1][x] != 'N' || map[y][x + 1] != 'N'))
				return (0);
	}
	return (1);
}

int	fill(t_data *data)
{
	t_point	start;
	char	**temp;
	
	start = get_point(data->worldMap, 'N');
	temp = NULL;
	temp = mapcpy(data->worldMap);
	if (!temp)
		ft_exit(data);
	floodfill(temp, start.y, start.x);
	int	i = -1;
	while (temp[++i])
		printf("%s\n", temp[i]);
	check_fill(temp);
	return (0);
}
