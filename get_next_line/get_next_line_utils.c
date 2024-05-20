/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:07:37 by aberion           #+#    #+#             */
/*   Updated: 2024/01/10 17:57:12 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

void	clean_stash(char **stash)
{
	char	*new_stash;
	ssize_t	stash_l;
	ssize_t	i;
	ssize_t	line_l;

	line_l = 0;
	while ((*stash)[line_l] != '\n' && (*stash)[line_l])
		line_l++;
	stash_l = ft_strlen(*stash);
	new_stash = malloc(sizeof(char) * (stash_l - line_l + 1));
	if (!new_stash)
		return ;
	i = 0;
	while (i < stash_l - line_l)
	{
		new_stash[i] = (*stash)[i + line_l + 1];
		i++;
	}
	new_stash[i] = 0;
	free(*stash);
	*stash = new_stash;
}

char	*stash_to_line(char **stash)
{
	ssize_t	i;
	ssize_t	line_l;
	char	*line;

	line_l = 0;
	i = -1;
	while ((*stash)[line_l] != '\n' && (*stash)[line_l])
		line_l++;
	if ((*stash)[line_l] == '\n')
		line = malloc(sizeof(char) * (line_l + 2));
	else
		line = malloc(sizeof(char) * (line_l + 1));
	if (!line)
		return (NULL);
	while (i++ < line_l)
		line[i] = (*stash)[i];
	if ((*stash)[line_l] == '\n')
	{
		line[line_l] = '\n';
		line[line_l + 1] = 0;
	}
	return (line);
}

ssize_t	ft_islinefinished(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
	{
		if (s[len] == '\n')
			return (len);
		len++;
	}
	return (-1);
}

void	addto_stash(char **s1, char *s2, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	s1_l;
	char	*new;

	s1_l = ft_strlen(*s1);
	new = malloc(sizeof(char) * (s1_l + n + 1));
	if (!new)
		return ;
	i = 0;
	while (i < s1_l)
	{
		new[i] = (*s1)[i];
		i++;
	}
	j = 0;
	while (s2[j] && j < n)
	{
		new[i + j] = s2[j];
		j++;
	}
	new[i + j] = 0;
	free(*s1);
	*s1 = new;
	return ;
}
