/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:32:16 by xalves            #+#    #+#             */
/*   Updated: 2025/08/11 18:27:50 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../minilibx-linux/mlx.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <stddef.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdarg.h>

# define SPRITE_SIZE 64
# define BUFFER_SIZE 1

typedef struct s_img
{
	void	*ptr;// Image pointer
	int		bpp;// Bits per pixel
	int		line_len;// Line length in bytes
	int		endian;// Endianness
}			t_img;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	bool	tex_loaded;// Track if textures are loaded
	char	**map;
	size_t	rows;
	size_t	row_len;
	size_t	player_count;
	size_t	player_y;
	size_t	player_x;
	size_t	cheese_count;
	size_t	exit_count;
    size_t	cheese_dupecount;

    size_t	exit_y;
	size_t	exit_x;

	t_img	wall;
	t_img	floor;
	t_img	player;// Player sprite
	t_img	cheese;
	t_img	desumi;
	t_img	mouse_trap;
}			t_game;

int		load_textures(t_game *game);
int		render_frame(t_game *game);
void	setup_renderer(t_game *game);
void	ft_put_image(t_game *game, char c, int x, int y);

void	ft_free_map(char **map);

char	**ft_split(const char *s, char c);

char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
char	*x_strjoin(char const *s1, char const *s2);
int		ft_strcmp(char *s1, char *s2);

// map check funcs 1
size_t	check_top_bot_lines(char *s);
int		check_valid_char(char s, t_game *game, size_t y, size_t x);
int		check_boarders(char c);
int		check_pec_count(t_game *game);

#endif
