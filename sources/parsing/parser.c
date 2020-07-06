/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 15:25:27 by avieira           #+#    #+#             */
/*   Updated: 2020/07/06 00:23:36 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int				init(t_file *f, char **line, int *fd, char *file_name)
{
	f->r = NULL;
	f->f = NULL;
	f->c = NULL;
	f->map = NULL;
	*line = NULL;
	f->str_map = NULL;
	f->path = NULL;
	if (ft_strlen(file_name) > 4)
	{
		if (ft_strncmp(file_name + ft_strlen(file_name) - 4, ".cub", 4))
			return ((*fd = ERROR));
	}
	else
		return ((*fd = ERROR));
	if ((*fd = open(file_name, O_RDONLY)) == ERROR)
		return (ERROR);
	if (!(f->path = ft_calloc(5, sizeof(char *))))
		return (ERROR);
	if (!(f->str_map = ft_strdup("")))
		return (ERROR);
	return (SUCCESS);
}

int				error(int fd, char *line, char *check_map)
{
	write(1, "Error\n", 6);
	if (fd == -1)
		write(1, "Ouverture du fichier echoue\n", 28);
	else if (line)
	{
		write(1, "Derniere ligne lue -->", 22);
		write(1, line, ft_strlen(line));
		write(1, "<--\n", 4);
		close(fd);
		free(line);
	}
	else if (check_map[0])
		write(1, check_map, ft_strlen(check_map));
	return (ERROR);
}

int				map_set(char *line)
{
	int			i;
	const char	set[] = " 012NSWE\t";

	i = -1;
	if (!*line)
		return (FAIL);
	while (set[++i])
	{
		if (set[i] == *line)
		{
			line++;
			i = -1;
		}
		if (!*line)
			return (SUCCESS);
	}
	return (FAIL);
}

int				read_line(char *line, t_file *file)
{
	static int	map_status = 0;
	const char	*id[8] = {"NO ", "SO ", "WE ", "EA ", "S ", "R ", "F ", "C "};
	int			i;

	i = -1;
	map_status = (map_status && !map_set(line)) ? 2 : map_status;
	if (*line)
	{
		if (map_set(line))
		{
			if (map_status == 2)
				return (FAIL);
			map_status = 1;
			return (write_map(file, line));
		}
		else
			while (++i < 8)
				if (!ft_strncmp(line, id[i], ft_strlen(id[i])))
					if (!map_status)
						return (write_elem(file, i, line + ft_strlen(id[i])));
		return (FAIL);
	}
	return (SUCCESS);
}

int				parser(t_file *f, char *file_name)
{
	char		*line;
	int			fd;
	int			ret;

	if (init(f, &line, &fd, file_name) != SUCCESS)
		return (error(fd, line, ""));
	ret = 1;
	while (ret)
	{
		if ((ret = get_next_line(fd, &line)) == ERROR)
			return (error(fd, line, ""));
		if (read_line(line, f) != SUCCESS)
			return (error(fd, line, ""));
		free(line);
	}
	close(fd);
	if (assemble_map(f) != SUCCESS)
		return (error(fd, NULL, "Map non valide\n"));
	if (!f->path[0] || !f->path[1] || !f->path[2] || !f->path[3] || !f->path[4]
	|| !f->r || !f->c || !f->f)
		return (error(fd, NULL, "Element manquant\n"));
	f->hex_f = get_rgb(f->f[2], f->f[1], f->f[0]);
	f->hex_c = get_rgb(f->c[2], f->c[1], f->c[0]);
	return (SUCCESS);
}
