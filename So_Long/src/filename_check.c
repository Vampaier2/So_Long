/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 12:40:44 by xalves            #+#    #+#             */
/*   Updated: 2025/08/14 12:41:50 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen((char *)s);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}

int check_filename(char *file)
{
    int     len;
    char    *doc_type;
    
    len = ft_strlen(file);
    doc_type = ft_strrchr(file, '.');
    if (len <= 4)
        return(ft_printerror("!!Error on file name size.!! -> %s", file), 1);
    if (ft_strcmp(doc_type, ".ber") != 0)
        return(ft_printerror("!!Error on file type.!! -> %s", file), 1);
    return(0);
}