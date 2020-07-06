/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 20:44:21 by avieira           #+#    #+#             */
/*   Updated: 2020/07/01 14:23:33 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int					overflow(int nb, char car, int u)
{
	unsigned int	test;

	test = nb + (car - 48) * u;
	if (test > 2147483647)
		return (1);
	return (0);
}

int					ft_atoi(const char *nptr)
{
	int				nb;
	const char		*temp;
	int				u;

	u = 1;
	nb = 0;
	temp = nptr;
	while ((*temp >= 9 && *temp <= 13) || *temp == ' ')
		temp++;
	if (*temp == '-' || *temp == '+')
		temp++;
	while (*temp >= '0' && *temp <= '9')
		temp++;
	while ((temp != nptr) || ((*temp < 9 && *temp > 13) && *temp-- != ' '))
	{
		if (*temp >= '0' && *temp <= '9')
		{
			if (overflow(nb, *temp, u))
				return (2147483647);
			nb += (*temp - 48) * u;
			u *= 10;
		}
		nb = (*temp == '-') ? -nb : nb;
	}
	return (nb);
}
