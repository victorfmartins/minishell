/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 23:40:27 by asoler            #+#    #+#             */
/*   Updated: 2022/12/03 23:45:52 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_table(t_env *hash_table[TABLE_SIZE])
{
	int	i;

	i = 0;
	while (i < TABLE_SIZE)
	{
		if (hash_table[i])
			print_env_lst(hash_table[i]);
		i++;
	}
}

void	exec_one_cmd(t_data *data, t_cmd *node, int flag)
{
	if (!ft_strncmp(node->args[0], "env", 3))
	{
		print_table(data->hash_table);
		return ;
	}
	if (flag == 1)
	{
		if (!ft_strncmp(node->args[0], "unset", 5))
			hash_table_delete(data, node->args[1]);
		else if (!ft_strncmp(node->args[0], "export", 6))
			hash_table_insert(data, node->args[1]);
		else if (!ft_strncmp(node->args[0], "exit", 4))
			exit_program(data);
	}
	return ;
}

int	exec_builtin(t_data *data, t_cmd *node, int flag)
{
	if (node->type == BUILTIN && !flag)
	{
		if (!data->exec.n_args)
		{
			exec_one_cmd(data, node, 1);
			return (1);
		}
	}
	if (!ft_strncmp(node->args[0], "echo", 4))
		return (0);
	if (flag == 1 && node->type == BUILTIN)
	{
		exec_one_cmd(data, node, 2);
		return (1);
	}
	else
		return (0);
	return (0);
}
