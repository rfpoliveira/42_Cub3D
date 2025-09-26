/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpatrici <jpatrici@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 11:46:30 by jpatrici          #+#    #+#             */
/*   Updated: 2025/09/24 11:55:44 by jpatrici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"


int	extension_finder(char *file)
{
	if (ft_strchr(file, '/') && ft_strlen(ft_strrchr(file, '/')) == 5)
		return (0);
	return (1);
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
	return (map_len > 8);
}

void	count_text(char *txt, char **map, t_data **data)
{
	int	i;
	int	y;
	int	x;

	y = -1;
	i = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == 'N' && map[y][x + 1] == 'O')
				txt[++i] = 'N';
			if (map[y][x] == 'S' && map[y][x + 1] == 'O')
				txt[++i] = 'S';
			if (map[y][x] == 'W' && map[y][x + 1] == 'E')
				txt[++i] = 'W';
			if (map[y][x] == 'E' && map[y][x + 1] == 'A')
				txt[++i] = 'E';
		}
	}
	check_count(txt, data);
}

int	check_text(char **map, t_data **data, int size)
{
	int	y;
	int	x;
	char	*count;

	y = -1;
	count = ft_calloc(sizeof(char), size);
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == 'N' && map[y][x + 1] == 'O')
				set_text(map, data, y, x + 2);
			if (map[y][x] == 'S' && map[y][x + 1] == 'O')
				set_text(map, data, y, x + 2);
			if (map[y][x] == 'W' && map[y][x + 1] == 'E')
				set_text(map, data, y, x + 2);
			if (map[y][x] == 'E' && map[y][x + 1] == 'A')
				set_text(map, data, y, x + 2);
		}
	}
	count_text(count, map, data);
	return (1);
}

void	free_map(char **map)
{
	int	i;

	i = -1;
	while (map[++i])
			free(map[i]);
		free(map);
}

void	cpy_file(char ***map, char *file, int size)
{
	int		fd;
	int		y;
	char	*temp;

	y = -1;
	fd = open(file, O_RDONLY);
	temp = get_next_line(fd);
	(*map)[++y] = ft_strdup(temp);
	(*map)[y][(ft_strlen((*map)[y]) - 1)] = '\0';
	while (temp && y < size - 1)
	{
		free(temp);
		temp = NULL;
		temp = get_next_line(fd);
		(*map)[++y] = ft_strdup(temp);
		(*map)[y][(ft_strlen((*map)[y]) - 1)] = '\0';
	}
	free(temp);
	close(fd);
}
