# Makefile for so_long
NAME      = so_long

# Sources
SRC_DIR = src
AUX_DIR = aux/
#AUX_FILES = ft_printf/

SRC_FILES = main.c \
			render.c \
			get_next_line.c \
			get_next_line_utils.c \
			ft_split.c \
			ft_strdup.c
			#$(AUX_FILES)

SRC       = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

# Objects
OBJ_DIR   = obj
OBJ       = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# Compiler
CC_FLAGS   = cc -Wall -Wextra -Werror -g
INCLUDES  = -Iincludes -Imlx_linux

# MiniLibX
MLX_DIR   = minilibx-linux
MLX_LIB   = $(MLX_DIR)/libmlx_Linux.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz

# Build the static library
all: $(NAME)
$(NAME): $(OBJ)
	$(CC_FLAGS) $(OBJ) -o $(NAME) $(INCLUDES) $(MLX_FLAGS)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC_FLAGS) $(INCLUDES) -c $< -o $@

$(MLX_LIB):
	@make -C $(MLX_DIR)

$(OBJ_DIR):
	@mkdir -p $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
# Rebuild everything
re: fclean all
