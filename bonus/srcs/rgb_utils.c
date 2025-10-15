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
	check_count(rgb, data);
}

void	check_count(char *str, t_data **data)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (ft_strlen(ft_strchr(str, str[i])) != \
ft_strlen(ft_strrchr(str, str[i])))
		{
			free(str);
			parse_exit(*data);
		}
	}
	free(str);
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
