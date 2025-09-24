/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpatrici <jpatrici@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:19:18 by jpatrici          #+#    #+#             */
/*   Updated: 2025/09/17 15:54:35 by jpatrici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

void	parse_exit(t_data *data)
{
	int	i;

	i = -1;
	if (data->worldMap)
	{
		while (data->worldMap[++i])
			free(data->worldMap[i]);
		free(data->worldMap);
	}
	i = -1;
	if (data->draw)
	{
		if (data->draw->textures[0].img)
			while (data->draw->textures[++i].img)
				mlx_destroy_image(data->mlx, data->draw->textures[i].img);
		free(data->draw);
	}
	if (data->mlx)
		free(data->mlx);
	if (data)
		free(data);
	ft_putstr_fd("Error\nInvalid map\n", 2);
	exit(1);
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
	{
		temp[y] = ft_substr(map[y], 0, ft_strlen(map[y]));
		temp[y][ft_strlen(map[y])] = '\0';
	}
	return (temp);
}

int	skip_spaces(char *line)
{
	int	x;

	x = 0;
	while (line[x] == ' ' || line[x] == '\t')
		x++;
	if (line[x] == '\n' || line[x] == '\0')
		return (-1);
	else
		return (x);
}

int	check_digit(char *file)
{
	int	x;
	int	n;

	x = -1;
	n = 0;
	while (file[++x])
	{
		if (file[x] >= '0' && file[x] <= '9')
			n++;	
		if (file[x] == ' ' || file[x] == '\t'
			|| file[x] == '\n' || file[x] == ',')
			return (n);
	}
	return (-1);
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
	close(fd);
	return (size);
}
