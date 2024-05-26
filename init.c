/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:35:10 by aberion           #+#    #+#             */
/*   Updated: 2024/05/10 17:50:58 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/src/ft_printf.h"
#include "libft/libft.h"
#include "so_long.h"

int init_map(char **argv, t_map *map)
{
    int fd;
    int i;
    int j;

    
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return 1;
    }
    int rows = 0, cols = 0;
    char *line;
    while ((line = get_next_line(fd)) != NULL)
    {   
        if (cols == 0)
            cols = ft_strlen(line) - 1;
        rows++;
        free(line);
    }
    close(fd);
    map->rows = rows;
    map->cols = cols;
    map->map = (char **)malloc(rows * sizeof(char *));
    if (!map->map)
        return 1;
    i = 0;
    while (i < rows)
    {
        map->map[i] = (char *)malloc(cols * sizeof(char));
        if (!map->map[i])
        {
            j = 0;
            while (j < i)
            {
                free(map->map[j]);
                j++;
            }
            free(map->map);
            return 1;
        }
        i++;
    }
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        i = 0;
        while (i < rows)
        {
            free(map->map[i]);
            i++;
        }
        free(map->map);
        return 1;
    }
    i = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        j = 0;
        while (j < cols)
        {
            map->map[i][j] = line[j];
            j++;
        }
        i++; 
        free(line);
    }
    close(fd);
    return 0;
}
