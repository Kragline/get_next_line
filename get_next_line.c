/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:36:26 by armarake          #+#    #+#             */
/*   Updated: 2025/01/30 17:12:16 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_join_free(char *storage, char *temp)
{
	char	*tmp;

	tmp = ft_strjoin(storage, temp);
	free(storage);
	storage = NULL;
	return (tmp);
}

static char	*ft_fill_storage(int fd, char *storage)
{
	char	*temp;
	int		bytes;

	if (!storage)
		storage = ft_calloc(1, 1);
	temp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	bytes = 1;
	while (!ft_strchr(storage, '\n') && bytes > 0)
	{
		bytes = read(fd, temp, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(storage);
			free(temp);
			return (NULL);
		}
		else if (bytes == 0)
			break ;
		temp[bytes] = 0;
		storage = ft_join_free(storage, temp);
	}
	free(temp);
	return (storage);
}

char	*ft_get_line(char *storage)
{
	char	*line;
	int		i;

	i = 0;
	if (!storage[i])
		return (NULL);
	while (storage[i] && storage[i] != '\n' && storage[i] != '\0')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (storage[i] && storage[i] != '\n' && storage[i] != '\0')
	{
		line[i] = storage[i];
		i++;
	}
	if (storage[i] && storage[i] == '\n')
		line[i] = '\n';
	return (line);
}

static char	*ft_update_storage(char *storage)
{
	char	*updated;
	int		i;
	int		j;

	i = 0;
	while (storage[i] && storage[i] != '\n')
		i++;
	if (!storage[i])
	{
		free(storage);
		return (NULL);
	}
	updated = ft_calloc((ft_strlen(storage) - i + 1), sizeof(char));
	i++;
	j = 0;
	while (storage[i])
		updated[j++] = storage[i++];
	free(storage);
	return (updated);
}

char	*get_next_line(int fd)
{
	static char	*storage = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	storage = ft_fill_storage(fd, storage);
	if (!storage)
	{
		free(storage);
		return (NULL);
	}
	line = ft_get_line(storage);
	storage = ft_update_storage(storage);
	return (line);
}

// int main(void)
// {
// 	int fd = open("new.txt", O_RDONLY);
// 	char *l1 = get_next_line(fd);
// 	char *l2 = get_next_line(fd);
// 	char *l3 = get_next_line(fd);
// 	char *l4 = get_next_line(fd);
// 	printf("%s", l1);
// 	printf("%s", l2);
// 	printf("%s", l3);
// 	printf("%s", l4);
// 	free(l1);
// 	free(l2);
// 	free(l3);
// 	free(l4);
// 	// system("leaks a.out");
// 	return (0);
// }