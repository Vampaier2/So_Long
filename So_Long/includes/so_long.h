/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:32:16 by xalves            #+#    #+#             */
/*   Updated: 2025/07/15 17:10:09 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define SPRITE_SIZE 64

typedef struct s_img
{
	void *ptr;    // Image pointer
	int bpp;      // Bits per pixel
	int line_len; // Line length in bytes
	int endian;   // Endianness
}			t_img;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	bool	tex_loaded; // Track if textures are loaded
	t_img	player;    // Player sprite
	t_img	cheese;
	t_img	mouse_trap;
}			t_game;

int			load_textures(t_game *game);
int			render_frame(t_game *game);
void		setup_renderer(t_game *game);

#endif
