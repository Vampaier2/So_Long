/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:57:12 by xalves            #+#    #+#             */
/*   Updated: 2025/07/11 16:31:51 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int load_textures(t_game *game)
{
    game->player.ptr = mlx_xpm_file_to_image(
        game->mlx,
        "assets/david.xpm",
        &(int){SPRITE_SIZE},
        &(int){SPRITE_SIZE}
    );
    
    if (!game->player.ptr) {
        printf("Error loading texture\n");
        return (0);
    }
    
    mlx_get_data_addr(
        game->player.ptr,
        &game->player.bpp,
        &game->player.line_len,
        &game->player.endian
    );
    
    game->tex_loaded = true;
    return (1);
}

int render_frame(t_game *game)
{
    mlx_clear_window(game->mlx, game->win);
    mlx_put_image_to_window(game->mlx, game->win, game->player.ptr, 0, 0);
    return (0);
}

void	setup_renderer(t_game *game)
{
	mlx_loop_hook(game->mlx, render_frame, game);
}