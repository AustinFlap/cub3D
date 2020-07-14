NAME = Cub3D

CC = clang

MKD = mkdir

RM = rm -rf

SRCS = 	sources/parsing/parser.c \
			sources/parsing/parser_elem.c \
			sources/parsing/parser_map.c \
			sources/GNL/get_next_line.c \
			sources/GNL/get_next_line_utils.c \
			sources/utils/ft_strlen.c \
			sources/utils/ft_strncmp.c \
			sources/utils/ft_strtrim.c \
			sources/utils/ft_atoi.c \
			sources/utils/ft_split.c \
			sources/cub3d.c \
			sources/engine.c \
			sources/utils.c \
			sources/engine_sprite.c \
			sources/engine_text.c \
			sources/movement.c \
			sources/init.c \
			sources/utils/ft_calloc.c \
			sources/destroy.c \
			sources/screenshot.c

OBJ = $(SRCS:%.c=%.o)

IFLAGS = ./includes/

CFLAGS = -Wall -Wextra -Werror -lm -lbsd -lX11 -lXext

SRC_DIR = sources/
GNL_DIR = sources/GNL/
PARS_DIR = sources/parsing/
UTILS_DIR = sources/utils/

MLX_DIR = minilibx-linux/

NAMEMLX = libmlx.a

STRT_STYLE = \033[1;32m

END_STYLE = \033[0m

all: $(NAME)

%.o: %.c
	@(gcc $(CFLAGS) -c -I$(IFLAGS) -I$(MLX_DIR) $< -o $(<:.c=.o))

$(NAME): $(OBJ)
	@(echo "$(STRT_STYLE)Compiling...$(END_STYLE)")
	@(cd $(MLX_DIR) && make -s)
	@(gcc -o $(NAME) -I$(IFLAGS) -I$(MLX_DIR) $(OBJ) $(MLX_DIR)/$(NAMEMLX) $(MLX_DIR)/libmlx_Linux.a $(CFLAGS))
	@(echo "$(STRT_STYLE)Done.$(END_STYLE)")

clean:
	@(echo "$(STRT_STYLE)Cleaning...$(END_STYLE)")
	@(make -s clean -C $(MLX_DIR))
	@($(RM) $(SRC_DIR)/*.o)
	@($(RM) $(GNL_DIR)/*.o)
	@($(RM) $(PARS_DIR)/*.o)
	@($(RM) $(UTILS_DIR)/*.o)
	@(echo "$(STRT_STYLE)Done.$(END_STYLE)")

fclean: clean
	@(echo "$(STRT_STYLE)Fcleaning...$(END_STYLE)")
	@($(RM) $(NAME))
	@(echo "$(STRT_STYLE)Done.$(END_STYLE)")

re: fclean all

.PHONY: all clean fclean re
