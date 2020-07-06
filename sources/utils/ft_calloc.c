/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 15:23:52 by avieira           #+#    #+#             */
/*   Updated: 2020/07/03 16:38:27 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		bz(void *s, size_t n)
{
	unsigned char *temp;

	temp = s;
	while (n--)
		*temp++ = 0;
	return (0);
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char *alloc;

	if (!(alloc = malloc(size * count)))
		return (NULL);
	bz(alloc, size * count);
	return ((void *)alloc);
}
