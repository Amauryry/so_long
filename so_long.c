/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:07:23 by aberion           #+#    #+#             */
/*   Updated: 2024/05/20 14:57:51 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "minilibx-linux/mlx.h"


int close_window(void *param)
{
    t_mlx *mlx = (t_mlx *)param;
    
    if (mlx && mlx->mlx_p && mlx->win_p)
    {
        mlx_clear_window(mlx->mlx_p, mlx->win_p);
        mlx_destroy_window(mlx->mlx_p, mlx->win_p);
        mlx_destroy_display(mlx->mlx_p);
    }
    free(mlx->mlx_p);
    free(mlx);
    exit(0);
    return (0);
}

int key_press(int keycode, void *param)
{
    if (keycode == ESC_KEY)
        close_window(param);
    return (0);
}

int main(int argc, char **argv)
{
    t_mlx *mlx;

    if (argc < 2)
    {
        perror("Error, please add a map file");
        return 1;
    }
    if (check_map(argv) != 0)
        return 1;
    mlx = (t_mlx *)malloc(sizeof(t_mlx));
    if (!mlx)
        return (1);
    mlx->mlx_p = mlx_init(); // Initialiser la bibliothèque graphique
    if (!mlx->mlx_p)
    {
        free(mlx);
        return (1); 
    }
    mlx->win_p = mlx_new_window(mlx->mlx_p, 800, 600, "Ma première fenêtre MiniLibX"); // Créer une nouvelle fenêtre
    if (!mlx->win_p)
    {
        free(mlx);
        return (1); // Gestion d'erreur si mlx_new_window échoue
    }
    mlx_hook(mlx->win_p, 17, 0, close_window, mlx);
    mlx_key_hook(mlx->win_p, key_press, mlx);
    mlx_loop(mlx->mlx_p);
    return (0);
}
