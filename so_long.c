/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:07:23 by aberion           #+#    #+#             */
/*   Updated: 2024/05/27 13:36:49 by aberion          ###   ########.fr       */
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

void	move_player(t_game *game, int move_x, int move_y)
{
	int		new_x;
	int		new_y;
	int		gang;
	char	target_tile;

	new_x = game->info->x + move_x;
	new_y = game->info->y + move_y;
	gang = 0;
	if (new_x >= 0 && new_x < game->map->rows && new_y >= 0
		&& new_y < game->map->cols && game->map->map[new_x][new_y] != '1')
	{
		game->info->count_move++;
		ft_printf("%d\n", game->info->count_move);
		target_tile = game->map->map[new_x][new_y];
		if (target_tile == 'C')
			game->info->left_items--;
		if (target_tile == 'E' && game->info->left_items == 0)
			close_window(game);
		if (target_tile == 'E')
			gang++;
		if (game->map->map[game->info->x][game->info->y] != 'E')
			game->map->map[game->info->x][game->info->y] = '0';
		game->info->x = new_x;
		game->info->y = new_y;
		game->map->map[game->info->x][game->info->y] = 'P';
		mlx_clear_window(game->mlx->mlx_p, game->mlx->win_p);
		draw_map(game);
		if (gang != 0)
			game->map->map[game->info->x][game->info->y] = 'E';
	}
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == ESC_KEY)
		close_window(game);
	else if (keycode == KEY_UP)
		move_player(game, -1, 0);
	else if (keycode == KEY_DOWN)
		move_player(game, 1, 0);
	else if (keycode == KEY_LEFT)
		move_player(game, 0, -1);
	else if (keycode == KEY_RIGHT)
		move_player(game, 0, 1);
	return (0);
}

void	draw_map(t_game *game)
{
	char	*move;

	int i, j;
	i = 0;
	while (i < game->map->rows)
	{
		j = 0;
		while (j < game->map->cols)
		{
			if (game->map->map[i][j] == '0')
				mlx_put_image_to_window(game->mlx->mlx_p, game->mlx->win_p,
					game->mlx->assets.grass, j * 80, i * 60);
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
			j++;
		}
		i++;
	}
	move = ft_itoa(game->info->count_move);
	mlx_string_put(game->mlx->mlx_p, game->mlx->win_p, 10, 20, 0xFF0000, move);
	free(move);
}

void	load_images(t_mlx *mlx)
{
	mlx->assets.grass = mlx_xpm_file_to_image(mlx->mlx_p, "assets/grass.xpm",
			&mlx->width, &mlx->height);
	mlx->assets.wall = mlx_xpm_file_to_image(mlx->mlx_p, "assets/wall.xpm",
			&mlx->width, &mlx->height);
	mlx->assets.coin = mlx_xpm_file_to_image(mlx->mlx_p, "assets/coin.xpm",
			&mlx->width, &mlx->height);
	mlx->assets.exit = mlx_xpm_file_to_image(mlx->mlx_p, "assets/exit.xpm",
			&mlx->width, &mlx->height);
	mlx->assets.chara = mlx_xpm_file_to_image(mlx->mlx_p, "assets/char.xpm",
			&mlx->width, &mlx->height);
	if (!mlx->assets.grass || !mlx->assets.wall || !mlx->assets.coin
		|| !mlx->assets.exit || !mlx->assets.chara)
	{
		perror("Error loading one or more images");
		exit(1);
	}
}

int	allocate_game_resources(t_game **game_ptr)
{
	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return (1);
	game->map = (t_map *)malloc(sizeof(t_map));
	if (!game->map)
		return (1);
	game->info = (t_info *)malloc(sizeof(t_info));
	if (!game->info)
		return (1);
	game->mlx = (t_mlx *)malloc(sizeof(t_mlx));
	if (!game->mlx)
		return (1);
	game->mlx->mlx_p = mlx_init();
	if (!game->mlx->mlx_p)
		return (1);
	*game_ptr = game;
	return (0);
}

int	check_and_init(int argc, char **argv, t_game **game)
{
	if (argc < 2)
	{
		perror("Error\nYou should try with a map (");
		return (1);
	}
	if (check_map(argv) != 0)
	{
		perror("Error\ntry a viable map maybe ?(");
		return (1);
	}
	if (allocate_game_resources(game) != 0)
	{
		free_resources(*game);
		perror("Error\nAllocating error )");
		return (1);
	}
	return (0);
}

int check_screen_size(t_mlx *mlx, int map_cols, int map_rows) 
{
    int screen_width;
    int screen_height;
    
    mlx_get_screen_size(mlx->mlx_p, &screen_width, &screen_height);
    if (80 * map_cols > screen_width || 60 * map_rows > screen_height)
    {
        perror("Error\nSize matters (");
        return 1;
    }
    return 0;
}

int	main(int argc, char **argv)
{
	t_game	*game;
    
	if (check_and_init(argc, argv, &game) != 0)
		return (1);
	init_map(argv, game->map);
	load_images(game->mlx);
	init_info(game);
    if (check_screen_size(game->mlx, game->map->cols, game->map->rows) != 0)
    {
        free_resources(game);
        return 1;
    }
	game->mlx->win_p = mlx_new_window(game->mlx->mlx_p, 80 * game->map->cols, 60
			* game->map->rows, "So_long"); // Créer une nouvelle fenêtre
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
