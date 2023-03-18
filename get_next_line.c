/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 01:10:44 by eej-jama          #+#    #+#             */
/*   Updated: 2022/11/13 17:39:59 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*str;
	char		*string;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (0);
	str = read_buffer(fd, str);
	if (!str)
		return (NULL);
	string = to_ret(str);
	str = chyata(str);
	return (string);
}
