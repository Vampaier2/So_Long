NAME = libftprintf.a

SRC_FILES =ft_handle_hex.c \
	ft_handle_point.c \
	ft_printf.c \
	ft_putchar_fd.c \
	ft_putdecimal_int.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c

# $<  = pre-requesitos

# -c = n fazer link aos files compilados.
# Gerar .o em vez de executavel

# -o = output
O_FILES = $(SRC_FILES:.c=.o)

CC = cc
C_FLAGS = -Wall -Wextra -Werror

AR = ar rcs

all: $(NAME)

$(NAME): $(O_FILES)
	$(AR) $(NAME) $(O_FILES)

clean:
	rm -f $(O_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all
