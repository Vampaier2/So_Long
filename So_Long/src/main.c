/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:00:11 by xalves            #+#    #+#             */
/*   Updated: 2025/07/10 17:31:33 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Close window gracefully
int close_window(t_game *game)
{
    if (game->tex_loaded && game->player.ptr)
        mlx_destroy_image(game->mlx, game->player.ptr);
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
    if (game->mlx) {
        mlx_destroy_display(game->mlx);
        free(game->mlx);
    }
    exit(0);
}

int	key_press(int key, t_game *game)
{
	if (key == XK_Escape)
		close_window(game);
	return (0);
}

int main(void)
{
    t_game data;

    // Initialize MLX
    data.mlx = mlx_init();
    if (!data.mlx) return (1);
    
    // Create window
    data.win = mlx_new_window(data.mlx, 1280, 720, "so_long");
    if (!data.win) {
        close_window(&data);
        return (1);
    }
    
    // Initialize renderer <<<
    setup_renderer(&data);
    
    // Set up hooks(key press)
    mlx_hook(data.win, 17, 0, close_window, &data);
    mlx_key_hook(data.win, key_press, &data);
    
    // Start main loop
    mlx_loop(data.mlx);
    return (0);
}

