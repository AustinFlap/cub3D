/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 12:50:55 by avieira           #+#    #+#             */
/*   Updated: 2020/07/06 02:05:55 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void				get_dist(t_sprite *sprite, t_player plr)
{
	int				i;

	i = -1;
	while (++i < sprite->n)
	{
		sprite->dist[i] = ((plr.posx - sprite->sprpos[i].x) *
		(plr.posx - sprite->sprpos[i].x) + (plr.posy - sprite->sprpos[i].y) *
		(plr.posy - sprite->sprpos[i].y));
	}
}

void				spr_sort(t_sprite *sprite)
{
	int				i;

	i = -1;
	while (++i < sprite->n - 1)
		if (sprite->dist[sprite->order[i]] <
									sprite->dist[sprite->order[i + 1]])
		{
			swap(&sprite->order[i], &sprite->order[i + 1]);
			i = -1;
		}
}

void				draw_sprite(t_sprite *spr, t_game *game, t_text *text_s,
																double *l_ray)
{
	int				pos[2];
	int				sprx;
	int				spry;
	unsigned int	pixel;

	pos[0] = spr->edgex[0] - 1;
	pos[1] = spr->edgey[0] - 1;
	while (++(pos[1]) <= spr->edgey[1])
	{
		spry = (((pos[1] * 256 - game->file.r[1] * 128 +
					spr->height * 128) * text_s->height) / spr->height) / 256;
		while (++(pos[0]) <= spr->edgex[1])
		{
			if (pos[0] >= 0 && pos[0] < game->file.r[0] && spr->depthy > 0 &&
				spr->depthy < l_ray[pos[0]])
			{
				sprx = (int)(256 * (pos[0] - (-spr->width / 2 + spr->screenx)) *
						text_s->width / spr->width) / 256;
				if (sprx >= 0 && spry >= 0)
					if ((pixel = pixel_get(&text_s->img, sprx, spry)))
						pixel_put(&game->img, pos[0], pos[1], pixel);
			}
		}
		pos[0] = spr->edgex[0] - 1;
	}
}

void				calc_spr(t_sprite *spr, int i, t_game *game)
{
	spr->x = spr->sprpos[spr->order[i]].x - game->player.posx;
	spr->y = spr->sprpos[spr->order[i]].y - game->player.posy;
	spr->det = 1.0 / (game->player.planx * game->player.diry -
									game->player.plany * game->player.dirx);
	spr->depthx = spr->det * (game->player.diry * spr->x -
												game->player.dirx * spr->y);
	spr->depthy = spr->det * (-game->player.plany * spr->x +
												game->player.planx * spr->y);
	spr->screenx = (int)((game->file.r[0] / 2) *
								(1 + spr->depthx / spr->depthy));
	spr->height = abs((int)(game->file.r[1] / spr->depthy)) / YFACTOR;
	spr->edgey[0] = -spr->height / 2 + game->file.r[1] / 2;
	spr->edgey[0] = (spr->edgey[0] < 0) ? 0 : spr->edgey[0];
	spr->edgey[1] = spr->height / 2 + game->file.r[1] / 2;
	spr->edgey[1] = (spr->edgey[1] >= game->file.r[1]) ?
										game->file.r[1] - 1 : spr->edgey[1];
	spr->width = abs((int)(game->file.r[0] / spr->depthy)) / XFACTOR;
	spr->edgex[0] = -spr->width / 2 + spr->screenx;
	spr->edgex[0] = (spr->edgex[0] < 0) ? 0 : spr->edgex[0];
	spr->edgex[1] = spr->width / 2 + spr->screenx;
	spr->edgex[1] = (spr->edgex[1] >= game->file.r[0]) ?
										game->file.r[0] - 1 : spr->edgex[1];
}

void				sprite(t_game *game, double *l_ray)
{
	int				i;

	get_dist(&game->sprite, game->player);
	spr_sort(&game->sprite);
	i = -1;
	while (++i < game->sprite.n)
	{
		calc_spr(&game->sprite, i, game);
		draw_sprite(&game->sprite, game, &game->text_s, l_ray);
	}
}
