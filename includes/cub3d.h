/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 14:31:18 by avieira           #+#    #+#             */
/*   Updated: 2020/07/06 15:16:14 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include "../minilibx-linux/mlx.h"
# include "get_next_line.h"

# define SUCCESS 1
# define FAIL 0
# define ERROR -1
# define COL 1.0000000001

/*
** COMMANDES
** ---------
** forward
** backward
** right strafe
** left strafe
** look right
** look left
** escape
*/
# define FW 119
# define BW 115
# define LS 97
# define RS 100
# define LR 65363
# define LL 65361
# define ESC 65307

/*
** OPTIONS
*/

# define SPEED 0.1
# define ANG_SPD 0.07

# define FOV 0.66

# define XFACTOR 1
# define YFACTOR 1

typedef struct				s_file
{
	char					**path;
	int						*r;
	int						*f;
	unsigned int			hex_f;
	unsigned int			hex_c;
	int						*c;
	char					**map;
	char					*str_map;
}							t_file;

typedef struct				s_img
{
	void					*pimg;
	char					*adr;
	int						bpp;
	int						l_line;
	int						endian;
}							t_img;

typedef struct				s_text
{
	t_img					img;
	int						width;
	int						height;
}							t_text;

typedef struct				s_mlx
{
	void					*pmlx;
	void					*win;
}							t_mlx;

typedef struct				s_player
{
	double					posx;
	double					posy;
	double					dirx;
	double					diry;
	double					planx;
	double					plany;
}							t_player;

typedef struct				s_cam
{
	double					screenx;
	double					rayx;
	double					rayy;
	double					camx;
	double					camy;
	double					deltax;
	double					deltay;
	double					distx;
	double					disty;
	double					distance;
	double					wallheight;
	int						mapx;
	int						mapy;
	int						stepx;
	int						stepy;
	int						side;
}							t_cam;

typedef struct				s_sprpos
{
	double					x;
	double					y;
}							t_sprpos;

typedef struct				s_sprite
{
	t_sprpos				*sprpos;
	int						screenx;
	int						edgey[2];
	int						edgex[2];
	double					det;
	double					x;
	double					y;
	int						width;
	int						height;
	double					*dist;
	double					depthx;
	double					depthy;
	int						*order;
	int						n;
	int						shift;
}							t_sprite;

typedef struct				s_game
{
	t_mlx					mlx;
	t_cam					cam;
	t_file					file;
	t_player				player;
	t_img					img;
	t_text					text_so;
	t_text					text_no;
	t_text					text_we;
	t_text					text_ea;
	t_text					text_s;
	t_sprite				sprite;
	int						save;
}							t_game;

size_t						ft_strlen(const char *str);
int							ft_strncmp(const char *s1, const char *s2, int l);
int							write_elem(t_file *file, int id, char *line);
char						*ft_strtrim(char const *str, char const *sep);
int							ft_atoi(const char *number);
char						**ft_split(char const *str, char sep);
int							write_map(t_file *file, char *line);
int							assemble_map(t_file *file);
void						pixel_put(t_img *img, int x, int y,
															unsigned int color);
int							parser(t_file *file, char *file_name);
void						ini_player(t_player *player, char **map);
int							raycasting(t_game *game);
void						move(int key, t_player *player, char **pos);
void						rotate(int key, t_player *player);
unsigned int				get_rgb(int r, int g, int b);
void						ini_text(t_game *game);
void						ini_mlx(t_mlx *mlx, int *r, int save, t_game *game);
void						draw_text(t_game *game, int x, int *edges, int *y);
void						ini_edges(t_game *game, t_cam *cam, int *edges,
																	int *resy);
int							is_empty(char **map, int x, int y);
int							ini_sprite(t_sprite *sprite, char **map);
void						*ft_calloc(size_t count, size_t size);
void						sprite(t_game *game, double *l_ray);
void						swap(int *a, int *b);
double						regul_speed(double speed);
int							destroy(t_game *game, char *msg);
void						bmp(t_img *img, t_game *game);
unsigned int				pixel_get(t_img *img, int x, int y);
void						abort_cub3d(t_game *game);
double						regul_speed(double speed);
void						abort_cub3d_at_input(char *msg);

#endif
