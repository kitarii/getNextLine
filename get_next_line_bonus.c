/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiyari <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 00:03:18 by ktiyari           #+#    #+#             */
/*   Updated: 2024/03/21 21:34:43 by ktiyari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

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
	// if(fd > 1024)
	// 	return NULL;
	static char	*str[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	str[fd] = read_line(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	line = get_first_line(str[fd]);
	str[fd] = get_remaining(str[fd]);
	return (line);
}
int main()
{
	printf("%s",get_next_line(1024));
}
// int main()
// {
// 	int fd1 = open("file1.txt", O_RDONLY | O_CREAT);
// 	int fd2 = open("file2.txt", O_RDONLY | O_CREAT);
// 	int i = 1;

// 	while (i < 5)
// 	{	
// 		char *line1 = get_next_line(fd1);
// 		char *line2 = get_next_line(fd2);
// 		printf("1 : %s\n",  line1);
// 		printf("2 : %s\n", line2);
// 	 	i++;
// 		free(line1);
// 		free(line2);
// 	}
//     return 0;
// }