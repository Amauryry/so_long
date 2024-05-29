/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:35:10 by aberion           #+#    #+#             */
/*   Updated: 2024/05/29 12:54:00 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/src/ft_printf.h"
#include "libft/libft.h"
#include "so_long.h"

void	init_map(char **argv, t_map *map)
{
	int	j;
	int	rows;
	int	cols;

	rows = 0;
	cols = 0;
	map->map = get_raw_map(argv[1]);
	while (map->map[rows])
	{
		j = 0;
		while (map->map[rows][j])
			j++;
		if (cols == 0)
			cols = j;
		rows++;
	}
	map->rows = rows;
	map->cols = cols;
}

void	init_info(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	game->info->left_items = 0;
	game->info->count_move = 0;
	while (i < game->map->rows)
	{
		j = 0;
		while (j < game->map->cols)
		{
			if (game->map->map[i][j] == 'C')
				game->info->left_items++;
			if (game->map->map[i][j] == 'P')
			{
				game->info->x = i;
				game->info->y = j;
			}
			j++;
		}
		i++;
	}
	game->mlx->width = 0;
	game->mlx->height = 0;
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
		perror("Error\nError loading one or more images");
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
	if (check_map(argv) != 0 || (!check_file_extension(argv[1], ".ber")))
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
