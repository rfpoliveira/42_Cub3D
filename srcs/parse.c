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
		printf("%c\n", file[x]);
			x += skip_spaces(&file[x]);
			if (check_digit(&file[x]) != -1)
			{
		printf("%c\n", file[x]);
				(*data)->f_rgb[0] = ft_atoi(ft_substr(file, x, check_digit(&file[x])));
				x += check_digit(&file[x]);
				x += skip_spaces(&file[x]);
		printf("%c\n", file[x]);
				if (file[x] == ',')
					x++;
		printf("%c\n", file[x]);
				x += skip_spaces(&file[x]);
				(*data)->f_rgb[1] = ft_atoi(ft_substr(file, x, check_digit(&file[x])));
				x += check_digit(&file[x]);
				x += skip_spaces(&file[x]);
				if (file[x] == ',')
					x++;
				x += skip_spaces(&file[x]);
				printf("%s\n", &file[x]);
				(*data)->f_rgb[2] = ft_atoi(ft_substr(file, x, check_digit(&file[x])));
			}
		}
		if (file[x] == ',')
			n++;
		/*if (skip_spaces(&file[x]) == -1 || !check_digit(&file[x]))*/
		/*	return (printf("here aaaaaaa\n"), 0);*/

	}
	printf("rgb[0] -\t%d\n", (*data)->f_rgb[0]);
	printf("rgb[1] -\t%d\n", (*data)->f_rgb[1]);
	printf("rgb[2] -\t%d\n", (*data)->f_rgb[2]);
	if (n > 3)
		return (0);
	return (1);
}

int	valid_rgb(char **map, t_data **data)
{
	int	y;
	int	x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			/*printf("here\n");*/
			if (skip_spaces(map[y]) != -1)
				x = skip_spaces(map[y]);
			/*else*/
			/*	break ;*/
			printf("x:\t%d\nline:\t%s\n", x, map[y]);
			if (map[y][x] == 'C' || map[y][x] == 'F')
				return (check_rgb(map[y], data));
			else
				break ;
		}
	}
	printf("here\n");
	return (0);
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
			if (skip_spaces(map[y]) != -1)
				x += skip_spaces(map[y]);
			if (start == -1 && (map[y][x] == 'C' || map[y][x] == 'F' || map[y][x] == 'S'
				|| map[y][x] == 'N' || map[y][x] == 'W' || map[y][x] == 'E'))
				break ;
			if (start == -1 && map[y][x] == '1')
				start = y;
			if ((map[y][x] != '1' && map[y][x] != '0'
				&& map[y][x] != 'N') && (skip_spaces(&map[y][x]) == -1
				&& map[y][x] != '\n'))
				return (NULL);
		}
	}
	return (mapcpy(&map[start]));
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
	(*data)->worldMap = valid_map(map);
	/*int	i;*/
	/*i = -1;*/
	/*while ((*data)->worldMap[++i])*/
	/*	printf("mapa: %s\n", (*data)->worldMap[i]);*/
	if (!(*data)->worldMap || !valid_rgb(map, data) || !fill(*data))
		return (0);
	return (1);
}
