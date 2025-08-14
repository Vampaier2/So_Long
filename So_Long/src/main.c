/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:00:11 by xalves            #+#    #+#             */
/*   Updated: 2025/08/14 14:03:55 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <fcntl.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (ft_printerror("Error on Inputs!!\n"), 0);
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
