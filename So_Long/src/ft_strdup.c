/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:56:31 by xalves            #+#    #+#             */
/*   Updated: 2025/07/25 14:15:21 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*ft_strdup(const char *s)
{
	int		len;
	char	*dup_str;

	len = ft_strlen((char *)s);
	dup_str = malloc(sizeof(char) * (len + 1));
	if (!dup_str)
		return (NULL);
	len = 0;
	while (s[len])
	{
		dup_str[len] = s[len];
		len++;
	}
	dup_str[len] = '\0';
	return (dup_str);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
