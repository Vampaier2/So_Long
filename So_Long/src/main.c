/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:00:11 by xalves            #+#    #+#             */
/*   Updated: 2025/08/13 18:01:07 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <fcntl.h>
#include <unistd.h>

//------------- Game + movement + images Actions ---------------
void	destroy_images(t_game *game)
{
	if (game->wall.ptr != NULL)
		mlx_destroy_image(game->mlx, game->wall.ptr);
	if (game->floor.ptr != NULL)
		mlx_destroy_image(game->mlx, game->floor.ptr);
	if (game->player.ptr != NULL)
		mlx_destroy_image(game->mlx, game->player.ptr);
	if (game->cheese.ptr != NULL)
		mlx_destroy_image(game->mlx, game->cheese.ptr);
	if (game->desumi.ptr != NULL)
		mlx_destroy_image(game->mlx, game->desumi.ptr);
	if (game->desumi_on.ptr != NULL)
		mlx_destroy_image(game->mlx, game->desumi_on.ptr);
	if (game->mouse_trap.ptr != NULL)
		mlx_destroy_image(game->mlx, game->mouse_trap.ptr);
}

int	close_window(t_game *game)
{
	if (game->tex_loaded)
		destroy_images(game);
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

void inc_and_printmove(t_game *game)
{
    game->player_moves++;
    ft_printf("Moves: %d", game->player_moves);
    write(1, "\n", 1);
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

int	key_press(int key, t_game *game)
{
	// printf("%i\n", key);
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

//---------map check--------------------

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
		else if (cicle_thru_midrows(game, y, top_line_len) == 1)
			return (ft_printf("\nError on mid row\n"), 1);
		y++;
	}
	return (0);
}

//------------get variables
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

int	validate_map(t_game *game, char **map_clone)
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
	game->cheese_dupecount = game->cheese_count;
	map_clone = copy_map(game->map, game);
	flood_fill(map_clone, game->player_x, game->player_y, game);
	if (game->cheese_dupecount != 0 || game->exit_count != 0)
	{
		ft_printf("\nMap is not solvable!\n");
		return (ft_free_map(map_clone), 1);
	}
	ft_free_map(map_clone);
	return (0);
}

int	get_next_loop(int fd, char **big_line, int *first_flag, t_game *game)
{
	char	*line;
	char	*tmp;

	line = get_next_line(fd);
	if (check_empty_file(line, first_flag) == 1)
		return (free(line), 1);
	/* while (line && ft_strcmp(line, "\n") == 0)
	{
		free(line);
		line = get_next_line(fd);
	} */
	if (line == NULL)
		return (0);
	tmp = x_strjoin(*big_line, line);
	free(*big_line);
	*big_line = tmp;
	game->rows++;
	free(line);
	return (2);
}

int	scan_map(int fd, t_game *game, char *file)
{
	char	*big_line;
	int		first_flag;
	int		loop_result;

	file = ft_strjoin("maps/", file);
	big_line = ft_strdup("");
	first_flag = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("\n\nError opening map file\n\n");
		return (free(big_line), free(file), close(fd), 1);
	}
	while (1)
	{
		loop_result = get_next_loop(fd, &big_line, &first_flag, game);
		if (loop_result == 1)
			return (free(big_line), free(file), close(fd), 1);
		if (loop_result == 0)
			break ;
	}
	game->map = ft_split(big_line, '\n');
	if (validate_map(game, NULL) == 1)
		return (ft_printf("\n\nError on map Validation"), free(big_line), free(file), close(fd), 1);
	return (free(big_line), free(file), close(fd), 0);
}

void	mlx_and_input(t_game *game)
{
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_key_hook(game->win, key_press, game);
	render_frame(game);
	mlx_loop(game->mlx);
}
//---------------------------------------------

int check_filename(char *file)
{
    
    return(0);
}

//---------------------------------------------

int setup_game(t_game *game, char *map_file)
{
	int fd = 0;

	init_game(game);
	if (scan_map(fd, game, map_file) == 1)
		return (ft_free_map(game->map), close(fd), 1);
	close(fd);
	return (0);
}

int setup_graphics(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (1);
	if (load_textures(game) == 1)
		return (ft_printf("Error loading textures\n"), close_window(game), 1);
	game->win = mlx_new_window(game->mlx, game->row_len * SPRITE_SIZE,
			game->rows * SPRITE_SIZE, "Puto Queijos & o Chedar Proibido");
	if (!game->win)
		return (close_window(game), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (ft_printf("Error on Inputs!!\n"), 0);
	if (check_filename(argv[1]) == 1)
		return (1);
    if (setup_game(&game, argv[1]) == 1)
		return (1);
	if (setup_graphics(&game) == 1)
		return (1);
	mlx_and_input(&game);
	ft_free_map(game.map);
	return (0);
}



/* int	main(int argc, char **argv)
{
	int		fd;
	t_game	game;

	if (argc != 2)
		return (ft_printf("Error on Inputs!!\n"), 0);
	else
	{
		init_game(&game);
		fd = 0;
		if (scan_map(fd, &game, argv[1]) == 1)
			return (ft_free_map(game.map), close(fd), 1);
		close(fd);
		game.mlx = mlx_init();
		if (!game.mlx)
			return (1);
		if (load_textures(&game) == 1)
			return (ft_printf("Error loading textures\n"), close_window(&game),	1);
		game.win = mlx_new_window(game.mlx, game.row_len * SPRITE_SIZE,
				game.rows * SPRITE_SIZE, "Puto Queijos & o Chedar Proibido");
		if (!game.win)
			return (close_window(&game), 1);
		mlx_and_input(&game);
		ft_free_map(game.map);
	}
	return (0);
} */
