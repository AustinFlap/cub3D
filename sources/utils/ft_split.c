/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 14:49:28 by avieira           #+#    #+#             */
/*   Updated: 2020/05/04 23:20:30 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int		word_count(char const *s, char c)
{
	int n;
	int i;

	i = 0;
	n = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			n++;
			while (s[i] != c && s[i])
				i++;
		}
		while (s[i] == c && s[i])
			i++;
	}
	return (n);
}

static int		len_to_sep(char const *s, char c, int i)
{
	int l;

	l = 0;
	while (s[i] != c && s[i])
	{
		l++;
		i++;
	}
	return (l);
}

static int		word_create(char const *s, char c, int i, char *split)
{
	int a;

	a = 0;
	while (s[i] != c && s[i])
	{
		split[a] = s[i];
		a++;
		i++;
	}
	split[a] = 0;
	return (i);
}

char			**ft_split(char const *s, char c)
{
	char	**split;
	int		i;
	int		j;
	int		n_words;

	n_words = word_count(s, c);
	if (!(split = malloc(sizeof(char *) * (n_words + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (j < n_words)
	{
		while (s[i] == c && s[i])
			i++;
		if (!(split[j] = malloc(sizeof(char) * (len_to_sep(s, c, i) + 1))))
			return (NULL);
		i = word_create(s, c, i, split[j]);
		while (s[i] == c && s[i])
			i++;
		j++;
	}
	split[j] = NULL;
	return (split);
}
