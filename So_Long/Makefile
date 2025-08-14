# Makefile for so_long
NAME      = so_long

# Sources
SRC_DIR = src

SRC_FILES = main.c \
			filename_check.c \
			free_func.c \
			ft_split.c \
			game_init_and_setup.c \
			get_next_line_utils.c \
			get_next_line.c \
			map_check_func.c \
			map_scan.c \
			mapvalid_flood_and_boarder.c \
			player_move_and_input.c \
			render.c \
			str_func.c \
			window_and_img_handling.c \
			$(PRINTF_FILES)

SRC       = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

# Printf
PRINTF_DIR = ft_printf

PRINTF_FILES = ft_printf/ft_handle_hex.c \
               ft_printf/ft_handle_point.c \
               ft_printf/ft_printf.c \
			   ft_printf/ft_printerror.c \
               ft_printf/ft_putchar_fd.c \
               ft_printf/ft_putdecimal_int.c \
               ft_printf/ft_putnbr_fd.c \
               ft_printf/ft_putstr_fd.c
# Objects
OBJ_DIR   = obj
OBJ       = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# Compiler
CC_FLAGS   = cc -Wall -Wextra -Werror -g -fPIE
INCLUDES  = -Iincludes -Imlx_linux

# MiniLibX
MLX_DIR   = minilibx-linux
MLX_LIB   = $(MLX_DIR)/libmlx_Linux.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz

# Build the static library
all: $(NAME)
$(NAME): $(OBJ)
	@$(MAKE) -C $(MLX_DIR)
	$(CC_FLAGS) $(OBJ) -o $(NAME) $(INCLUDES) $(MLX_FLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC_FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(MLX_DIR)/obj

fclean: clean
	rm -f $(NAME)
# Rebuild everything
re: fclean all
