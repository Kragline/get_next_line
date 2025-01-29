/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:36:26 by armarake          #+#    #+#             */
/*   Updated: 2025/01/29 17:16:59 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_join_free(char *storage, char *temp)
{
	char	*tmp;

	tmp = ft_strjoin(storage, temp);
	free(storage);
	return (tmp);
}

char	*ft_fill_storage(int fd, char *storage)
{
	char	*temp;
	int		bytes;

	if (!storage)
		storage = ft_calloc(1, 1);
	temp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, temp, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(temp);
			return (NULL);
		}
		temp[bytes] = 0;
		storage = ft_join_free(storage, temp);
		if (ft_strchr(storage, '\n'))
			break ;
	}
	return (storage);
}

char	*ft_get_line(char *storage)
{
	char	*line;
	int		i;

	i = 0;
	if (!storage[i])
		return (NULL);
	while (storage[i] && storage[i] != '\n')
		i++;
	line = ft_calloc(i, sizeof(char));
	i = 0;
	while (storage[i] && storage[i] != '\n')
	{
		line[i] = storage[i];
		i++;
	}
	if (storage[i] && storage[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*ft_update_storage(char *storage)
{
	char	*updated;
	int		i;
	int		j;

	i = 0;
	if (!storage[i])
	{
		free(storage);
		return (NULL);
	}
	while (storage[i] && storage[i] != '\n')
		i++;
	updated = ft_calloc(ft_strlen(storage) - i, sizeof(char));
	i++;
	j = 0;
	while (storage[i])
		updated[j++] = storage[i++];
	free(storage);
	return (updated);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	storage = ft_fill_storage(fd, storage);
	if (!storage)
		return (NULL);
	line = ft_get_line(storage);
	storage = ft_update_storage(storage);
	return (line);
}

// int main(void)
// {
// 	int fd = open("new.txt", O_RDONLY);
// 	int i = 1;
// 	while (i < 5)
// 	{
// 		printf("[%d] %s", i, get_next_line(fd));
// 		i++;
// 	}
// 	return (0);
// }