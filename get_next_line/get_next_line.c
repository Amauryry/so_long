/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:07:39 by aberion           #+#    #+#             */
/*   Updated: 2024/04/11 16:05:54 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;

	if (!stash)
	{
		stash = malloc(1);
		if (!stash)
			return (NULL);
		*stash = '\0';
	}
	read_and_update_stash(fd, &stash);
	if (stash == NULL || stash[0] == '\0')
	{
		free(stash);
		return (NULL);
	}
	line = stash_to_line(&stash);
	clean_stash(&stash);
	return (line);
}

void	process_read_data(char **stash, char *buffer, int bytes_read)
{
	if (bytes_read < 0)
	{
		free(buffer);
		free(*stash);
		*stash = NULL;
		return ;
	}
	buffer[bytes_read] = '\0';
	addto_stash(stash, buffer, bytes_read);
	if (bytes_read == 0)
	{
		free(buffer);
		if (*stash[0] == '\0')
		{
			free(*stash);
			*stash = NULL;
		}
		return ;
	}
}

void	read_and_update_stash(int fd, char **stash)
{
	char	*buffer;
	int		bytes_read;
	int		line_i;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return ;
	line_i = ft_islinefinished(*stash);
	while (line_i < 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		process_read_data(stash, buffer, bytes_read);
		if (*stash == NULL || bytes_read == 0)
			return ;
		line_i = ft_islinefinished(*stash);
	}
	free(buffer);
}

// int	main(int ac, char **av)
// {
// 	int		fd;
// 	int i = 0;
// 	char	*line;

// 	if (ac != 2)
// 		return (0);
// 	fd = open(av[1], O_RDONLY);
// 	line = get_next_line(fd);
// 	while (i < 5)
// 	{
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 		i++;
// 	}
// 	return (0);
// }
