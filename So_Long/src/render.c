/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:57:12 by xalves            #+#    #+#             */
/*   Updated: 2025/08/19 11:27:36 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	*generate_img_ptr(t_game *game, char *xpm_src)
{
	int		size;
	void	*ptr;

	size = SPRITE_SIZE;
	ptr = mlx_xpm_file_to_image(game->mlx, xpm_src, &size, &size);
	if (!ptr)
	{
		ft_printerror("Error\n On loading texture: %s\n", xpm_src);
		ptr = NULL;
	}
	return (ptr);
}

int	load_textures(t_game *game)
{
	game->wall.ptr = generate_img_ptr(game, "textures/wall.xpm");
	game->floor.ptr = generate_img_ptr(game, "textures/floor.xpm");
	game->player.ptr = generate_img_ptr(game, "textures/david.xpm");
	game->cheese.ptr = generate_img_ptr(game, "textures/Cheese.xpm");
	game->desumi.ptr = generate_img_ptr(game, "textures/desumi_off.xpm");
	game->desumi_on.ptr = generate_img_ptr(game, "textures/desumi_on.xpm");
	game->mouse_trap.ptr = generate_img_ptr(game, "textures/mouse_trap.xpm");
	game->tex_loaded = true;
	if (!game->wall.ptr || !game->floor.ptr || !game->player.ptr
		|| !game->cheese.ptr || !game->desumi.ptr || !game->desumi_on.ptr
		|| !game->mouse_trap.ptr)
	{
		ft_printerror("Error\n Failed to load texture files.\n");
		return (1);
	}
	return (0);
}

int	render_frame(t_game *game)
{
	int		x;
	int		y;
	char	*moves_txt;

	x = 0;
	y = 0;
	while (game->map[y])
	{
		while (game->map[y][x] != '\0')
		{
			ft_put_image(game, game->map[y][x], x, y);
			x++;
		}
		if (game->map[y] == NULL)
			break ;
		x = 0;
		y++;
	}
	moves_txt = ft_itoa(game->player_moves);
	mlx_string_put(game->mlx, game->win, 16, 32, 0x000000, "Moves: ");
	mlx_string_put(game->mlx, game->win, 52, 32, 0x000000, moves_txt);
	return (free(moves_txt), 0);
}

void	ft_put_image(t_game *game, char c, int x, int y)
{
	if (c == '1')
		mlx_put_image_to_window(game->mlx, game->win, game->wall.ptr, x
			* SPRITE_SIZE, y * SPRITE_SIZE);
	if (c == '0')
		mlx_put_image_to_window(game->mlx, game->win, game->floor.ptr, x
			* SPRITE_SIZE, y * SPRITE_SIZE);
	if (c == 'P')
		mlx_put_image_to_window(game->mlx, game->win, game->player.ptr, x
			* SPRITE_SIZE, y * SPRITE_SIZE);
	if (c == 'C')
		mlx_put_image_to_window(game->mlx, game->win, game->cheese.ptr, x
			* SPRITE_SIZE, y * SPRITE_SIZE);
	if (c == 'E')
	{
		if (game->cheese_count != 0)
			mlx_put_image_to_window(game->mlx, game->win, game->desumi.ptr, x
				* SPRITE_SIZE, y * SPRITE_SIZE);
		else
		{
			mlx_put_image_to_window(game->mlx, game->win, game->desumi_on.ptr, x
				* SPRITE_SIZE, y * SPRITE_SIZE);
		}
	}
}
