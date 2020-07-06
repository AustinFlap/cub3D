/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 20:43:17 by avieira           #+#    #+#             */
/*   Updated: 2020/07/05 22:36:59 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int			write_map(t_file *file, char *line)
{
	char	*temp;

	temp = file->str_map;
	if (*file->str_map)
	{
		if (!(file->str_map = ft_strjoin(temp, "\n")))
			return (ERROR);
		free(temp);
	}
	temp = file->str_map;
	if (!(file->str_map = ft_strjoin(temp, line)))
		return (ERROR);
	free(temp);
	return (SUCCESS);
}

int			is_empty(char **map, int y, int x)
{
	int		iy;

	iy = -1;
	if (x >= 0 && y >= 0)
		while (map[++iy])
			if (iy == y)
				if (x < (int)ft_strlen(map[y]))
					if (map[y][x] != ' ')
						return (FAIL);
	return (SUCCESS);
}

int			is_next_to_empty(char **map, int y, int x)
{
	if (is_empty(map, y - 1, x) || is_empty(map, y, x - 1) ||
							is_empty(map, y + 1, x) || is_empty(map, y, x + 1))
		return (SUCCESS);
	return (FAIL);
}

int			check_map(char **map)
{
	int		start;
	int		x;
	int		y;
	char	pos;

	start = 0;
	x = -1;
	y = -1;
	while (map[++y])
	{
		while (map[y][++x])
		{
			pos = map[y][x];
			if (pos == 'N' || pos == 'S' || pos == 'E' || pos == 'W')
				start++;
			if (pos == '0' || pos == '2' || pos == 'N' || pos == 'S' ||
				pos == 'E' || pos == 'W')
				if (is_next_to_empty(map, y, x))
					return (FAIL);
		}
		x = 0;
	}
	if (start == 1)
		return (SUCCESS);
	return (FAIL);
}

int			assemble_map(t_file *file)
{
	if (!*file->str_map)
		return (FAIL);
	if (!(file->map = ft_split(file->str_map, '\n')))
		return (ERROR);
	return (check_map(file->map));
}
