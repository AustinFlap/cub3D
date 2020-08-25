/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 13:52:25 by avieira           #+#    #+#             */
/*   Updated: 2020/07/06 00:44:38 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void			ini_mlx(t_mlx *mlx, int *r, int save, t_game *game)
{
	int			screen_size[2];

	game->text_so.img.pimg = NULL;
	game->text_no.img.pimg = NULL;
	game->text_ea.img.pimg = NULL;
	game->text_we.img.pimg = NULL;
	game->text_s.img.pimg = NULL;
	game->img.pimg = NULL;
	game->mlx.win = NULL;
	game->mlx.pmlx = NULL;
	if (!(mlx->pmlx = mlx_init()))
		abort_cub3d(game);
	printf("init %p\n", mlx->pmlx);
	if (!save)
	{
		mlx_get_screen_size(mlx->pmlx, &screen_size[0], &screen_size[1]);
		r[0] = (r[0] > screen_size[0]) ? screen_size[0] : r[0];
		r[1] = (r[1] > screen_size[1]) ? screen_size[1] : r[1];
		if (!(mlx->win = mlx_new_window(mlx->pmlx, r[0], r[1], "cub3d")))
			abort_cub3d(game);
	}
}

void			ini_text(t_game *g)
{
	g->text_so.img.pimg = mlx_xpm_file_to_image(g->mlx.pmlx, g->file.path[1],
										&g->text_so.width, &g->text_so.height);
	g->text_no.img.pimg = mlx_xpm_file_to_image(g->mlx.pmlx, g->file.path[0],
										&g->text_no.width, &g->text_no.height);
	g->text_we.img.pimg = mlx_xpm_file_to_image(g->mlx.pmlx, g->file.path[2],
										&g->text_we.width, &g->text_we.height);
	g->text_ea.img.pimg = mlx_xpm_file_to_image(g->mlx.pmlx, g->file.path[3],
										&g->text_ea.width, &g->text_ea.height);
	g->text_s.img.pimg = mlx_xpm_file_to_image(g->mlx.pmlx, g->file.path[4],
										&g->text_s.width, &g->text_s.height);
	if (!(g->text_so.img.pimg && g->text_no.img.pimg && g->text_ea.img.pimg &&
									g->text_we.img.pimg && g->text_s.img.pimg))
		abort_cub3d(g);
	g->text_so.img.adr = mlx_get_data_addr(g->text_so.img.pimg,
		&g->text_so.img.bpp, &g->text_so.img.l_line, &g->text_so.img.endian);
	g->text_no.img.adr = mlx_get_data_addr(g->text_no.img.pimg,
		&g->text_no.img.bpp, &g->text_no.img.l_line, &g->text_no.img.endian);
	g->text_we.img.adr = mlx_get_data_addr(g->text_we.img.pimg,
		&g->text_we.img.bpp, &g->text_we.img.l_line, &g->text_we.img.endian);
	g->text_ea.img.adr = mlx_get_data_addr(g->text_ea.img.pimg,
		&g->text_ea.img.bpp, &g->text_ea.img.l_line, &g->text_ea.img.endian);
	g->text_s.img.adr = mlx_get_data_addr(g->text_s.img.pimg,
		&g->text_s.img.bpp, &g->text_s.img.l_line, &g->text_s.img.endian);
}

void			ini_edges(t_game *game, t_cam *cam, int edges[2], int *resy)
{
	*resy = game->file.r[1];
	cam->wallheight = (int)((double)*resy / cam->distance);
	edges[0] = -cam->wallheight / 2 + *resy / 2;
	edges[0] = (edges[0] < 0) ? 0 : edges[0];
	edges[1] = cam->wallheight / 2 + *resy / 2;
	edges[1] = (edges[1] < *resy) ? edges[1] : *resy - 1;
}

int				spr_count(t_sprite *sprite, char **map)
{
	int			n;
	int			i;
	int			j;

	i = -1;
	j = -1;
	n = 0;
	while (map[++i])
	{
		while (map[i][++j])
			if (map[i][j] == '2')
				n++;
		j = 0;
	}
	if (!((sprite->sprpos = ft_calloc(n, sizeof(t_sprpos))) &&
								(sprite->order = ft_calloc(n, sizeof(int)))))
		return (ERROR);
	if (!(sprite->dist = ft_calloc(n, sizeof(double))))
		return (ERROR);
	i = -1;
	while (++i < n)
		sprite->order[i] = i;
	sprite->n = n;
	return (SUCCESS);
}

int				ini_sprite(t_sprite *sprite, char **map)
{
	int			i;
	int			j;
	int			n;

	i = -1;
	j = -1;
	n = 0;
	if (spr_count(sprite, map) == ERROR)
		return (ERROR);
	while (map[++i])
	{
		while (map[i][++j])
		{
			if (map[i][j] == '2')
			{
				sprite->sprpos[n].x = i + 0.5;
				sprite->sprpos[n++].y = j + 0.5;
			}
			if (n == sprite->n)
				return (SUCCESS);
		}
		j = 0;
	}
	return (FAIL);
}
