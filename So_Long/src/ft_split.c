/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:28:05 by xalves            #+#    #+#             */
/*   Updated: 2025/07/23 16:17:12 by xalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

static void	ft_free_split(char **arr, int j)
{
	int	i;

	i = -1;
	while (++i < j)
		free(arr[i]);
	free(arr);
}

static int	ft_count_words(const char *s, char c)
{
	int	i;
	int	words;
	int	in_word;

	i = 0;
	words = 0;
	in_word = 0;
	while (s[i])
	{
		if (s[i] != c && in_word == 0)
		{
			words++;
			in_word = 1;
		}
		else if (s[i] == c)
			in_word = 0;
		i++;
	}
	return (words);
}

static char	*add_word(const char *s, int start, int end)
{
	char	*word;
	int		i;

	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

void	increment(int *i, int *len, const char *s, char c)
{
	while (s[*i] == c && s[*i])
	{
		(*i)++;
	}
	while (s[*i] != c && s[*i])
	{
		(*i)++;
		(*len)++;
	}
}

char	**ft_split(const char *s, char c)
{
	int		i;
	int		j;
	int		len;
	char	**arr;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	arr = malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (s[i])
	{
		len = 0;
		increment(&i, &len, s, c);
		if (len > 0)
		{
			arr[j] = add_word(s, i - len, i);
			if (!arr[j])
				return (ft_free_split(arr, j), NULL);
			j++;
		}
	}
	return (arr[j] = NULL, arr);
}
//cc -Wall -Werror -Wextra ft_split.c
//arr[j] = NULL; AKA end of a arrays of strings

/* int	main(void)
{
 //Segmentation fault
 	//char	s[] = "";
	//char	c = 'a';
	 char	s1[] = "^^^1^^2a,^^^^3^^^^--h^^^^";
	char	c1 = '^';
	char **arr1 = ft_split(s1, c1);
	printf("%s\n", arr1[0]);  // prints "apple"
	printf("%s\n", arr1[1]);
	printf("%s\n", arr1[2]);
	printf("%s\n", arr1[3]);
	ft_free_split(arr1, 4);
	return (0);
} */
