/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:35:10 by aberion           #+#    #+#             */
/*   Updated: 2024/05/27 12:01:33 by aberion          ###   ########.fr       */
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
