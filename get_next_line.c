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

char	*fill_storage(int fd, char *storage)
{
	char	*temp;
	int		bytes;

	if (!storage)
		storage = malloc(1);
	temp = malloc(sizeof(char) * BUFFER_SIZE + 1);
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
		if (ft_strchr(temp, '\n'))
			break ;
	}
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	storage = fill_storage(fd, storage);
	return (storage);
}

#include <stdio.h>
int main(void)
{
	int fd = open("new.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	return (0);
}