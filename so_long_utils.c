/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-26 06:19:44 by aberion           #+#    #+#             */
/*   Updated: 2024-05-26 06:19:44 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_valid_move(t_game *game, int new_x, int new_y)
{
	return (new_x >= 0 && new_x < game->map->rows && new_y >= 0
		&& new_y < game->map->cols && game->map->map[new_x][new_y] != '1');
}

void	update_player_position(t_game *game, int new_x, int new_y)
{
	char	target_tile;

	target_tile = game->map->map[new_x][new_y];
	if (target_tile == 'C')
		game->info->left_items--;
	if (target_tile == 'E' && game->info->left_items == 0)
		close_window(game);
	if (game->map->map[game->info->x][game->info->y] != 'E')
		game->map->map[game->info->x][game->info->y] = '0';
	game->info->x = new_x;
	game->info->y = new_y;
	game->map->map[game->info->x][game->info->y] = 'P';
	if (target_tile == 'E')
		game->map->map[game->info->x][game->info->y] = 'E';
}

void	move_player(t_game *game, int move_x, int move_y)
{
	int	new_x;
	int	new_y;

	new_x = game->info->x + move_x;
	new_y = game->info->y + move_y;
	if (is_valid_move(game, new_x, new_y))
	{
		game->info->count_move++;
		ft_printf("%d\n", game->info->count_move);
		update_player_position(game, new_x, new_y);
		mlx_clear_window(game->mlx->mlx_p, game->mlx->win_p);
		draw_map(game);
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
