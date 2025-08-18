/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:32:16 by xalves            #+#    #+#             */
/*   Updated: 2025/08/18 15:24:51 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../minilibx-linux/mlx.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

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
	bool	tex_loaded; // Track if textures are loaded
	char	**map;
	size_t	rows;
	size_t	row_len;
	size_t	player_count;
	size_t	player_y;
	size_t	player_x;
	size_t	player_moves;

	size_t	cheese_count;
	size_t	cheese_dupecount;

	size_t	exit_count;
	char	*current_pos;
	char	*next_pos;

	size_t	exit_y;
	size_t	exit_x;
	size_t	player_on_exit;

	t_img	wall;
	t_img	floor;
	t_img	player; // Player sprite
	t_img	cheese;
	t_img	desumi;
	t_img	desumi_on;
	t_img	mouse_trap;
}			t_game;

int			load_textures(t_game *game);
int			render_frame(t_game *game);
void		setup_renderer(t_game *game);
void		ft_put_image(t_game *game, char c, int x, int y);

void		ft_free_map(char **map);
void	ft_free_linefilefd(char *big_line, char *file, int fd);


char		**ft_split(const char *s, char c);

char		*ft_strdup(const char *s);
size_t		ft_strlen(const char *s);
char		*x_strjoin(char const *s1, char const *s2);
int			ft_strcmp(char *s1, char *s2);

char		*ft_itoa(int n);

// Game initiation && Setup

void		init_game(t_game *game);
int			setup_game(t_game *game, char *map_file);
int			setup_graphics(t_game *game);
void		mlx_and_input(t_game *game);

// Player Movement && Input
int			key_press(int key, t_game *game);
int			move_player(t_game *game, int y, int x);
void		apply_move(t_game *game, int y, int x);
void		inc_and_printmove(t_game *game);

// Window & Image Handling
void		destroy_images(t_game *game);
int			close_window(t_game *game);

// Map Validation
void		flood_fill(char **map, int x, int y, t_game *game);
int			cicle_thru_midrows(t_game *game, int y, int top_line_len);
int			check_lines(t_game *game);
char		**copy_map(char **map, t_game *game);
int			validate_map(t_game *game, char **map_clone);

// Map Scanning
int			get_next_loop(int fd, char **big_line, int *first_flag,
				t_game *game);
int			check_empty_file(char *line, int *first_flag);
int			scan_map(int fd, t_game *game, char *file);

// File & Filename Utilities
char		*ft_strrchr(const char *s, int c);
int			check_filename(char *file);

// map check funcs 1
size_t		check_top_bot_lines(char *s);
int			check_valid_char(char s, t_game *game, size_t y, size_t x);
int			check_boarders(char c);
int			check_pec_count(t_game *game);

#endif
