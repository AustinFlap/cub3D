/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 15:55:18 by avieira           #+#    #+#             */
/*   Updated: 2020/07/24 13:53:32 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int				input(int key, t_game *game)
{
	if (key == LS || key == RS || key == FW || key == BW)
		move(key, &game->player, game->file.map);
	if (key == LR || key == LL)
		rotate(key, &game->player);
	if (key == ESC)
		destroy(game, "");
	return (1);
}

void			screen_manager(t_game *game)
{
	if (!(game->l_ray = malloc(sizeof(double) * game->file.r[0])))
		abort_cub3d(game);
	if (!game->save)
	{
		mlx_hook(game->mlx.win, 17, 1L << 17, &destroy, game);
		mlx_hook(game->mlx.win, 2, 1L << 0, &input, game);
		mlx_loop_hook(game->mlx.pmlx, &raycasting, game);
		mlx_loop(game->mlx.pmlx);
	}
	else
	{
		raycasting(game);
		destroy(game, "");
	}
}

int				main(int ac, char **av)
{
	t_game		game;

	game.save = 0;
	game.mlx.pmlx = NULL;
	if (ac == 3)
	{
		if (ft_strcmp(av[2], "--save"))
			abort_cub3d_at_input("\nArgument invalide\n");
		game.save = 1;
	}
	if (ac > 3 || ac < 2)
		abort_cub3d_at_input("\nNombre d'arguments invalide\n");
	if (parser(&game.file, av[1]) != SUCCESS)
		destroy(&game, "");
	ini_mlx(&game.mlx, game.file.r, game.save, &game);
	if (ini_sprite(&game.sprite, game.file.map) == ERROR)
		abort_cub3d(&game);
	ini_player(&game.player, game.file.map);
	ini_text(&game);
	screen_manager(&game);
}
