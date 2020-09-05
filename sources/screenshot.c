/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 13:57:16 by avieira           #+#    #+#             */
/*   Updated: 2020/07/06 02:36:47 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void				file_header(int resy, int resx, unsigned char *file_h)
{
	long int		n_oct;
	int				pad;

	pad = (4 - (resx * 3) % 4) % 4;
	n_oct = 54 + (3 * resx + pad) * resy;
	file_h[0] = 'B';
	file_h[1] = 'M';
	file_h[2] = (unsigned char)(n_oct);
	file_h[3] = (unsigned char)(n_oct >> 8);
	file_h[4] = (unsigned char)(n_oct >> 16);
	file_h[5] = (unsigned char)(n_oct >> 24);
	file_h[6] = (unsigned char)(n_oct >> 32);
	file_h[7] = (unsigned char)(n_oct >> 40);
	file_h[8] = (unsigned char)(n_oct >> 48);
	file_h[9] = (unsigned char)(n_oct >> 56);
	file_h[10] = (unsigned char)54;
}

void				bmp_header(int resy, int resx, unsigned char *bmp_h)
{
	bmp_h[0] = (unsigned char)40;
	bmp_h[4] = (unsigned char)resx;
	bmp_h[5] = (unsigned char)(resx >> 8);
	bmp_h[6] = (unsigned char)(resx >> 16);
	bmp_h[7] = (unsigned char)(resx >> 24);
	bmp_h[8] = (unsigned char)resy;
	bmp_h[9] = (unsigned char)(resy >> 8);
	bmp_h[10] = (unsigned char)(resy >> 16);
	bmp_h[11] = (unsigned char)(resy >> 24);
	bmp_h[12] = (unsigned char)1;
	bmp_h[14] = (unsigned char)24;
}

int					convert_img(t_img *img, int fd, int resy, int resx)
{
	unsigned char	rgb[3];
	int				x;
	int				y;

	y = resy;
	while (--y > -1)
	{
		x = -1;
		while (++x < resx)
		{
			rgb[0] = pixel_get(img, x, y);
			rgb[1] = pixel_get(img, x, y) >> 8;
			rgb[2] = pixel_get(img, x, y) >> 16;
			if (write(fd, rgb, 3) == ERROR)
				return (ERROR);
		}
		write(fd, " ", (4 - (resx * 3) % 4) % 4);
	}
	return (SUCCESS);
}

void				abort_screenshot(t_game *game, unsigned char *bmp_h,
													unsigned char *file_h)
{
	if (bmp_h)
		free(bmp_h);
	if (file_h)
		free(file_h);
	abort_cub3d(game);
}

void				bmp(t_img *img, t_game *game)
{
	int				fd;
	unsigned char	*bmp_h;
	unsigned char	*file_h;

	bmp_h = NULL;
	file_h = NULL;
	if ((!(file_h = ft_calloc(14, sizeof(unsigned char))) ||
		!(bmp_h = ft_calloc(50, sizeof(unsigned char)))))
		abort_screenshot(game, bmp_h, file_h);
	if ((fd = open("screenshot.bmp", O_CREAT)) == ERROR)
		abort_screenshot(game, bmp_h, file_h);
	if (close(fd) == ERROR)
		abort_screenshot(game, bmp_h, file_h);
	file_header(game->file.r[1], game->file.r[0], file_h);
	bmp_header(game->file.r[1], game->file.r[0], bmp_h);
	if ((fd = open("screenshot.bmp", O_RDWR)) == ERROR)
		abort_screenshot(game, bmp_h, file_h);
	if (write(fd, file_h, 14) == ERROR || write(fd, bmp_h, 40) == ERROR)
		abort_screenshot(game, bmp_h, file_h);
	if (convert_img(img, fd, game->file.r[1], game->file.r[0]) == ERROR)
		abort_screenshot(game, bmp_h, file_h);
	if (close(fd) == ERROR)
		abort_screenshot(game, bmp_h, file_h);
	free(bmp_h);
	free(file_h);
}
