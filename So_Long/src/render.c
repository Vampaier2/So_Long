/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:57:12 by xalves            #+#    #+#             */
/*   Updated: 2025/07/23 12:52:16 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	*generate_img_ptr(t_game *game, char *xpm_src)
{
	int	size;
	void *ptr;

	size = SPRITE_SIZE;
	ptr = mlx_xpm_file_to_image(game->mlx, xpm_src, &size, &size);
	if (!ptr)
		printf("Error loading texture: %s\n", xpm_src);
	return (ptr);
}

int	load_textures(t_game *game)
{
	game->player.ptr = generate_img_ptr(game, "assets/david.xpm");
	game->cheese.ptr = generate_img_ptr(game, "assets/Cheese.xpm");
	game->mouse_trap.ptr = generate_img_ptr(game, "assets/mouse_trap.xpm");
	game->tex_loaded = true;
	return (1);
}

/*
** Convert an xpm file to a new image instance.
**
** @param	void *mlx_ptr	the mlx instance;
** @param	char *filename	the file to load;
** @param	int  *width		a pointer to where the width ought to be written;
** @param	int  *height	a pointer to where the height ought to be written;
** @return	void*			the image instance, and NULL in case of error.
*/
//void	*mlx_xpm_file_to_image(void *mlx_ptr, char *filename, int *width, int *height);


int	render_frame(t_game *game)
{
	//int	x = 0, y = 0;
	mlx_clear_window(game->mlx, game->win);
	/* while (y <= 2160)
	{
		while (x <= 3840)
		{
			mlx_put_image_to_window(game->mlx, game->win, game->cheese.ptr, x, y);
			x +=64;
		}
		x = 0;
		y += 64;
	} */

	mlx_put_image_to_window(game->mlx, game->win, game->player.ptr, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->cheese.ptr, 64, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->mouse_trap.ptr, 0, 64);
	return (0);
}

void	setup_renderer(t_game *game)
{
	mlx_loop_hook(game->mlx, render_frame, game);
}
