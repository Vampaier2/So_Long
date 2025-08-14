/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:50:54 by xalves            #+#    #+#             */
/*   Updated: 2025/07/23 15:16:17 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*join_till_newline(char *line, const char *buffer)
{
	char	*new_line;

	if (!line)
		line = ft_calloc(1, sizeof(char));
	new_line = ft_strjoin(line, buffer);
	if (!new_line)
		return (NULL);
	return (free(line), new_line);
}

/*----Calloc + Bzero----*/
void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*ptr;
	size_t			m;
	size_t			i;
	unsigned char	*ptr_aux;

	m = nmemb * size;
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb > (m / size))
		return (NULL);
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	ptr_aux = (unsigned char *)ptr;
	while (i < m)
	{
		ptr_aux[i] = 0;
		i++;
	}
	return (ptr_aux);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_linelen((char *)s1);
	s2_len = ft_linelen((char *)s2);
	new_str = ft_calloc(s1_len + s2_len + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < s1_len && s1[i])
	{
		new_str[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < s2_len && s2[i])
	{
		new_str[s1_len + i] = s2[i];
		i++;
	}
	return (new_str);
}

int	manage_buffer(char *buffer)
{
	size_t	i;
	size_t	j;
	int		found_nl;

	found_nl = 0;
	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
		{
			found_nl = 1;
			i++;
			break ;
		}
		i++;
	}
	j = 0;
	while (buffer[i])
		buffer[j++] = buffer[i++];
	while (j < i)
		buffer[j++] = '\0';
	return (found_nl);
}

size_t	ft_linelen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	return (i);
}
