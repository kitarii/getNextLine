/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiyari <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:06:03 by ktiyari           #+#    #+#             */
/*   Updated: 2024/03/21 01:07:56 by ktiyari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*read_line(int fd, char *str)
{
	char	*buff;
	int		nb_rd;

	buff = (char *)malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	nb_rd = 1;
	while ((!ft_strchr(str, '\n') && nb_rd > 0))
	{
		nb_rd = read(fd, buff, BUFFER_SIZE);
		if ((nb_rd < 0))
		{
			free(str);
			free(buff);
			return (NULL);
		}
		buff[nb_rd] = '\0';
		str = ft_strjoin(str, buff);
	}
	free (buff);
	return (str);
}

char	*get_first_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (str[i] == '\0')
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*get_remaining(char *str)
{
	int		i;
	int		j;
	char	*remained;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\0')
	{
		free (str);
		return (NULL);
	}
	remained = (char *)malloc(sizeof(char) * (ft_strlen(str) - i));
	if (!remained)
		return (NULL);
	if (str[i] == '\n')
		i++;
	j = 0;
	while (str[i])
		remained[j++] = str[i++];
	remained[j] = '\0';
	free(str);
	return (remained);
}

char	*get_next_line(int fd)
{
	if(fd > 1024)
		return NULL;
	static char	*str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	str = read_line(fd, str);
	if (!str)
		return (NULL);
	line = get_first_line(str);
	str = get_remaining(str);
	return (line);
}
int main()
{
	get_next_line(5454);
}
