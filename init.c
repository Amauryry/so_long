// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   init.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/05/10 17:35:10 by aberion           #+#    #+#             */
// /*   Updated: 2024/05/10 17:50:58 by aberion          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "so_long.h"

// void	ft_free_struct(t_game *game)
// {
// 	if (game->map)
// 		ft_free_map(game);
// 	if (game->mlx)
// 		ft_free_mlx(game);
// 	free(game);
// }

// void	ft_error(char *str)
// {
// 	ft_printf("Error \n");
// 	ft_printf("%s", str);
// 	exit(0);
// }

// void	ft_error_free(char *str, t_game *game)
// {
// 	ft_printf("\nError \n");
// 	ft_printf("%s", str);
// 	ft_free_struct(game);
// 	exit (0);
// }

// t_game	*init_game(t_game *game, char *str)
// {
// 	game = malloc(sizeof(t_game));
// 	if (!game)
// 		ft_error("Problem while allocating structure game !");
// 	game->map = NULL;
// 	game->mlx = NULL;
// 	game->map = malloc(sizeof(t_map));
// 	game->mlx = malloc(sizeof(t_mlx));
// 	if (!game->map || !game->mlx)
// 		ft_error_free("Problem while allocating game in-structures !", game);
// 	init_map(game, str);
// 	init_mlx(game);
// 	return (game);
// }
