/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move_and_input.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 12:25:52 by xalves            #+#    #+#             */
/*   Updated: 2025/08/18 14:39:39 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	key_press(int key, t_game *game)
{
	if (key == XK_Escape)
		close_window(game);
	if (key == 119)
		move_player(game, -1, 0);
	if (key == 97)
		move_player(game, 0, -1);
	if (key == 115)
		move_player(game, 1, 0);
	if (key == 100)
		move_player(game, 0, 1);
	return (0);
}

int	move_player(t_game *game, int y, int x)
{
	game->current_pos = &game->map[game->player_y][game->player_x];
	game->next_pos = &game->map[game->player_y + y][game->player_x + x];
	if (*game->next_pos == '1')
		return (0);
	if (*game->next_pos == '0')
		apply_move(game, y, x);
	if (*game->next_pos == 'C')
	{
		apply_move(game, y, x);
		game->cheese_count--;
	}
	if (*game->next_pos == 'E')
	{
		if (game->cheese_count == 0)
		{
			inc_and_printmove(game);
			close_window(game);
		}
		else
		{
			apply_move(game, y, x);
			game->player_on_exit = 1;
		}
	}
	return (render_frame(game), 1);
}

void	apply_move(t_game *game, int y, int x)
{
	if (game->player_on_exit == 0)
	{
		*game->current_pos = '0';
		*game->next_pos = 'P';
		game->player_y += y;
		game->player_x += x;
	}
	else
	{
		*game->current_pos = 'E';
		*game->next_pos = 'P';
		game->player_y += y;
		game->player_x += x;
		game->player_on_exit = 0;
	}
	inc_and_printmove(game);
}

void	inc_and_printmove(t_game *game)
{
	game->player_moves++;
	ft_printf("Moves: %d", game->player_moves);
	write(1, "\n", 1);
}
