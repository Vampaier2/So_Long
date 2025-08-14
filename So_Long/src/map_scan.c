/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_scan.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 12:37:56 by xalves            #+#    #+#             */
/*   Updated: 2025/08/14 12:39:15 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

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

int	check_empty_file(char *line, int *first_flag)
{
	if (line == NULL && *first_flag == 0)
	{
		ft_printerror("\n\nError file Empty\n\n");
		return (1);
	}
	else
		(*first_flag)++;
	return (0);
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
		ft_printerror("\n\nError opening map file\n\n");
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
		return (ft_printerror("\n\nError on map Validation"), free(big_line), free(file), close(fd), 1);
	return (free(big_line), free(file), close(fd), 0);
}

