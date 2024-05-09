/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:07:23 by aberion           #+#    #+#             */
/*   Updated: 2024/05/09 18:56:04 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int main()
{
    void *mlx_ptr;
    void *win_ptr;

    // Initialize the MiniLibX
    mlx_ptr = mlx_init();
    
    // Create a new window
    win_ptr = mlx_new_window(mlx_ptr, 800, 600, "So Long");
    __builtin_printf("Window pointer: %p\n", win_ptr);

    // Setup event handlers
    mlx_key_hook(win_ptr, handle_key, mlx_ptr);
    mlx_hook(win_ptr, 17, 0L, close_window, mlx_ptr); // 17 is the window close event

    // Main loop to keep the window open
    mlx_loop(mlx_ptr);
    return (0);
}
