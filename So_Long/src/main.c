/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:00:11 by xalves            #+#    #+#             */
/*   Updated: 2025/07/16 16:32:32 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// Close window gracefully
int	close_window(t_game *game)
{
	if (game->tex_loaded && game->player.ptr)
	{
		mlx_destroy_image(game->mlx, game->player.ptr);
		mlx_destroy_image(game->mlx, game->cheese.ptr);
		mlx_destroy_image(game->mlx, game->mouse_trap.ptr);
	}
		if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
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

// Add this initialization function
void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->tex_loaded = false;
	game->player.ptr = NULL;
	game->player.bpp = 0;
	game->player.line_len = 0;
	game->player.endian = 0;
}

int	main(void)
{
	t_game	data;

	init_game(&data); // Initialize all values
	data.mlx = mlx_init();
	if (!data.mlx)
		return (1);
	data.win = mlx_new_window(data.mlx, 1280, 720, "so_long");
	if (!data.win)
	{
		close_window(&data);
		return (1);
	}
	// Load textures BEFORE rendering loop
	if (!load_textures(&data))
	{
		close_window(&data);
		return (1);
	}
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_key_hook(data.win, key_press, &data);
	mlx_loop_hook(data.mlx, render_frame, &data);
	mlx_loop(data.mlx);
	return (0);
}
