/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 18:48:08 by aberion           #+#    #+#             */
/*   Updated: 2024/05/29 12:01:51 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <X11/X.h>

int	handle_key(int key, void *param)
{
	(void)key;
	(void)param;
	return (0);
}

int	close_window(void *win_pointeur, void *mlx_ptr)
{
	mlx_clear_window(&mlx_ptr, &mlx_ptr);
	mlx_destroy_window(&mlx_ptr, &win_pointeur);
	mlx_destroy_display(mlx_ptr);
	exit(0);
}
