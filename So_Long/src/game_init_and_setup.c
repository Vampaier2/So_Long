/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init_and_setup.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 12:19:15 by xalves            #+#    #+#             */
/*   Updated: 2025/08/19 11:20:48 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->tex_loaded = false;
	game->player.ptr = NULL;
	game->player.bpp = 0;
	game->map = NULL;
	game->player.line_len = 0;
	game->player.endian = 0;
	game->player_count = 0;
	game->cheese_count = 0;
	game->exit_count = 0;
	game->cheese_dupecount = 0;
	game->rows = 0;
	game->exit_x = 0;
	game->exit_y = 0;
	game->player_on_exit = 0;
	game->player_moves = 0;
}

int	setup_game(t_game *game, char *map_file)
{
	int	fd;

	fd = 0;
	init_game(game);
	if (scan_map(fd, game, map_file) == 1)
		return (ft_free_map(game->map), close(fd), 1);
	close(fd);
	return (0);
}

int	setup_graphics(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (1);
	if (load_textures(game) == 1)
		return (ft_printerror("Error\n On loading textures\n"),
			close_window(game), 1);
	game->win = mlx_new_window(game->mlx, game->row_len * SPRITE_SIZE,
			game->rows * SPRITE_SIZE, "Puto Queijos & o Chedar Proibido");
	if (!game->win)
		return (close_window(game), 1);
	return (0);
}

void	mlx_and_input(t_game *game)
{
	mlx_hook(game->win, KeyPress, KeyPressMask, key_press, game);
	mlx_hook(game->win, 17, 0, close_window, game);
	render_frame(game);
	mlx_loop(game->mlx);
}
