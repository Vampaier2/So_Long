/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:00:11 by xalves            #+#    #+#             */
/*   Updated: 2025/07/25 16:04:23 by xalves           ###   ########.fr       */
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
	game->player.line_len = 0;
	game->player.endian = 0;
}

void	ft_free_map(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
		free(map[i++]);
	free(map);
}

char	*x_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen((char *)s1);
	s2_len = ft_strlen((char *)s2);
	new_str = ft_calloc(s1_len + s2_len + 1, sizeof(char));
	// calloc instead of malloc
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < s1_len && s1[i])
	{
		new_str[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < s2_len && s2[i])
	{
		new_str[s1_len + i] = s2[i];
		i++;
	}
	return (new_str);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (1)
	{
		if (s1[i] == '\0' && s2[i] == '\0')
		{
			return (0);
		}
		if (s1[i] == '\0' || s2[i] == '\0')
		{
			return (s1[i] - s2[i]);
		}
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
}

size_t	check_top_bot_lines(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '\n')
	{
		// printf("\n%c", s[i]);
		if (s[i] != '1')
			return (1);
		i++;
	}
	return (0);
}
//---------MID SECTION--------------------
int	check_valid_char(char s)
{
	if (s == '0' || s == '1' || s == 'P' || s == 'E' || s == 'C' || s == '\n'
		|| s == '\0')
		return (0);
	return (1);
}

int	check_boarders(char c)
{
	if (c != '1')
		return (1);
	return (0);
}
//-----------------------------
size_t	get_num_rows(int fd, size_t rows)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			printf("[EOF]\n");
			free(line);
			break ;
		}
		rows++;
		free(line);
	}
	return (rows);
}

int	check_lines(t_game *game)
{
	char	*line;
	size_t	top_line_len;
	size_t	len;
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	top_line_len = ft_linelen(game->map[y]);
	if (!top_line_len)
	{
		printf("\nError Top line lenght\n");
		return (1);
	}
	//------------------------------
	while (y < game->rows || game->map[y])
	{
		line = game->map[y];
		len = ft_linelen(game->map[y]);
		if (len != top_line_len)
		{
			printf("\nError DIFERENT len\n");
			return (1);
		}
		if (y == 0 || y == (game->rows - 1))
		{
			if (check_top_bot_lines(game->map[y]) == 1)
			{
				printf("\nError not 1\n");
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
						printf("\nError on side boarder\n");
						return (1);
					}
				}
				else
				{
					if (check_valid_char(game->map[y][x]) == 1)
					{
						printf("\nError on inside char\n");
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

int	scan_map(int fd, t_game *game)
{
	size_t	top_line_len;
	size_t	len;
	char	*line;
	char	*big_line;
	size_t	digits;
	char	*tmp;
    int     first_flag;

    first_flag = 0;
	game->rows = 0;
	len = 0;
	digits = 0;
	top_line_len = 0;
	big_line = ft_strdup("");
	fd = open("maps/map.ber", O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening map file");
		return (1);
	}
	while (1)
	{
		line = get_next_line(fd);
        if (line == NULL && first_flag == 0)
        {
		    printf("Error file Empty");
            break;
        }
        else
            first_flag++;
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
		printf("\nERROR ON MAP LINES Check!\n");
		return (1);
	}
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
	printf("\n\nPrint Map:\n");
	while (game.map[i] != NULL)
	{
		printf("%s\n", game.map[i]);
		i++;
	}
	printf("\nRows : %zu\n", game.rows);
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
		printf("Error opening file");
		return (1);
	}
	while (1)
	{
		line = get_next_line(fd);
		len = ft_linelen(line);
		if (line == NULL)
		{
			printf("[EOF]: get_next_line returned NULL\n");
			break ;
		}
		rows++;
		digits += len;
		count++;
		printf("len: %zu| [%d]:%s", len,count, line);
		free(line);
	}
	printf("\n\n[rows]:%zu \n[digits]:%zu", rows, (digits - rows));
	close(fd);
	return (0);
}

*/
