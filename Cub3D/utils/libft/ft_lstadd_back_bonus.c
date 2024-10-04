/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbacquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:43:15 by cbacquet          #+#    #+#             */
/*   Updated: 2022/11/24 17:31:05 by cbacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*end;

	if (!lst)
		return ;
	if (*lst)
	{
		end = ft_lstlast(*lst);
		end->next = new;
	}
	else
		*lst = new;
}

/*
typedef struct s_data
{
	int j;
	int i;
	int k;
} t_data;

 int main (void)
 {
	// t_list *lst;
	t_list *new;
	t_list *lst;

	t_data data;
	data.i = 17;
	data.j = 8;

	//char *content = "ff'";

	lst = NULL;
	printf("%p\n", lst);
	new = ft_lstnew(&data);
	ft_lstadd_back(&lst, new);

	t_data *lst_data = lst->content;
	printf("%d|%d\n", lst_data->i, lst_data->j);
 }*/