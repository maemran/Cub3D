CC = cc
CFLAGS = -Wall -Werror -Wextra
MLX_FLAGS = -L. -lm -lmlx -lXext -lX11
MLX_DIR = ./minilibx
OBJ_DIR = OBJ
LIBFT_DIR = ./libft
NAME = cub3d
SRC = 	srcs/parsing/parsing.c					\
		srcs/parsing/directions.c				\
		srcs/parsing/cleanup.c					\
		srcs/parsing/map.c						\
		srcs/parsing/ceil.c						\
		srcs/parsing/floor.c					\
		srcs/parsing/initialize.c				\
		srcs/parsing/rgb.c						\
		srcs/parsing/flood_fill.c				\
		srcs/parsing/ceil_helper.c				\
		srcs/parsing/floor_helper.c 			\
		srcs/parsing/map_helper_one.c			\
		srcs/parsing/check_walls.c				\
		srcs/parsing/check_walls_two.c			\
		srcs/parsing/init_map.c					\
		srcs/parsing/ceil_utils.c				\
		srcs/parsing/cleanup_two.c				\
		srcs/parsing/map_utils.c				\
		srcs/parsing/set_dir_path.c				\
		srcs/parsing/read_file.c				\
		srcs/parsing/validate_res.c				\
		srcs/parsing/direction_utils.c			\
		srcs/raycasting/utils.c					\
		srcs/raycasting/textures_config.c		\
		srcs/raycasting/ray_casting.c			\
		srcs/raycasting/draw.c					\
		srcs/raycasting/movement.c				\
		srcs/raycasting/initialization.c		\
		srcs/raycasting/mlx_manage.c			\
		srcs/raycasting/keys.c					\
		srcs/raycasting/keys_utils.c			\
		srcs/main.c							

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(MLX_FLAGS) -L$(LIBFT_DIR) -lft -I./include

$(OBJ_DIR)/%.o:%.c ./include/cub3d.h $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I./include -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(MAKE) clean -C $(MLX_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -fr $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all re fclean clean
