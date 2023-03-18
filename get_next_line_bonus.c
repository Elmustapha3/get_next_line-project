/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 16:04:24 by eej-jama          #+#    #+#             */
/*   Updated: 2022/11/13 17:44:53 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	cp(char **str, char **line)
{
	int		i;
	char	*s1;
	char	*s2;

	i = 0;
	s1 = *str;
	s2 = *line;
	while (s1[i] && s1[i] != '\n')
	{
		s2[i] = s1[i];
		i++;
	}
	return (i);
}

char	*to_ret(char *str)
{
	int		i;
	char	*line;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
	{
		free(str);
		return (0);
	}
	i = cp(&str, &line);
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*chyata(char *str)
{
	int		i;
	int		k;
	char	*ret;

	i = 0;
	k = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i] || !str[i + 1])
	{
		free(str);
		return (0);
	}
	ret = malloc(ft_strlen(str) - i);
	if (!ret)
		return (0);
	i++;
	while (str[i])
		ret[k++] = str[i++];
	ret[k] = '\0';
	free(str);
	return (ret);
}

char	*read_buffer(int fd, char *str)
{
	char	*string;
	int		rd;

	string = malloc(BUFFER_SIZE + 1);
	while (1)
	{
		rd = read(fd, string, BUFFER_SIZE);
		if (!rd)
			break ;
		if (rd == -1)
		{
			free(string);
			if (str)
				free(str);
			return (NULL);
		}
		string[rd] = '\0';
		str = ft_strjoin(str, string);
		if (ft_strchr(string, '\n'))
			break ;
	}
	free(string);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str[OPEN_MAX];
	char		*string;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > OPEN_MAX)
		return (0);
	str[fd] = read_buffer(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	string = to_ret(str[fd]);
	str[fd] = chyata(str[fd]);
	return (string);
}
