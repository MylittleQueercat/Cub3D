NAME = cub3d

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
		$(SRC_DIR)/parsing/sprite_and_door.c \
		$(SRC_DIR)/utils/error.c \
		$(SRC_DIR)/utils/free.c

OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJDIR)/%.o,$(SRC))

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
