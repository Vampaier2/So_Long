/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:00:11 by xalves            #+#    #+#             */
/*   Updated: 2025/08/06 15:26:24 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <fcntl.h>
#include <unistd.h>


/* 
----- MAP ---------
- check_top_bot_lines
- check_valid_char
- check_boarders
- check_pec_count
- flood_fill
----------------------
- copy_map

- get_num_rows

----------------
- check_lines
- scan_map
-------------------

*/
//------------- Key Actions ---------------
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
//-----------------------------------------
// Initialize game values
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
}

//--------- MAP ANALISIS --------------------


//---------flood_fill--------------------

void flood_fill(char **map, int x, int y, t_game *game)
{
	//ft_printf("\n\nEntered flood field\n\n");
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

char **copy_map(char **map, t_game *game)
{
    size_t i;
	size_t j;
	char **copy;
	
	i = 0;
    copy = ft_calloc((game->rows + 1), sizeof(char *));
    if (!copy)
        return NULL;
    while (i < game->rows)
    {
        copy[i] = ft_strdup(map[i]);
        if (!copy[i])
        {
            j = 0;
            while (j < i)
                free(copy[j++]);
            free(copy);
            return NULL;
        }
        i++;
    }
    copy[i] = NULL; // Null-terminate
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
/////////////////////////////////////////////////////////////////

int	check_lines(t_game *game)
{
	//char	*line;
	size_t	top_line_len;
	size_t	len;
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	top_line_len = ft_linelen(game->map[y]);
	if (!top_line_len)
	{
		ft_printf("\nError Top line lenght\n");
		return (1);
	}
	//------------------------------
	while (y < game->rows || game->map[y])
	{
		len = ft_linelen(game->map[y]);
		if (len != top_line_len)
		{
			ft_printf("\nError DIFERENT len\n");
			return (1);
		}
		if (y == 0 || y == (game->rows - 1))
		{
			if (check_top_bot_lines(game->map[y]) == 1)
			{
				ft_printf("\nError not 1\n");
				return (1);
			}
		}
		else
		{
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
		}
		x = 0;
		y++;
	}
	return (0);
}
///////////////////////////////////////////////////
//			Scan Map Functions

int check_empty_file(char *line, int *first_flag)
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



int	scan_map(int fd, t_game *game)
{
	char	*line;
	char	*big_line;
	char	*tmp;
    int     first_flag;
	char	**map_clone;

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
            break;
		tmp = x_strjoin(big_line, line);
		free(big_line);
		big_line = tmp;
		game->rows++;
		free(line);
	}
	game->map = ft_split(big_line, '\n');
    free(line);
	free(big_line);
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
	map_clone = copy_map(game->map, game);
	//ft_printf("\n\nBefore flood fill: cheese = %d, exit = %d\n", game->cheese_count, game->exit_count);
	flood_fill(map_clone, game->player_x, game->player_y, game);
	//ft_printf("\n\nAfter flood fill: cheese = %d, exit = %d\n", game->cheese_count, game->exit_count);
	 if (game->cheese_count != 0 || game->exit_count != 0)
    {
        ft_printf("\nMap is not solvable!\n");
        return (1);
    }
	ft_free_map(map_clone);
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
	i = 0;
	ft_printf("\n\nPrint Map:\n");
	while (game.map[i] != NULL)
	{
		ft_printf("%s\n", game.map[i]);
		i++;
	}
	/* ft_printf("\nRows : %d\n", game.rows);
	ft_printf("\nPlayer Count : %d\n", game.player_count);
	ft_printf("\nCheese Count : %d\n", game.cheese_count);
	ft_printf("\nExit Count : %d\n", game.exit_count);
	ft_printf("\nPlayer pos y=%d x=%d\n", game.player_y, game.player_x); */

	ft_free_map(game.map);
	close(fd);
	return (0);
}
/* 		t_game	data;

	init_game(&data); // Initialize all values
	data.mlx = mlx_init();
	if (!data.mlx)
		return (1);
	data.win = mlx_new_window(data.mlx, 3840, 2160, "so_long");
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
} */
/*
	int		fd;
	char	*line;
	int		count;
	size_t	rows;
	size_t	len;
	size_t	digits;

	count = 0;
	rows = 0;
	len = 0;
	digits = 0;
	fd = open("maps/map.txt", O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error opening file");
		return (1);
	}
	while (1)
	{
		line = get_next_line(fd);
		len = ft_linelen(line);
		if (line == NULL)
		{
			ft_printf("[EOF]: get_next_line returned NULL\n");
			break ;
		}
		rows++;
		digits += len;
		count++;
		ft_printf("len: %zu| [%d]:%s", len,count, line);
		free(line);
	}
	ft_printf("\n\n[rows]:%zu \n[digits]:%zu", rows, (digits - rows));
	close(fd);
	return (0);
}

*/
