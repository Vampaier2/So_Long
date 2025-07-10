/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:57:12 by xalves            #+#    #+#             */
/*   Updated: 2025/07/10 17:55:18 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	render_frame(t_game *game)
{
	if (!game->tex_loaded)
    {
        // Load XPM image file
        game->player.ptr = mlx_xpm_file_to_image(
            game->mlx,                  // MLX connection
            "assets/david.xpm",         // Player sprite path
            &(int){SPRITE_SIZE},        // Verify width=64px
            &(int){SPRITE_SIZE}         // Verify height=64px
        );
        
        // Error handling
        if (!game->player.ptr) {
            printf("Error: Failed to load image\n");
            exit(1);
        }
        
        // Get image memory layout
        mlx_get_data_addr(
            game->player.ptr,
            &game->player.bpp,          // Bits per pixel (usually 32)
            &game->player.line_len,     // Bytes per row (64px * 4 bytes)
            &game->player.endian        // CPU byte order (0=big, 1=little)
        );
        
        game->tex_loaded = true;  // Mark as loaded
    }
	mlx_clear_window(game->mlx, game->win);         // Clear previous frame
    mlx_put_image_to_window(game->mlx, game->win, game->player.ptr, 0, 0);  // Draw at top-left corner (0,0)
    return(0);
}

void	setup_renderer(t_game *game)
{
	mlx_loop_hook(game->mlx, render_frame, game);
}