/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapvalid_flood_and_boarder.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 12:32:32 by xalves            #+#    #+#             */
/*   Updated: 2025/08/19 10:17:07 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	flood_fill(char **map, int x, int y, t_game *game)
{
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;
	if (map[y][x] == 'C')
		game->cheese_dupecount--;
	if (map[y][x] == 'E')
		game->exit_count--;
	map[y][x] = 'F';
	flood_fill(map, x + 1, y, game);
	flood_fill(map, x - 1, y, game);
	flood_fill(map, x, y + 1, game);
	flood_fill(map, x, y - 1, game);
}

int	cicle_thru_midrows(t_game *game, int y, int top_line_len)
{
	int	x;

	x = 0;
	while (x < top_line_len)
	{
		if (x == 0 || x == top_line_len - 1)
		{
			if (check_boarders(game->map[y][x]) == 1)
			{
				ft_printerror("Error\n On side boarder\n");
				return (1);
			}
		}
		else
		{
			if (check_valid_char(game->map[y][x], game, y, x) == 1)
			{
				ft_printerror("Error\n On inside char\n");
				return (1);
			}
		}
		x++;
	}
	return (0);
}

int	check_lines(t_game *game)
{
	size_t	top_line_len;
	size_t	len;
	size_t	y;

	y = 0;
	top_line_len = ft_linelen(game->map[y]);
	if (!top_line_len)
		return (ft_printerror("Error\n On Top line lenght\n"), 1);
	game->row_len = top_line_len;
	while (y < game->rows || game->map[y])
	{
		len = ft_linelen(game->map[y]);
		if (len != top_line_len)
			return (ft_printerror("Error\n DIFERENT line len\n"), 1);
		if (y == 0 || y == (game->rows - 1))
		{
			if (check_top_bot_lines(game->map[y]) == 1)
				return (ft_printerror("Error\n not 1\n"), 1);
		}
		else if (cicle_thru_midrows(game, y, top_line_len) == 1)
			return (ft_printerror("Error\n On mid row\n"), 1);
		y++;
	}
	return (0);
}

char	**copy_map(char **map, t_game *game)
{
	size_t	i;
	size_t	j;
	char	**copy;

	i = 0;
	copy = ft_calloc((game->rows + 1), sizeof(char *));
	if (!copy)
		return (NULL);
	while (i < game->rows)
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
		{
			j = 0;
			while (j < i)
				free(copy[j++]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

int	validate_map(t_game *game, char **map_clone)
{
	if (check_lines(game) == 1)
	{
		ft_printerror("Error\n ON MAPVALID LINES Check!\n");
		return (1);
	}
	if (check_pec_count(game) == 1)
	{
		ft_printerror("Error\n ON MAPVALID PEC count!\n");
		return (1);
	}
	game->cheese_dupecount = game->cheese_count;
	map_clone = copy_map(game->map, game);
	flood_fill(map_clone, game->player_x, game->player_y, game);
	if (game->cheese_dupecount != 0 || game->exit_count != 0)
	{
		ft_printerror("Error\n Map is not solvable!\n");
		return (ft_free_map(map_clone), 1);
	}
	ft_free_map(map_clone);
	return (0);
}
