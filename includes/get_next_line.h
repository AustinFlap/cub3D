/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 14:31:18 by avieira           #+#    #+#             */
/*   Updated: 2020/05/03 22:01:28 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# define MAX_FD 250
# define BUFFER_SIZE 2048

char			*ft_strjoin(char *s1, char *s2);
char			*ft_strdup(char *s1);
char			*ft_substr(char const *s, unsigned int start, size_t len);
size_t			ft_strl_spec(const char *str, char spec);
void			*ft_memcpy(void *dst, const void *src, size_t n);
int				get_next_line(int fd, char **line);

#endif
