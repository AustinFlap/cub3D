/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 09:12:08 by avieira           #+#    #+#             */
/*   Updated: 2020/07/24 13:45:23 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void			pixel_put(t_img *img, int x, int y, unsigned int color)
{
	char		*dst;

	dst = img->adr + (y * img->l_line  + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

unsigned int	pixel_get(t_img *img, int x, int y)
{
	char		*dst;

	dst = img->adr + (y * img->l_line + x * (img->bpp / 8));
	return (*(unsigned int *)dst);
}

unsigned int	get_rgb(int r, int g, int b)
{
	return (b << 16 | g << 8 | r);
}

void			swap(int *a, int *b)
{
	int			temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

double			regul_speed(double speed)
{
	if (speed < -1.0)
		return (-1.0);
	else if (speed > 1.0)
		return (1.0);
	return (speed);
}
