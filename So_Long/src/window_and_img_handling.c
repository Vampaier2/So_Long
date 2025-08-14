/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_and_img_handling.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 12:29:12 by xalves            #+#    #+#             */
/*   Updated: 2025/08/14 12:30:15 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

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