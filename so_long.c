/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:07:23 by aberion           #+#    #+#             */
/*   Updated: 2024/05/10 19:24:36 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int close_window(void *param)
{
    t_mlx *mlx = (t_mlx *)param;
    
    if (mlx && mlx->mlx_p && mlx->win_p)
    {
        mlx_destroy_window(mlx->mlx_p, mlx->win_p);
        free(mlx);
    }
    exit(0);
    return (0);
}

int main(void)
{
    t_mlx *mlx;

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
    
    mlx_hook(mlx->win_p, 17, 0, close_window, mlx); // Gérer l'événement de fermeture de fenêtre

    mlx_loop(mlx->mlx_p);
    free(mlx->mlx_p);
    free(mlx->win_p);
    free(mlx);
    return (0);
}