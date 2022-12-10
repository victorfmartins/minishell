/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 23:40:27 by asoler            #+#    #+#             */
/*   Updated: 2022/12/10 19:53:15 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_one_cmd(t_data *data, t_cmd *node, int flag)
{
	if (!ft_strncmp(node->args[0], "env", 4))
	{
		builtin_env(data->hash_table, 0);
		return ;
	}
	if (flag == 1)
	{
		if (!ft_strncmp(node->args[0], "unset", 5))
			builtin_unset(data, node->args[1]);
		else if (!ft_strncmp(node->args[0], "export", 6))
			builtin_export(data, node->args[1]);
		else if (!ft_strncmp(node->args[0], "exit", 5))
			builtin_exit(data);
		else if (!ft_strncmp(node->args[0], "cd", 4))
			builtin_cd(node->args[1]);
	}
	return ;
}

int	exec_builtin(t_data *data, t_cmd *node, int flag)
{
	if (!ft_strncmp(node->args[0], "echo", 4))
		return (0);
	if (node->type == BUILTIN && !flag && !data->exec.n_args)
	{
		exec_one_cmd(data, node, 1);
		return (1);
	}
	if (flag && node->type == BUILTIN)
	{
		exec_one_cmd(data, node, 2);
		return (1);
	}
	else
		return (0);
	return (0);
}
