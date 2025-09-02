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

void	floodfill(char **map, t_point size, int col, int row)
{
	if (col < 0 || row < 0 || col > size.y || row > size.x)
		return ;
	if (map[col][row] == '2' || map[col][row] == '1')
		return ;
	map[col][row] = '2';
	floodfill(map, size, col + 1, row);
	floodfill(map, size, col - 1, row);
	floodfill(map, size, col, row + 1);
	floodfill(map, size, col, row - 1);
}

int	fill(char **map)
{
	char	**temp;
	
	temp = NULL;
	temp = mapcpy(map); 

}
