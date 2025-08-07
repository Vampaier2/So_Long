/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:00:11 by xalves            #+#    #+#             */
/*   Updated: 2025/08/07 18:20:14 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <fcntl.h>
#include <unistd.h>

//------------- Key Actions ---------------
int	close_window(t_game *game)
{
	if (game->tex_loaded && game->player.ptr)
	{
		mlx_destroy_image(game->mlx, game->wall.ptr);
		mlx_destroy_image(game->mlx, game->floor.ptr);
		mlx_destroy_image(game->mlx, game->player.ptr);
		mlx_destroy_image(game->mlx, game->cheese.ptr);
		mlx_destroy_image(game->mlx, game->desumi.ptr);
		mlx_destroy_image(game->mlx, game->mouse_trap.ptr);
	}
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	ft_free_map(game->map);
	exit(0);
}

int	key_press(int key, t_game *game)
{
	if (key == XK_Escape)
		close_window(game);
	return (0);
}

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
	game->cheese_to_get = 0;
}

//---------flood_fill--------------------

void	flood_fill(char **map, int x, int y, t_game *game)
{
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;
	if (map[y][x] == 'C')
		game->cheese_count--;
	if (map[y][x] == 'E')
		game->exit_count--;
	map[y][x] = 'F';
	flood_fill(map, x + 1, y, game);
	flood_fill(map, x - 1, y, game);
	flood_fill(map, x, y + 1, game);
	flood_fill(map, x, y - 1, game);
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
//-----------------------------------------------

size_t	get_num_rows(int fd, size_t rows)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			ft_printf("[EOF]\n");
			free(line);
			break ;
		}
		rows++;
		free(line);
	}
	return (rows);
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
				ft_printf("\nError on side boarder\n");
				return (1);
			}
		}
		else
		{
			if (check_valid_char(game->map[y][x], game, y, x) == 1)
			{
				ft_printf("\nError on inside char\n");
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
		return (ft_printf("\nError Top line lenght\n"), 1);
	game->row_len = top_line_len;
	while (y < game->rows || game->map[y])
	{
		len = ft_linelen(game->map[y]);
		if (len != top_line_len)
			return (ft_printf("\nError DIFERENT len\n"), 1);
		if (y == 0 || y == (game->rows - 1))
        {
			if (check_top_bot_lines(game->map[y]) == 1)
				return (ft_printf("\nError not 1\n"), 1);
		}
        else
            if (cicle_thru_midrows(game, y, top_line_len) == 1)
				return (ft_printf("\nError on mid row\n"), 1);
		y++;
	}
	return (0);
}
///////////////////////////////////////////////////
//			Scan Map Functions

int	check_empty_file(char *line, int *first_flag)
{
	if (line == NULL && *first_flag == 0)
	{
		ft_printf("\n\nError file Empty\n\n");
		return (1);
	}
	else
		(*first_flag)++;
	return (0);
}

int validate_map(t_game *game, char	**map_clone)
{
    if (check_lines(game) == 1)
	{
		ft_printf("\nERROR ON MAP LINES Check!\n");
		return (1);
	}
	if (check_pec_count(game) == 1)
	{
		ft_printf("\nERROR ON MAP PEC count!\n");
		return (1);
	}
	game->cheese_to_get = game->cheese_count;
	map_clone = copy_map(game->map, game);
	flood_fill(map_clone, game->player_x, game->player_y, game);
	if (game->cheese_count != 0 || game->exit_count != 0)
	{
		ft_printf("\nMap is not solvable!\n");
		return (ft_free_map(map_clone), 1);
	}
    ft_free_map(map_clone);
    return (0);
}

int	scan_map(int fd, t_game *game)
{
	char	*line;
	char	*big_line;
	char	*tmp;
	int		first_flag;
	char	**map_clone;

	map_clone = NULL;
	first_flag = 0;
	game->rows = 0;
	big_line = ft_strdup("");
	fd = open("maps/medium_map.ber", O_RDONLY);
	if (fd == -1)
	{
		ft_printf("\n\nError opening map file\n\n");
		return (1);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (check_empty_file(line, &first_flag) == 1)
			return (free(line), free(big_line), 1);
		while (line && ft_strcmp(line, "\n") == 0)
		{
			free(line);
			line = get_next_line(fd);
		}
		if (line == NULL)
			break ;
		tmp = x_strjoin(big_line, line);
		free(big_line);
		big_line = tmp;
		game->rows++;
		free(line);
	}
	game->map = ft_split(big_line, '\n');
	free(line);
	free(big_line);
    //-------------------------
	if (validate_map(game, map_clone) == 1)
        return (ft_printf("\n\nError on map Validation"), 1);
	return (0);
}

int	main(void)
{
	int		fd;
	t_game	game;
	int		i;

	init_game(&game);
	fd = 0;
	if (scan_map(fd, &game) == 1)
		return (ft_free_map(game.map), close(fd), 1);
	close(fd);
	i = 0;
	ft_printf("\n\nPrint Map:\n");
	while (game.map[i] != NULL)
	{
		ft_printf("%s\n", game.map[i]);
		i++;
	}
	game.mlx = mlx_init();
	if (!game.mlx)
		return (1);
	game.win = mlx_new_window(game.mlx, game.row_len * SPRITE_SIZE, game.rows
			* SPRITE_SIZE, "Puto Queijos & o Chedar Proibido");
	if (!game.win)
	{
		close_window(&game);
		return (1);
	}
	// Load textures BEFORE rendering loop
	if (!load_textures(&game))
	{
		close_window(&game);
		return (1);
	}
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_key_hook(game.win, key_press, &game);
	render_frame(&game);
	// mlx_put_image_to_window(game.mlx, game.win, game.player.ptr, 0, 0);
	// mlx_loop_hook(game.mlx, render_frame, &game);
	mlx_loop(game.mlx);
	ft_free_map(game.map);
	return (0);
}

/* ft_printf("\nRows : %d\n", game.rows);
	ft_printf("\nPlayer Count : %d\n", game.player_count);
	ft_printf("\nCheese Count : %d\n", game.cheese_count);
	ft_printf("\nExit Count : %d\n", game.exit_count);
	ft_printf("\nPlayer pos y=%d x=%d\n", game.player_y, game.player_x);
*/

/* 		t_game	game;

	init_game(&game); // Initialize all values
	game.mlx = mlx_init();
	if (!game.mlx)
		return (1);
	game.win = mlx_new_window(game.mlx, 3840, 2160, "so_long");
	if (!game.win)
	{
		close_window(&game);
		return (1);
	}
	// Load textures BEFORE rendering loop
	if (!load_textures(&game))
	{
		close_window(&game);
		return (1);
	}
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_key_hook(game.win, key_press, &game);
	mlx_loop_hook(game.mlx, render_frame, &game);
	mlx_loop(game.mlx);
	return (0);
} */
