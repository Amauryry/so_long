/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:07:23 by aberion           #+#    #+#             */
/*   Updated: 2024/06/03 16:57:29 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/src/ft_printf.h"
#include "minilibx-linux/mlx.h"
#include "so_long.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

int	close_window(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	free_resources(game);
	exit(0);
	return (0);
	return (0);
}

void	draw_tile(t_game *game, int i, int j)
{
	if (game->map->map[i][j] == '0')
		mlx_put_image_to_window(game->mlx->mlx_p, game->mlx->win_p,
			game->mlx->assets.grass, j * 80, i * 60);
	else if (game->map->map[i][j] == 'E' && (game->info->x == i
			&& game->info->y == j))
		mlx_put_image_to_window(game->mlx->mlx_p, game->mlx->win_p,
			game->mlx->assets.chara, j * 80, i * 60);
	else if (game->map->map[i][j] == '1')
		mlx_put_image_to_window(game->mlx->mlx_p, game->mlx->win_p,
			game->mlx->assets.wall, j * 80, i * 60);
	else if (game->map->map[i][j] == 'C')
		mlx_put_image_to_window(game->mlx->mlx_p, game->mlx->win_p,
			game->mlx->assets.coin, j * 80, i * 60);
	else if (game->map->map[i][j] == 'E')
		mlx_put_image_to_window(game->mlx->mlx_p, game->mlx->win_p,
			game->mlx->assets.exit, j * 80, i * 60);
	else if (game->map->map[i][j] == 'P')
		mlx_put_image_to_window(game->mlx->mlx_p, game->mlx->win_p,
			game->mlx->assets.chara, j * 80, i * 60);
}

void	draw_map(t_game *game)
{
	int		i;
	int		j;
	char	*move;

	i = 0;
	while (i < game->map->rows)
	{
		j = 0;
		while (j < game->map->cols)
		{
			draw_tile(game, i, j);
			j++;
		}
		i++;
	}
	move = ft_itoa(game->info->count_move);
	mlx_string_put(game->mlx->mlx_p, game->mlx->win_p, 10, 20, 0xFF0000, move);
	free(move);
}

int	check_screen_size(t_mlx *mlx, int map_cols, int map_rows)
{
	int	screen_width;
	int	screen_height;

	mlx_get_screen_size(mlx->mlx_p, &screen_width, &screen_height);
	if (80 * map_cols > screen_width || 60 * map_rows > screen_height)
	{
		perror("Error\nSize matters (");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_game	*game;

	if (env == NULL || *env == NULL)
		exit(EXIT_FAILURE);
	if (check_and_init(argc, argv, &game) != 0)
		return (1);
	init_map(argv, game->map);
	load_images(game);
	init_info(game);
	if (check_screen_size(game->mlx, game->map->cols, game->map->rows) != 0)
		return (free_resources(game), 1);
	game->mlx->win_p = mlx_new_window(game->mlx->mlx_p, 80 * game->map->cols, 60
			* game->map->rows, "So_long");
	if (!game->mlx->win_p)
	{
		free_resources(game);
		return (1);
	}
	draw_map(game);
	mlx_hook(game->mlx->win_p, 17, 0, close_window, game);
	mlx_key_hook(game->mlx->win_p, key_press, game);
	mlx_loop(game->mlx->mlx_p);
	return (0);
}
