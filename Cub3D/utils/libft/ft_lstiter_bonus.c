/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbacquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:51:03 by cbacquet          #+#    #+#             */
/*   Updated: 2022/11/24 18:11:56 by cbacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

/*

void	replace_every_other_char_by_two(void *str)
{
	size_t i;

	i = 0;
	while (((char *)str)[i])
	{
		if (i % 2 == 0)
			((char *)str)[i] = '2';
		i++;
	}
}

void	replace_every_other_char_by_seven(void *str)
{
	size_t i;

	i = 0;
	while (((char *)str)[i])
	{
		if (i % 2 == 1)
			((char *)str)[i] = '7';
		i++;
	}
}

void print_lst(t_list *lst)
{
	while (lst)
	{
		ft_putstr_fd(lst->content, 1);
		lst = lst->next;
	}
}

int main()
{
	t_list	*head;

	head = NULL;

	ft_lstadd_back(&head, ft_lstnew(ft_strdup("Salut\n")));
	ft_lstadd_back(&head, ft_lstnew(ft_strdup("Bonjour\n")));
	ft_lstadd_back(&head, ft_lstnew(ft_strdup("Non\n")));
	ft_lstadd_back(&head, ft_lstnew(ft_strdup("-----------\n")));

	print_lst(head);	

	ft_lstiter(head, &replace_every_other_char_by_two);

	print_lst(head);	
	
	ft_lstiter(head, &replace_every_other_char_by_seven);
	
	print_lst(head);	

}
*/