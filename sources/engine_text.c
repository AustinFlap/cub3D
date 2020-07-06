/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 09:29:34 by avieira           #+#    #+#             */
/*   Updated: 2020/07/05 23:23:34 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_text			*text_select(t_cam *cam, t_game *game, double *wallx)
{
	if (cam->side)
	{
		if (cam->rayy >= 0)
			return (&game->text_ea);
		*wallx = 1 - *wallx;
		return (&game->text_we);
	}
	else
	{
		if (cam->rayx <= 0)
			return (&game->text_no);
		*wallx = 1 - *wallx;
		return (&game->text_so);
	}
	return (NULL);
}

void			draw_text(t_game *game, int x, int edges[2], int *y)
{
	double		wallx;
	double		step;
	int			textpos[2];
	t_text		*text;
	double		pos;

	if (!game->cam.side)
		wallx = game->player.posy + game->cam.distance * game->cam.rayy;
	else
		wallx = game->player.posx + game->cam.distance * game->cam.rayx;
	wallx -= floor(wallx);
	text = text_select(&game->cam, game, &wallx);
	textpos[0] = (int)(wallx * (double)text->width);
	step = (double)text->height / game->cam.wallheight;
	pos = (edges[0] - game->file.r[1] / 2 + game->cam.wallheight / 2) * step;
	while (*y <= edges[1])
	{
		textpos[1] = (int)pos & (text->height - 1);
		pixel_put(&game->img, x, *y, pixel_get(&text->img, textpos[0],
															textpos[1]));
		pos += step;
		*y += 1;
	}
}
