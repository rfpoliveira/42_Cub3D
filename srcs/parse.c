/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:05:23 by jpatrici          #+#    #+#             */
/*   Updated: 2025/10/09 11:59:54 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

void	set_text(char **map, t_data **data, int y, int x)
{
	char	*temp;
	static int	n = 0;

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
				|| map[y][x] == ' ' || map[y][x] == '\t' || map[y][x] == '2')
			{
				if (map[y][x] == 'N' || map[y][x] == 'W'
				|| map[y][x] == 'S' || map[y][x] == 'E')
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

	size = map_size(file);
	map = NULL;
	map = ft_calloc(sizeof(char *), size + 1);
	fd = open(file, O_RDONLY);
	temp = get_next_line(fd);
	while (temp && y < size - 2)
	{
		free(temp);
		temp = NULL;
		temp = get_next_line(fd);
		map[++y] = ft_strdup(temp);
		map[y][(ft_strlen(map[y]) - 1)] = '\0';
	}
	free(temp);
	(*data)->worldmap = valid_map(map);
	if (!(*data)->worldmap || !char_check((*data)->worldmap) || !valid_rgb(map, data) || !fill(*data))
		return (matrix_free(map), 0);
	return (matrix_free(map), 1);
}
