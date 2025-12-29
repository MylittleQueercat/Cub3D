/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:43:24 by lilwang           #+#    #+#             */
/*   Updated: 2025/12/29 13:26:40 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static char	*ensure_stash(char *stash)
// {
// 	if (!stash)
// 	{
// 		stash = ft_strdup("");
// 		if (!stash)
// 			return (NULL);
// 	}
// 	return (stash);
// }

// static char	*extract_line(char *stash)
// {
// 	int		i;
// 	char	*line;

// 	i = 0;
// 	if (!stash || !stash[i])
// 		return (NULL);
// 	while (stash[i] && stash[i] != '\n')
// 		i++;
// 	line = malloc(i + 2);
// 	if (!line)
// 		return (NULL);
// 	i = 0;
// 	while (stash[i] && stash[i] != '\n')
// 	{
// 		line[i] = stash[i];
// 		i++;
// 	}
// 	if (stash[i] == '\n')
// 		line[i++] = '\n';
// 	line[i] = '\0';
// 	return (line);
// }

// static	char	*get_new_buffer(char *stash)
// {
// 	int		i;
// 	int		j;
// 	char	*new_buf;

// 	i = 0;
// 	if (!stash)
// 		return (NULL);
// 	while (stash[i] && stash[i] != '\n')
// 		i++;
// 	if (!stash[i])
// 		return (free(stash), NULL);
// 	new_buf = malloc(ft_strlen(stash) - i + 1);
// 	if (!new_buf)
// 	{
// 		free(stash);
// 		return (NULL);
// 	}
// 	i++;
// 	j = 0;
// 	while (stash[i])
// 		new_buf[j++] = stash[i++];
// 	new_buf[j] = '\0';
// 	free(stash);
// 	return (new_buf);
// }

// static	char	*fill_buffer_util_newline(int fd, char *stash)
// {
// 	char	*buff;
// 	int		rd_bytes;

// 	stash = ensure_stash(stash);
// 	if (!stash)
// 		return (NULL);
// 	buff = malloc(BUFFER_SIZE + 1);
// 	if (!buff)
// 		return (NULL);
// 	rd_bytes = 1;
// 	while (!ft_strchr(stash, '\n') && rd_bytes != 0)
// 	{
// 		rd_bytes = read(fd, buff, BUFFER_SIZE);
// 		if (rd_bytes == -1)
// 			return (free(buff), free(stash), NULL);
// 		buff[rd_bytes] = '\0';
// 		stash = ft_strjoin(stash, buff);
// 		if (!stash)
// 			return (free(buff), NULL);
// 	}
// 	free(buff);
// 	return (stash);
// }

// char	*get_next_line(int fd)
// {
// 	char		*line;
// 	static char	*stash[OPEN_MAX];

// 	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= OPEN_MAX)
// 		return (NULL);
// 	stash[fd] = fill_buffer_util_newline(fd, stash[fd]);
// 	if (!stash[fd])
// 		return (NULL);
// 	line = extract_line(stash[fd]);
// 	if (!line)
// 	{
// 		free(stash[fd]);
// 		stash[fd] = NULL;
// 		return (NULL);
// 	}
// 	stash[fd] = get_new_buffer(stash[fd]);
// 	return (line);
// }


static int	clear(char *buff, int i)
{
	if (i < 0)
		i = 0;
	while (i <= BUFFER_SIZE)
		buff[i++] = 0;
	return (1);
}

static int	nl_index(const char *str, int bytes)
{
	int	i;

	i = -1;
	if (!str)
		return (-1);
	while (str[++i])
	{
		if (str[i] == '\n')
			return (i + 1);
	}
	if (bytes < BUFFER_SIZE)
		return (bytes);
	return (-1);
}

char	*str_join(char *s1, const char *s2, int len)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (s1 && s1[i])
		i++;
	j = 0;
	while (j < len && s2[j])
		j++;
	str = malloc(i + j + 1);
	if (!str)
		return (free(s1), NULL);
	len = -1;
	while (++len < i)
		str[len] = s1[len];
	len = -1;
	while (++len < j)
		str[i + len] = s2[len];
	str[i + len] = 0;
	return (free(s1), str);
}


char	*get_next_line(int fd)
{
	static char	buff[1024][BUFFER_SIZE + 1];
	char		*line;
	int			b;
	int			i;
	int			j;

	if (fd < 0 || fd > 1023)
		return (NULL);
	free((j = -1, line = NULL, b = BUFFER_SIZE, NULL));
	while (nl_index(buff[fd], b) == -1)
	{
		line = str_join(line, buff[fd], BUFFER_SIZE);
		b = read(fd, buff[fd], BUFFER_SIZE);
		// if (clear(buff[fd], b) && (b < 0 || !line || (!b && !*line)))
		// 	return (clear(buff[fd], 0), free(line), NULL);
		if (b < 0)
			return (clear(buff[fd], 0), free(line), NULL);
		clear(buff[fd], b);
		if (!line || (!b && !*line))
			return (clear(buff[fd], 0), free(line), NULL);
	}
	i = nl_index(buff[fd], b);
	line = str_join(line, buff[fd], i);
	while (buff[fd][++j + i])
		buff[fd][j] = buff[fd][j + i];
	buff[fd][j] = 0;
	if (!line || !*line)
		return (free(line), NULL);
	return (line);
}

