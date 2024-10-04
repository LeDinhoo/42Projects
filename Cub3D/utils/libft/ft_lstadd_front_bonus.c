/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbacquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:34:32 by cbacquet          #+#    #+#             */
/*   Updated: 2022/11/23 13:11:58 by cbacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst)
		return ;
	if (*lst)
		new->next = *lst;
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

	char *content = "ff'";

	lst = NULL;
	printf("%p\n", lst);
	new = ft_lstnew(&data);
	ft_lstadd_front(&lst, new);

	t_data *lst_data = lst->content;
	printf("%d|%d\n", lst_data->i, lst_data->j);
 }
 */