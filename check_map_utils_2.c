/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:57:01 by aberion           #+#    #+#             */
/*   Updated: 2024/06/03 14:05:18 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>

char	*ft_realloc(char *ptr, size_t size)
{
	char	*self;

	free(ptr);
	self = ft_calloc((size + 1), sizeof(char));
	if (!self)
		exit(EXIT_FAILURE);
	return (self);
}

void	read_map_file(int fd_map, t_map_info *map_info)
{
	map_info->bytes_read = read(fd_map, map_info->raw_map, map_info->read_size);
	while (map_info->bytes_read >= map_info->read_size)
	{
		map_info->read_size <<= 1;
		map_info->raw_map = ft_realloc(map_info->raw_map, map_info->read_size);
		map_info->bytes_read = read(fd_map, map_info->raw_map,
				map_info->read_size);
	}
}

char	**get_raw_map(char *map_path)
{
	int			fd_map;
	t_map_info	map_info;
	char		**new;

	map_info.read_size = 1024;
	map_info.raw_map = ft_calloc(map_info.read_size, sizeof(char));
	if (!map_info.raw_map)
		exit(EXIT_FAILURE);
	fd_map = open(map_path, O_RDONLY);
	if (fd_map < 0)
	{
		free(map_info.raw_map);
		perror("Error\n");
		exit(EXIT_FAILURE);
	}
	read_map_file(fd_map, &map_info);
	close(fd_map);
	new = ft_split(map_info.raw_map, '\n');
	free(map_info.raw_map);
	if (!new)
	{
		perror("Error\nTry a viable map maybe ? (");
		exit(EXIT_FAILURE);
	}
	return (new);
}
