/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_func1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:33:15 by xalves            #+#    #+#             */
/*   Updated: 2025/08/11 18:30:54 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

size_t	check_top_bot_lines(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '\n')
	{
		if (s[i] != '1')
			return (1);
		i++;
	}
	return (0);
}

int	check_valid_char(char s, t_game *game, size_t y, size_t x)
{
	if (s == '0' || s == '1' || s == '\n' || s == '\0')
		return (0);
	if (s == 'P')
	{
		game->player_y = y;
		game->player_x = x;
		return (game->player_count++, 0);
	}
	if (s == 'E')
    {
        game->exit_y = y;
        game->exit_x = x;
        return (game->exit_count++, 0);
    }	
	if (s == 'C')
		return (game->cheese_count++, 0);
	return (1);
}

int	check_boarders(char c)
{
	if (c != '1')
		return (1);
	return (0);
}

int	check_pec_count(t_game *game)
{
	if (game->player_count != 1 || game->exit_count != 1)
		return (1);
	if (game->cheese_count < 1)
		return (1);
	return (0);
}
