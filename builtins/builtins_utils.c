/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 23:40:27 by asoler            #+#    #+#             */
/*   Updated: 2022/12/04 02:17:10 by asoler           ###   ########.fr       */
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

int	valid_env_var(char *env)
{
	if (!ft_strrchr(env, '='))
		return (0);
	return (1);
}

void	export(t_data *data, char *arg)
{
	unsigned int	i;
	t_env			*node;
	char			**key_value;

	if (!valid_env_var(arg))
		return ;
	key_value = ft_split(arg, '=');
	node = get_env_var(data, key_value[0]);
	if (!node)
	{
		i = hash(key_value[0]);
		node = ft_envnew(key_value[0], key_value[1]);
		ft_env_addback(&data->hash_table[i], node);
	}
	else
	{
		free(node->value);
		node->value = ft_strdup(key_value[1]);
	}
	free_and_count_array(key_value, free);
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
			export(data, node->args[1]);
		else if (!ft_strncmp(node->args[0], "exit", 4))
			exit_program(data);
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
