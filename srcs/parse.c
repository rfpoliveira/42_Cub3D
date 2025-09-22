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
			if (skip_spaces(map[y]) != -1)
				x = skip_spaces(map[y]);
			if (map[y][x] == 'C' || map[y][x] == 'F')
				return (check_rgb(map[y], data));
			else
				break ;
		}
	}
	return (0);
}

void	set_text(char **map, t_data **data, int y, int x)
{
	char	*temp;

	temp = NULL;
	x += skip_spaces(&map[y][x]);
	temp = ft_substr(map[y], x, ft_strlen(&map[y][x]));
	if (mlx_xpm_file_to_image((*data)->mlx, temp, &(*data)->draw->tex_w,
		&(*data)->draw->tex_h))
		{
			(*data)->draw->textures->img = mlx_xpm_file_to_image((*data)->mlx, temp,
				&(*data)->draw->tex_w, &(*data)->draw->tex_h);
		}
	free(temp);
}

int	check_text(char **map, t_data **data)
{
	int	y;
	int	x;

	y = -1;
	(*data)->draw->textures->img = NULL;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == 'N' && map[y][x + 1] == 'O')
				set_text(map, data, y, x);
			if (map[y][x] == 'S' && map[y][x + 1] == 'O')
				set_text(map, data, y, x);
			if (map[y][x] == 'W' && map[y][x + 1] == 'E')
				set_text(map, data, y, x);
			if (map[y][x] == 'E' && map[y][x + 1] == 'A')
				set_text(map, data, y, x);
		}
	}
	if (!(*data)->draw->textures->img)
		return (0);
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
			if (skip_spaces(&map[y][x]) != -1)
				x += skip_spaces(&map[y][x]);
			if (start == -1 && (map[y][x] == 'C' || map[y][x] == 'F' || map[y][x] == 'S'
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
	while (temp && y < size - 2)
	{
		free(temp);
		temp = NULL;
		temp = get_next_line(fd);
		map[++y] = ft_strdup(temp);
		map[y][(ft_strlen(map[y]) - 1)] = '\0';
	}
	(*data)->worldMap = valid_map(map);
	int	i;
	i = -1;
	while ((*data)->worldMap[++i])
		printf("mapa: %s\n", (*data)->worldMap[i]);
	if (!(*data)->worldMap || !char_check((*data)->worldMap) || !valid_rgb(map, data) || !fill(*data))
		return (0);
	return (1);
}
