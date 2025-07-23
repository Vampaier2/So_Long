/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:00:11 by xalves            #+#    #+#             */
/*   Updated: 2025/07/23 17:54:58 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <fcntl.h>
#include <unistd.h>

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

void	ft_free_map(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
		free(map[i++]);
	free(map);
}

size_t	check_top_bot_lines(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '\n')
	{
		printf("\n%c", s[i]);
		if (s[i] != '1')
			return (1);
		i++;
	}
	return (0);
}

int	check_boarders(char *line, size_t len)
{
	if (line[0] != '1' || line[len - 1] != '1')
		return (1);
	return (0);
}

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

int	check_lines(int fd)
{
	char	*line;
	size_t	top_line_len;
	size_t	len;

	//---- Get first line len ------
	line = get_next_line(fd);
	top_line_len = ft_linelen(line);
	if (line == NULL)
	{
		printf("\nError NULL\n");
		free(line);
		return (1);
	}
	if (check_top_bot_lines(line) == 1)
	{
		printf("\nError not 1\n");
		free(line);
		return (1);
	}
	free(line);
	//------------------------------
	while (1)
	{
		line = get_next_line(fd);
		printf("\nline = %s", line);
		if (line == NULL)
		{
			printf("[EOF]\n");
			free(line);
			break ;
			// return(0);
		}
		len = ft_linelen(line);
		if (len != top_line_len)
		{
			printf("\nError DIFERENT len\n");
			free(line);
			return (1);
		}
		/* if (check_boarders(line, len) == 1)
		{
			printf("\nError on boarder\n");
			free(line);
			return(1) ;
		} */
		if (get_next_line(fd) == NULL)
		{
			if (check_top_bot_lines(line) == 1)
			{
				printf("\nError not 1\n");
				free(line);
				return (1);
			}
			free(line);
		}
		free(line);
	}
	free(line);
	return (0);
}

int	scan_map(int fd, t_game *game)
{
	size_t	top_line_len;
	size_t	len;
	char	*line;
	char	*big_line;
	size_t	digits;

	game->rows = 0;
	len = 0;
	digits = 0;
	top_line_len = 0;
	big_line = NULL;
	fd = open("maps/map.ber", O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening map file");
		return (1);
	}
	/* if (check_lines(fd) == 1)
	{
		printf("\nERROR ON MAP LINES!\n");
		return (1);
	} */
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			printf("[EOF]\n");
			break ;
		}
		big_line = ft_strjoin(big_line, line);
		len = ft_linelen(line);
		digits += len;
		game->rows++;
		// printf("%s", line);
		free(line);
	}
	game->map = ft_split(big_line, '\n');
	free(big_line);
	// printf("\n\n[rows]:%zu \n[digits+0+n]:%zu \n\n", rows, digits);
	return (0);
}

int	main(void)
{
	int		fd;
	t_game	data;

	init_game(&data);
	fd = 0;
	if (scan_map(fd, &data) == 1)
		return (1);
	printf("\nRows : %zu\n", data.rows);
	ft_free_map(data.map);
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
