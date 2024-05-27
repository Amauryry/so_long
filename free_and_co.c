/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_co.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:36:52 by aberion           #+#    #+#             */
/*   Updated: 2024/05/27 13:42:38 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void free_mlx_resources(t_mlx *mlx)
{
    if (mlx->assets.grass)
        mlx_destroy_image(mlx->mlx_p, mlx->assets.grass);
    if (mlx->assets.wall)
        mlx_destroy_image(mlx->mlx_p, mlx->assets.wall);
    if (mlx->assets.coin)
        mlx_destroy_image(mlx->mlx_p, mlx->assets.coin);
    if (mlx->assets.exit)
        mlx_destroy_image(mlx->mlx_p, mlx->assets.exit);
    if (mlx->assets.chara)
        mlx_destroy_image(mlx->mlx_p, mlx->assets.chara);
    if (mlx->win_p)
        mlx_destroy_window(mlx->mlx_p, mlx->win_p);
    if (mlx->mlx_p) {
        mlx_destroy_display(mlx->mlx_p);
        free(mlx->mlx_p);
    }
    free(mlx);
}

void	free_resources(t_game *game)
{
    int i;

    i = 0;
	if (game->mlx)
	    free_mlx_resources(game->mlx);
	if (game->info)
		free(game->info);
	if (game->map)
	{
		if (game->map->map)
		{
			while (i < game->map->rows)
            {
				free(game->map->map[i]);
                i++;
            }
            free(game->map->map);
		}
		free(game->map);
	}
	free(game);
}

void free_tab(char **tab)
{
    int i;
    
    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}
