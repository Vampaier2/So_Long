/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:00:11 by xalves            #+#    #+#             */
/*   Updated: 2025/07/22 16:36:38 by xalves           ###   ########.fr       */
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

size_t	ft_linerun(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	return (i);
}

int	scan_map(int fd, t_game *data)
{
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
		printf("Error opening map file");
		return (1);
	}
	while (1)
	{
		line = get_next_line(fd);
		len = ft_linelen(line);
		if (line == NULL)
		{
			printf("[EOF]\n");
			break ;
		}
		rows++;
		digits += len;
		count++;
		printf("len: %zu| [%d]:  %s", len, count, line);
		free(line);
	}
	printf("\n\n[rows]:%zu \n[digits+0+n]:%zu", rows, digits);
	return(0);
}

int	main(void)
{
	int	fd;
	t_game	data;

	init_game(&data);
	fd = 0;
	if (!scan_map(fd, &data))
		return(1);
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
