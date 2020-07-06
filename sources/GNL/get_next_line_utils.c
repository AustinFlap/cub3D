/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 14:15:30 by avieira           #+#    #+#             */
/*   Updated: 2020/05/04 23:19:50 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

size_t					ft_strl_spec(const char *s, char spec)
{
	int					l;

	l = 0;
	while (s[l] && s[l] != spec)
		l++;
	return (l);
}

char					*ft_strjoin(char *s1, char *s2)
{
	char				*s;
	int					i;
	int					j;

	if (!s1 || !s2)
		return (NULL);
	if (!(s = malloc(sizeof(char) * (ft_strl_spec(s1, 0)
		+ ft_strl_spec(s2, 0) + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		s[j++] = s1[i++];
	i = 0;
	while (s2[i])
		s[j++] = s2[i++];
	s[j] = 0;
	return (s);
}

char					*ft_strdup(char *s1)
{
	char				*cpy;
	char				*temp;
	int					len;

	len = 0;
	while (s1[len])
		len++;
	if (!(cpy = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	temp = cpy;
	while (len--)
		*temp++ = *s1++;
	*temp = 0;
	return (cpy);
}

void					*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*t_dst;
	const unsigned char	*t_src;

	t_dst = dst;
	t_src = src;
	if (!dst && !src)
		return (NULL);
	while (n--)
		*t_dst++ = *t_src++;
	return (dst);
}

char					*ft_substr(char const *s, unsigned int start, size_t l)
{
	int					i;
	char				*substr;
	unsigned int		len_s;

	len_s = 0;
	if (!s)
		return (NULL);
	while (s[len_s])
		len_s++;
	l = (l > len_s - start) ? len_s - start : l;
	l = (start > len_s) ? 0 : l;
	if (!(substr = malloc(sizeof(char) * (l + 1))))
		return (NULL);
	i = 0;
	while (l-- && s[start + i])
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = 0;
	return (substr);
}
