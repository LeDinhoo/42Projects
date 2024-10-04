/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:16:46 by cbacquet          #+#    #+#             */
/*   Updated: 2023/12/18 13:31:44 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_word(char const *str, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (i == 0 && str[i] != c)
			count++;
		if ((str[i] != c) && (i > 0 && str[i - 1] == c))
			count++;
		i++;
	}
	return (count + 1);
}

static size_t	len_word(char const *str, char c, size_t index)
{
	size_t	len;

	len = 0;
	while (str[index])
	{
		if (str[index] == c)
			return (len);
		index++;
		len++;
	}
	return (len);
}

static char	**ft_free(char **tab, size_t i)
{
	while (i > 0)
		free(tab[i--]);
	free(tab[i]);
	free(tab);
	return (NULL);
}

char	**ft_fill_malloc(char const *s, char **tab, char c)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	while (s[i] && k < (count_word(s, c) - 1))
	{
		while (s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			tab[k] = ft_substr(s, i, (len_word(s, c, i)));
			if (!tab[k] && k > 0)
				return (ft_free(tab, k));
			else if (!tab[k])
				return (free(tab), NULL);
			i++;
			i += (len_word(s, c, i));
			k++;
		}
	}
	tab[k] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char		**tab;

	if (!s)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * count_word(s, c));
	if (!tab)
		return (NULL);
	return (ft_fill_malloc(s, tab, c));
}

/*
int main (void)
{
	char *s;
	char c;
	char **tabstr;
	size_t i;
	
	i = 0;
	s = " Hello my name is clement ";
	c = ' ';
	tabstr = ft_split(s, c);
	while (tabstr[i])
	{
		printf("%s\n", *tabstr);
		tabstr++;
		i++;
	}
}
*/
