/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 16:27:03 by avieira           #+#    #+#             */
/*   Updated: 2020/07/24 13:53:14 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		camera(t_cam *cam, int x, t_player *player, int resx)
{
	cam->screenx = 2 * x / (double)resx - 1;
	cam->rayx = player->dirx + player->planx * cam->screenx;
	cam->rayy = player->diry + player->plany * cam->screenx;
	cam->deltax = fabs(1.0 / cam->rayx);
	cam->deltay = fabs(1.0 / cam->rayy);
	cam->mapx = (int)player->posx;
	cam->mapy = (int)player->posy;
	cam->stepx = (cam->rayx < 0) ? -1 : 1;
	cam->stepy = (cam->rayy < 0) ? -1 : 1;
	if (cam->stepx == -1)
		cam->distx = (player->posx - cam->mapx) * cam->deltax;
	else
		cam->distx = (cam->mapx + 1 - player->posx) * cam->deltax;
	if (cam->stepy == -1)
		cam->disty = (player->posy - cam->mapy) * cam->deltay;
	else
		cam->disty = (cam->mapy + 1 - player->posy) * cam->deltay;
}

void		detection(t_cam *cam, t_file *file)
{
	int		hit;

	hit = 0;
	while (!hit)
	{
		if (cam->distx < cam->disty)
		{
			cam->distx += cam->deltax;
			cam->mapx += cam->stepx;
			cam->side = 0;
		}
		else
		{
			cam->disty += cam->deltay;
			cam->mapy += cam->stepy;
			cam->side = 1;
		}
		hit = (file->map[cam->mapx][cam->mapy] == '1') ? 1 : 0;
	}
}

void		get_distance(t_cam *cam, t_player *player)
{
	if (!cam->side)
		cam->distance = (cam->mapx - player->posx + (1 - cam->stepx) / 2)
																/ cam->rayx;
	else
		cam->distance = (cam->mapy - player->posy + (1 - cam->stepy) / 2)
																/ cam->rayy;
}

void		draw_line(t_cam *cam, int x, t_game *game)
{
	int		edges[2];
	int		resy;
	int		y;

	ini_edges(game, cam, edges, &resy);
	y = 0;
	while (y < edges[0])
	{
		pixel_put(&game->img, x, y, game->file.hex_c);
		y++;
	}
	draw_text(game, x, edges, &y);
	while (y < resy)
	{
		pixel_put(&game->img, x, y, game->file.hex_f);
		y++;
	}
}

int			raycasting(t_game *game)
{
	int		x;
	double	l_ray[game->file.r[0]];

	if (!(game->img.pimg = mlx_new_image(game->mlx.pmlx, game->file.r[0]
														, game->file.r[1])))
		abort_cub3d(game);
	game->img.adr = mlx_get_data_addr(game->img.pimg, &game->img.bpp,
										&game->img.l_line, &game->img.endian);
	x = -1;
	while (++x < game->file.r[0])
	{
		camera(&game->cam, x, &game->player, game->file.r[0]);
		detection(&game->cam, &game->file);
		get_distance(&game->cam, &game->player);
		draw_line(&game->cam, x, game);
		l_ray[x] = game->cam.distance;
	}
	sprite(game, l_ray);
	if (!game->save)
		mlx_put_image_to_window(game->mlx.pmlx, game->mlx.win,
														game->img.pimg, 0, 0);
	else
		bmp(&game->img, game);
	mlx_destroy_image(game->mlx.pmlx, game->img.pimg);
	return (1);
}
