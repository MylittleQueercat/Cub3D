NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -Iminilibx

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -lX11 -lXext -lm

OBJDIR = obj
SRC_DIR = src

SRC =	$(SRC_DIR)/main.c \
		$(SRC_DIR)/parsing/check_elements.c \
		$(SRC_DIR)/parsing/get_map.c \
		$(SRC_DIR)/parsing/parse.c \
		$(SRC_DIR)/parsing/parse_color.c \
		$(SRC_DIR)/parsing/parse_map.c \
		$(SRC_DIR)/parsing/parse_texture.c \
		$(SRC_DIR)/parsing/prepare_map.c \
		$(SRC_DIR)/parsing/utils.c \
		$(SRC_DIR)/sprites/init_sprites.c \
		$(SRC_DIR)/sprites/render_sprites.c \
		$(SRC_DIR)/sprites/sprite_collision.c \
		$(SRC_DIR)/hooks.c \
		$(SRC_DIR)/hooks_util.c \
		$(SRC_DIR)/doors_util.c \
		$(SRC_DIR)/draw_door_overlay.c \
		$(SRC_DIR)/mouse_bonus.c \
     	$(SRC_DIR)/init_club.c \
    	$(SRC_DIR)/render_background.c \
		$(SRC_DIR)/walls_util.c \
		$(SRC_DIR)/img_utils.c \
		$(SRC_DIR)/move.c \
		$(SRC_DIR)/textures.c \
		$(SRC_DIR)/render_walls.c \
		$(SRC_DIR)/render_minimap_bonus.c \
		$(SRC_DIR)/utils/error.c \
		$(SRC_DIR)/utils/free.c

OBJ = $(addprefix $(OBJDIR)/,$(subst $(SRC_DIR)/,,$(SRC:.c=.o)))

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(NAME)

$(OBJDIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm -rf $(OBJDIR)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
