/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 21:57:32 by avieira           #+#    #+#             */
/*   Updated: 2020/07/06 00:45:08 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		move_front(double spd, t_player *plr, char **map, double *pos[2])
{
	if (map[(int)(*pos[0] + plr->dirx * COL * spd)][(int)(*pos[1])] != '1')
		*pos[0] += plr->dirx * spd;
	if (map[(int)(*pos[0])][(int)(*pos[1] + plr->diry * COL * spd)] != '1')
		*pos[1] += plr->diry * spd;
}

void		move_side(double spd, t_player *plr, char **map, double *pos[2])
{
	if (map[(int)(*pos[0])][(int)(*pos[1] - plr->dirx * COL * spd)] != '1')
		*pos[1] -= plr->dirx * spd;
	if (map[(int)(*pos[0] + plr->diry * COL * spd)][(int)(*pos[1])] != '1')
		*pos[0] += plr->diry * spd;
}

void		move(int key, t_player *player, char **map)
{
	double	spd;
	double	*pos[2];

	pos[0] = &player->posx;
	pos[1] = &player->posy;
	spd = (key == BW || key == LS) ? -SPEED : SPEED;
	if (key == FW || key == BW)
		move_front(spd, player, map, pos);
	else
		move_side(spd, player, map, pos);
}

void		rotate(int key, t_player *player)
{
	double	angle;
	double	temp;

	angle = (key == LR) ? -ANG_SPD : ANG_SPD;
	temp = player->dirx;
	player->dirx = player->dirx * cos(angle) - player->diry * sin(angle);
	player->diry = temp * sin(angle) + player->diry * cos(angle);
	temp = player->planx;
	player->planx = player->planx * cos(angle) - player->plany * sin(angle);
	player->plany = temp * sin(angle) + player->plany * cos(angle);
}

void		ini_player(t_player *player, char **map)
{
	int		x;
	int		y;

	x = -1;
	y = -1;
	while (map[++x])
	{
		while (map[x][++y])
			if (map[x][y] == 'N' || map[x][y] == 'S' ||
										map[x][y] == 'E' || map[x][y] == 'W')
			{
				player->posx = x + 0.5;
				player->posy = y + 0.5;
				player->diry = (map[x][y] == 'E') ? 1 : 0;
				player->diry = (map[x][y] == 'W') ? -1 : player->diry;
				player->dirx = (map[x][y] == 'S') ? 1 : 0;
				player->dirx = (map[x][y] == 'N') ? -1 : player->dirx;
			}
		y = -1;
	}
	player->planx = FOV * player->diry;
	player->plany = -FOV * player->dirx;
}
