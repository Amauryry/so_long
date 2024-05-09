/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 18:48:08 by aberion           #+#    #+#             */
/*   Updated: 2024/05/09 18:57:46 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int handle_key(int key, void *param)
{
    (void) key;
    (void) param;
    return (0);
}

int close_window(void *param, void *mlx_ptr)
{
    // Close the window and terminate the main loop
    mlx_destroy_window(param, mlx_ptr);
    exit(0);
}