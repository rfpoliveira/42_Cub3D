/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:00:33 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/10/15 15:02:40 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cube.h"

void	count_rgb(char **map, t_data **data, int size)
{
	int		i;
	int		y;
	int		x;
	char	*rgb;

	y = -1;
	i = -1;
	rgb = ft_calloc(sizeof(char), size);
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == 'C')
				rgb[++i] = 'C';
			if (map[y][x] == 'F')
				rgb[++i] = 'F';
		}
	}
	check_count(rgb, map, data);
	if (rgb)
		free(rgb);
}

void	check_count(char *str, char **map, t_data **data)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (i == 0 || ((str[i - 1] == 'C' || str[i - 1] == 'F') && i != 2)
		|| ((str[i - 1] == 'N' || str[i - 1] == 'S'
				|| str[i - 1] == 'W' || str[i - 1] == 'E') && i != 4))
	{
		free(str);
		str = NULL;
		free_map(&map);
		parse_exit(*data);
	}
}

int	ft_strchrlen(char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}
