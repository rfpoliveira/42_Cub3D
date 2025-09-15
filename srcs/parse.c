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
#include <fcntl.h>

int	extension_finder(char *file)
{
	if (ft_strchr(file, '/') && ft_strlen(ft_strrchr(file, '/')) == 5)
		return (0);
	return (1);
}

int	map_size(char *file)
{
	int		fd;
	int		size;
	char	*temp;

	size = 0;
	fd = open(file, O_RDONLY);
	temp = get_next_line(fd);
	if (fd == -1)
		return (0);
	while (temp)
	{
		free(temp);
		temp = NULL;
		temp = get_next_line(fd);
		size++;
	}
	return (size);
}

int	valid_file(char *file)
{
	int		size;
	int		map_len;

	map_len = 0;
	size = ft_strlen(file);
	map_len = map_size(file);
	if (!extension_finder(file) || size == 4
		|| (!ft_strnstr(&file[size - 4], ".cub", size)
			&& file[size + 1] != '\0'))
		return (0);	
	printf("here %d\n", map_len);
	return (map_len > 8);
}

int	skip_spaces(char *line)
{
	int	x;

	x = 0;
	while (line[x] == ' ' && line[x] == '\t')
		x++;
	if (line[x] == '\n' || line[x] == '\0')
		return (0);
	else
		return (x);
}

int	check_digit(char *file)
{
	int	x;

	x = 0;
	while (file[x])
		if (file[x] >= '0' && file[x] <= '9')
			x++;
	if (file[x] != ' ' || file[x] != '\t'
		|| file[x] != '\n' || file[x] != ',')
		return (0);
	return (1);
}

int	check_rgb(char *file)
{
	int	x;
	int	n;

	x = -1;
	n = 0;
	while (file[++x])
	{
		if (!skip_spaces(file))
			return (0);
		x = skip_spaces(&file[x]);
		if (file[x] == 'C' || file[x] == 'F')
			++x;
		if (!skip_spaces(&file[x]))
			return (0);
		if (!check_digit(&file[x]))
			return (0);
		if (file[x] == ',')
			n++;
	}
	if (n > 3)
		return (0);
	return (1);
}

int	valid_rgb(char **map)
{
	int	y;
	int	x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (skip_spaces(map[y]))
				x = skip_spaces(map[y]);
			else
				break ;
			if (map[y][x] == 'C' || map[y][x] == 'F')
				return (check_rgb(map[y]));
			else
				break ;
		}
	}
	return (1);
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
			if (skip_spaces(map[y]))
				x = skip_spaces(map[y]);
			if (start == -1 && map[y][x] == '1')
				start = y;
			if (map[y][x] == '1' || map[y][x] == '0'
				|| map[y][x] == 'N')
				continue ;
			else if (start != -1)
				return (NULL);
		}
	}
	printf("start: %d\n", start);
	printf("map: %s", map[start]);
	return (mapcpy(&map[start]));
}
char **mapcpy(char **map)
{
	int		y;
	char	**temp;

	y = 0;
	while (map[y])
		++y;
	temp = malloc(sizeof(char *) * (y + 1));
	if (!temp)
		return (NULL);
	temp[y] = NULL;
	y = -1;
	while (map[++y])
		temp[y] = ft_strdup(map[y]);	
	return (temp);
}

int	map_check(char *file, t_data **data)
{
	int		fd;
	int		y;
	int		size;
	char	*temp;
	char	**map;

	y = -1;
	size = map_size(file);
	map = NULL;
	map = ft_calloc(sizeof(char *), size + 1);
	fd = open(file, O_RDONLY);
	temp = get_next_line(fd);
	while (temp)
	{
		free(temp);
		temp = NULL;
		temp = get_next_line(fd);
		map[++y] = ft_strdup(temp);
	}
	if (!valid_rgb(map))
		return (0);
	(*data)->worldMap = valid_map(map);
	int	i;
	i = -1;
	while (map[++i + 5])
		printf("mapa: %s", map[i + 5]);
	if (!(*data)->worldMap)
		return (0);
	return (1);
}
