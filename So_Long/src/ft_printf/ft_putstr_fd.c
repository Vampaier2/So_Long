/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:27:01 by xalves            #+#    #+#             */
/*   Updated: 2025/05/06 12:48:49 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s || fd < 0)
		return (ft_putstr_fd("(null)", fd));
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
	return (i);
}
