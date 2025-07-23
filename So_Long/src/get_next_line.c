/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 10:03:03 by xalves            #+#    #+#             */
/*   Updated: 2025/07/23 12:52:17 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*result_line;
	size_t		b_idx;

	b_idx = 0;
	if (BUFFER_SIZE < 1)
	{
		while (b_idx <= BUFFER_SIZE)
			buffer[b_idx++] = '\0';
		return (NULL);
	}
	result_line = NULL;
	while (buffer[0] || (read(fd, buffer, BUFFER_SIZE) > 0))
	{
		result_line = join_till_newline(result_line, buffer);
		if (manage_buffer(buffer))
			break ;
	}
	return (result_line);
}

/* int	main(void)
{
	int		fd;
	char	*line;
	int		count;

	count = 0;
	fd = open("a.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening file");
		return (1);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			printf("[EOF]: get_next_line returned NULL\n");
			break;
		}
		count++;
		printf("[%d]:%s", count, line);
		free(line);
	}
	close(fd);
	return (0);
} */
