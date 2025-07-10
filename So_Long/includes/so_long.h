/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:32:16 by xalves            #+#    #+#             */
/*   Updated: 2025/07/10 17:30:06 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
#include <stdbool.h>
# include <../minilibx-linux/mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>

#define SPRITE_SIZE 64

typedef struct s_img {
    void    *ptr;       // Image pointer
    int     bpp;        // Bits per pixel
    int     line_len;   // Line length in bytes
    int     endian;     // Endianness
} t_img;

typedef struct s_game {
    void    *mlx;
    void    *win;
    bool    tex_loaded;  // Track if textures are loaded
    t_img   player;     // Player sprite
} t_game;


int     render_frame(t_game *game);  // int instead of void
void	setup_renderer(t_game *game);

#endif
