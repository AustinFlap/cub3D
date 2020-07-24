/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_elem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 04:20:22 by avieira           #+#    #+#             */
/*   Updated: 2020/07/24 12:31:28 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int			is_sep(int c, int cm)
{
	if (c == ' ' || c == '\t' || (cm && c == ','))
		return (SUCCESS);
	return (FAIL);
}

int			valid_elem(char *line, int is_nb, int cm, int n_goal)
{
	int		n;
	int		n_cm;

	n = 0;
	n_cm = 0;
	while (*line)
	{
		if (is_nb && !(*line >= '0' && *line <= '9') && !is_sep(*line, cm))
			return (FAIL);
		if (!is_sep(*line, cm) && (is_sep(*(line + 1), cm) || !*(line + 1)))
		{
			n_cm--;
			n++;
		}
		n_cm = (*line == ',') ? n_cm + 1 : n_cm;
		if (cm && ((n_cm != 0 && n_cm != -1) ||
									(*line == ',' && n == 0 && n == n_goal)))
			return (FAIL);
		line++;
	}
	if (n != n_goal || (n_cm != -1 && cm) ||
									(n == n_goal && is_sep(*(line - 1), 0)))
		return (FAIL);
	return (SUCCESS);
}

int			path(t_file *file, int id, char *line, int n_goal)
{
	(void)n_goal;
	if (file->path[id])
		return (FAIL);
	if (!(file->path[id] = ft_strtrim(line, " \t")))
		return (ERROR);
	if (ft_strcmp(file->path[id] + ft_strlen(file->path[id]) - 4, ".xpm"))
		return (ERROR);
	return (SUCCESS);
}

int			value(t_file *file, int id, char *line, int n_goal)
{
	int		n;
	int		*temp;

	n = 0;
	if ((id == 5 && file->r) || (id == 6 && file->f) || (id == 7 && file->c))
		return (FAIL);
	if (!(temp = malloc(sizeof(int) * n_goal)))
		return (ERROR);
	while (*line++)
		if (!is_sep(*(line - 1), 1))
		{
			if ((temp[n++] = ft_atoi(line - 1)) > 255 && (id == 6 || id == 7))
			{
				free(temp);
				return (ERROR);
			}
			while (!is_sep(*(line - 1), 1) && *line)
				line++;
		}
	file->r = (id == 5) ? temp : file->r;
	file->f = (id == 6) ? temp : file->f;
	file->c = (id == 7) ? temp : file->c;
	if (id == 5 && (!file->r[0] || !file->r[1]))
		return (ERROR);
	return (SUCCESS);
}

int			write_elem(t_file *file, int id, char *line)
{
	int		(*f[8])(t_file *, int, char *, int);
	int		is_nb;
	int		cm;
	int		n_goal;

	cm = (id > 5) ? 1 : 0;
	is_nb = (id < 5) ? 0 : 1;
	n_goal = (id < 5) ? 1 : 2;
	n_goal = (id > 5) ? 3 : n_goal;
	if (id < 8 && id > 4)
		if (valid_elem(line, is_nb, cm, n_goal) != SUCCESS)
			return (FAIL);
	f[0] = &path;
	f[1] = &path;
	f[2] = &path;
	f[3] = &path;
	f[4] = &path;
	f[5] = &value;
	f[6] = &value;
	f[7] = &value;
	return (f[id](file, id, line, n_goal));
}
