NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -Iminilibx

MLX_DIR = minilibx
MLX = $(MLX_DIR)/libmlx.a
//MLX_FLAGS = -framework OpenGL -framework AppKit 
MLX_FLAGS = -lX11 -lXext -lm


SRC_DIR = src
SRC = $(SRC_DIR)/main.c \
      $(SRC_DIR)/hooks.c \
      $(SRC_DIR)/init_club.c \
      $(SRC_DIR)/img_utils.c \
      $(SRC_DIR)/render_background.c \
	  $(SRC_DIR)/walls_util.c \
	  $(SRC_DIR)/move.c \
	  $(SRC_DIR)/textures.c \
	  $(SRC_DIR)/render_walls.c \
	  $(SRC_DIR)/render_minimap_bonus.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
