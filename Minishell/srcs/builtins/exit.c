/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:07:29 by clement           #+#    #+#             */
/*   Updated: 2023/10/13 10:42:36 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	exit_build(t_cmd *current, t_mini *mini)
{
	int		ret_val;
	bool	is_error;

	is_error = false;
	ret_val = get_return_value(current->cmd_args, &is_error, mini);
	if (ret_val == 1 && is_error)
	{
		printf("exit\nmini: exit: too many arguments\n");
		return (1);
	}
	free_env(mini);
	if (ret_val == 2 && is_error)
		printf("exit\nmini: exit: required numerical argument\n");
	mini->ret = ret_val;
	free_signals(mini);
	exit(ret_val);
}

int	get_return_value(char **argv, bool *is_error, t_mini *mini)
{
	int	i;

	if (!argv[1])
		return (printf("exit\n"), mini->ret);
	else if (argv[1] && argv[2])
		return (*is_error = true, 1);
	else
	{
		i = 0;
		while (argv[1][i])
		{
			if (!ft_isdigit(argv[1][i]))
				return (*is_error = true, 2);
			i++;
		}
		return (printf("exit\n"), ft_atoi(argv[1]));
	}
}
