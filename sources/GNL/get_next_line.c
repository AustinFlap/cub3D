/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 18:24:13 by avieira           #+#    #+#             */
/*   Updated: 2020/05/04 23:19:28 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

static char			*append_line(char *buff, char *line, int *nl)
{
	int				l_to_end;
	int				l_buff;
	char			*temp_line;
	char			*temp_substr;

	l_to_end = ft_strl_spec(buff, '\n');
	l_buff = ft_strl_spec(buff, 0);
	if (!(temp_substr = ft_substr(buff, 0, l_to_end)))
		return (NULL);
	if (!(temp_line = ft_strjoin(line, temp_substr)))
		return (NULL);
	free(line);
	free(temp_substr);
	line = temp_line;
	*nl = (buff[l_to_end] == '\n') ? 1 : 0;
	ft_memcpy(buff, buff + l_to_end + *nl, l_buff - l_to_end - *nl + 1);
	if (buff[BUFFER_SIZE + 1])
		*nl = 1;
	return (line);
}

static int			ini_check(int fd, char **line, int *new_line)
{
	if (!line || !(MAX_FD > fd) || BUFFER_SIZE < 1 || fd < 0)
	{
		if (line)
			free(*line);
		return (1);
	}
	if (!(*line = ft_strdup("")))
		return (1);
	*new_line = 0;
	return (0);
}

int					get_next_line(int fd, char **line)
{
	static char		buff[MAX_FD][BUFFER_SIZE + 2];
	int				ret;
	int				new_line;

	if (ini_check(fd, line, &new_line))
		return (-1);
	while (!new_line)
	{
		if (!*buff[fd])
		{
			if ((ret = read(fd, buff[fd], BUFFER_SIZE)) == -1)
				return (ret);
			buff[fd][ret] = 0;
			if (ret < BUFFER_SIZE && !buff[fd][ft_strl_spec(buff[fd], '\n')])
				buff[fd][BUFFER_SIZE + 1] = 1;
		}
		if (!(*line = append_line(buff[fd], *line, &new_line)))
			return (-1);
	}
	if (!buff[fd][BUFFER_SIZE + 1])
		return (1);
	buff[fd][BUFFER_SIZE + 1] = 0;
	return (0);
}
