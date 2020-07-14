/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 23:05:36 by avieira           #+#    #+#             */
/*   Updated: 2020/07/05 23:15:35 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		abort_cub3d_at_input(char *msg)
{
	write(1, msg, ft_strlen(msg));
	exit(EXIT_SUCCESS);
}

void		abort_cub3d(t_game *game)
{
	perror("\nErreur");
	destroy(game, "");
}

void		free_text(t_game *game)
{
	if (game->text_so.img.pimg)
		mlx_destroy_image(game->mlx.pmlx, game->text_so.img.pimg);
	if (game->text_no.img.pimg)
		mlx_destroy_image(game->mlx.pmlx, game->text_no.img.pimg);
	if (game->text_ea.img.pimg)
		mlx_destroy_image(game->mlx.pmlx, game->text_ea.img.pimg);
	if (game->text_we.img.pimg)
		mlx_destroy_image(game->mlx.pmlx, game->text_we.img.pimg);
	if (game->text_s.img.pimg)
		mlx_destroy_image(game->mlx.pmlx, game->text_s.img.pimg);
}

void		free_file(t_file *file)
{
	int		i;

	i = -1;
	if (file->path)
	{
		while (++i < 5)
			if (file->path[i])
				free(file->path[i]);
		free(file->path);
	}
	if (file->r)
		free(file->r);
	if (file->f)
		free(file->f);
	if (file->c)
		free(file->c);
	if (file->str_map)
		free(file->str_map);
	i = -1;
	if (file->map)
	{
		while (file->map[++i])
			free(file->map[i]);
		free(file->map);
	}
}

int			destroy(t_game *game, char *msg)
{
	if (*msg != 17)
		write(1, msg, ft_strlen(msg));
	free_file(&game->file);
	if (game->mlx.pmlx)
	{
		free_text(game);
		if (!game->save)
			mlx_destroy_window(game->mlx.pmlx, game->mlx.win);
		free(game->sprite.sprpos);
		free(game->sprite.dist);
		free(game->sprite.order);
		free(game->mlx.pmlx);
	}
	exit(EXIT_SUCCESS);
	return (1);
}
