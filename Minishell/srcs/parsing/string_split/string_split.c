/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:57:09 by hdupuy            #+#    #+#             */
/*   Updated: 2023/10/13 12:54:48 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	update_in_quotes(t_parser *parser)
{
	parser->in_quotes = !(parser->in_quotes);
	parser->start = parser->end + 1;
}

void	handle_equal(t_token **head, t_split *tkn, const char *str)
{
	if (str[tkn->end - 1])
		tkn->equal = 1;
}

static void	process_string_part1(const char *str, t_token **head, t_split *tkn)
{
	if ((str[tkn->end] == ':' || str[tkn->end] == '!') && tkn->length == 1)
		return ;
	if (str[tkn->end] == '\'')
		handle_single_quotes(head, tkn, str);
	else if (str[tkn->end] == '\"')
		handle_double_quotes(head, tkn, str);
	else if (tkn->in_quotes == '\'' && str[tkn->end] != '\0')
		handle_single_quotes_content(head, tkn, str);
	else if (tkn->in_quotes == '\"' && str[tkn->end] != '\0')
		handle_double_quotes_content(head, tkn, str);
}

static void	process_string_part2(const char *str, t_token **head, t_split *tkn)
{
	if (str[tkn->end] == '<')
		handle_less_than_operator(head, tkn, str);
	else if (str[tkn->end] == '>')
		handle_greater_than_operator(head, tkn, str);
	else if (str[tkn->end] == ';' || str[tkn->end] == '|')
		handle_semicolon_or_pipe_operator(head, tkn, str);
	else if (str[tkn->end] == '=')
		handle_equal(head, tkn, str);
	else if (str[tkn->end] == ' ')
		handle_space(head, tkn, str);
	else if (str[tkn->end] == ' ' || str[tkn->end] == '\0')
		handle_end_of_string(head, tkn, str);
}

void	process_string(const char *str, t_token **head, t_split *tkn)
{
	while (tkn->end <= tkn->length)
	{
		process_string_part1(str, head, tkn);
		process_string_part2(str, head, tkn);
		tkn->end++;
	}
}
