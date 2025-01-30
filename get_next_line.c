/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:36:26 by armarake          #+#    #+#             */
/*   Updated: 2025/01/30 17:49:55 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_fill_storage(int fd, char *storage, char *buffer)
{
	ssize_t	bytes;
	char	*temp;

	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (NULL);
		else if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		temp = storage;
		storage = ft_strjoin(temp, buffer);
		if (!storage)
		{
			free(temp);
			temp = NULL;
			return (NULL);
		}
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (storage);
}

static char	*ft_update_storage(char *final_line)
{
	char	*updated;
	ssize_t	i;

	if (!final_line)
		return (NULL);
	i = 0;
	while (final_line[i] && final_line[i] != '\n' && final_line[i] != '\0')
		i++;
	if (final_line[i] == '\0' || final_line[i + 1] == '\0')
		return (NULL);
	updated = ft_substr(final_line, i + 1, ft_strlen(final_line) - i);
	if (!updated)
		return (NULL);
	final_line[i + 1] = '\0';
	if (*updated == '\0')
		updated = NULL;
	return (updated);
}

char	*get_next_line(int fd)
{
	static char	*storage = NULL;
	char		*final_line;
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0))
	{
		free(buffer);
		free(storage);
		buffer = NULL;
		storage = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	final_line = ft_fill_storage(fd, storage, buffer);
	free(buffer);
	buffer = NULL;
	if (!final_line || *final_line == '\0')
	{
		free(final_line);
		return (NULL);
	}
	storage = ft_update_storage(final_line);
	return (final_line);
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
// 	system("leaks a.out");
// 	return (0);
// }