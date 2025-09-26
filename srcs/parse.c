/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpatrici <jpatrici@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:05:23 by jpatrici          #+#    #+#             */
/*   Updated: 2025/08/14 15:29:49 by jpatrici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

void	set_text(char **map, t_data **data, int y, int x)
{
	char	*temp;
	static int	n = 0;

	printf("HELLO\n");
	temp = NULL;
	temp = ft_strtrim(&map[y][x], "\t ");
	(*data)->draw->tex_w = 64;
	(*data)->draw->tex_h = 64;
	(*data)->draw->textures[n].img = mlx_xpm_file_to_image((*data)->mlx, temp,
		&(*data)->draw->tex_w, &(*data)->draw->tex_h);
	n++;
	free(temp);
	if (!(*data)->draw->textures[n - 1].img)
		parse_exit(*data);
}

char	**valid_map(char **map)
{
	int	y;
	int	x;
	int	start;

	y = -1;
	start = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (skip_spaces(&map[y][x]) != -1)
				x += skip_spaces(&map[y][x]);
			if (start == -1 && (map[y][x] == 'C' 
				|| map[y][x] == 'F' || map[y][x] == 'S'
				|| map[y][x] == 'N' || map[y][x] == 'W' || map[y][x] == 'E'))
				break ;
			if (start == -1 && map[y][x] == '1')
				start = y;
		}
	}
	if (start == -1)
		return (NULL);
	return (mapcpy(&map[start]));
}

int	char_check(char **map)
{
	int	y;
	int	x;
	int	n;

	y = -1;
	n = 0;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == '1' || map[y][x] == '0' || map[y][x] == 'N'
				|| map[y][x] == 'W' || map[y][x] == 'S' || map[y][x] == 'E'
				|| map[y][x] == ' ' || map[y][x] == '\t')
			{
				if (map[y][x] == 'N')
					n++;
				continue ;
			}
			else
				return (0); 
		}
	}
	return (n == 1);
}

int	map_check(char *file, t_data **data)
{
	int		size;
	char	**map;
	int		i;

	i = -1;
	size = map_size(file);
	map = NULL;
	map = ft_calloc(sizeof(char *), size + 1);
	cpy_file(&map, file, size);
	if (!map)
		return (0);
	while(map[++i])
		printf("file:\t%s\n", map[i]);
	(*data)->worldMap = valid_map(map);
	i = -1;
	while((*data)->worldMap[++i])
		printf("map:\t%s\n", (*data)->worldMap[i]);
	if (!(*data)->worldMap || !char_check((*data)->worldMap) 
		|| !valid_rgb(map, data, 0) || !fill(*data) || !check_text(map, data))
		return (free_map(map), 0);
	printf("rgb\t%d\n", (*data)->f_rgb[0]);
	printf("rgb\t%d\n", (*data)->f_rgb[1]);
	printf("rgb\t%d\n", (*data)->f_rgb[2]);
	printf("rgb\t%d\n", (*data)->c_rgb[0]);
	printf("rgb\t%d\n", (*data)->c_rgb[1]);
	printf("rgb\t%d\n", (*data)->c_rgb[2]);
	printf("NO\t%p\n", (*data)->draw->textures[0].img);
	printf("SO\t%p\n", (*data)->draw->textures[1].img);
	printf("WE\t%p\n", (*data)->draw->textures[2].img);
	printf("EA\t%p\n", (*data)->draw->textures[3].img);
	return (free_map(map), 1);
}