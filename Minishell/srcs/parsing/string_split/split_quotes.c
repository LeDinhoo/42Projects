/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:38:00 by hdupuy            #+#    #+#             */
/*   Updated: 2023/10/13 11:18:05 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	handle_single_quotes(t_token **head, t_split *tkn, const char *str)
{
	if (tkn->in_quotes == '\'')
	{
		tkn->in_quotes = 0;
		if (tkn->end - tkn->start > 0 && str[tkn->end - 1] != '\'')
		{
			add_token_to_list(head, &str[tkn->start], tkn->end - tkn->start,
				tkn);
			tkn->start = tkn->end + 1;
		}
	}
	else if (!tkn->in_quotes)
	{
		tkn->in_quotes = '\'';
		tkn->in_simple_quotes = 1;
	}
}

void	handle_double_quotes(t_token **head, t_split *tkn, const char *str)
{
	if (tkn->in_quotes == '\"')
	{
		tkn->in_quotes = 0;
		if (tkn->end - tkn->start > 0 && str[tkn->end - 1] != '\"')
		{
			add_token_to_list(head, &str[tkn->start], tkn->end - tkn->start,
				tkn);
			tkn->start = tkn->end + 1;
		}
	}
	else if (!tkn->in_quotes)
		tkn->in_quotes = '\"';
}

int	quote_count(const char *str, int i)
{
	int	nb_quote;
	int	is_open;

	nb_quote = 0;
	is_open = 1;
	while (str[i] && is_open == 1)
	{
		if (str[i] == '\"')
		{
			if ((ft_strichr("<>;| ", str[i + 1]) != -1) || str[i + 1] == '\0')
				is_open = 0;
			nb_quote++;
		}
		i++;
	}
	return (nb_quote);
}

int	single_quote_count(const char *str, int i)
{
	int	nb_quote;
	int	is_open;

	nb_quote = 0;
	is_open = 1;
	while (str[i] && is_open == 1)
	{
		if (str[i] == '\'')
		{
			if ((ft_strichr("<>;| ", str[i + 1]) != -1) || str[i + 1] == '\0')
				is_open = 0;
			nb_quote++;
		}
		i++;
	}
	return (nb_quote);
}

void	handle_single_quotes_content(t_token **head, t_split *tkn,
		const char *str)
{
	while (tkn->end <= tkn->length)
	{
		if (str[tkn->end] == '\"')
		{
			if (tkn->in_quotes == 0)
				tkn->in_quotes = '\"';
			else
				tkn->in_quotes = 0;
		}
		if (tkn->in_quotes == 0 && ft_strichr("<>;| ", str[tkn->end + 1]) != -1)
			break ;
		tkn->end++;
	}
	add_token_to_list(head, &str[tkn->start], tkn->end - tkn->start + 1, tkn);
	tkn->end++;
	tkn->start = tkn->end + 1;
	tkn->in_quotes = 0;
}
