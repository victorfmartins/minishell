/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:01:50 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/30 15:58:46 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_args(char ***args, char **cmd, t_main *data)
{
	int	i;

	i = 0;
	if (args && cmd)
	{
		while ((*args)[i])
			free((*args)[i++]);
		free(*args);
		free(*cmd);
	}
	i = 0;
	while (i < data->n_args)
	{
		free(data->inter.fd[i]);
		i++;
	}
	free(data->inter.fd);
	free(data->inter.id);
}

// int	verify_cmd_access(char **args, char **cmd)
// {
// 	if (access(*cmd, F_OK) < 0 || !args[0])
// 	{
// 		write(2, "bash: ", 6);
// 		if (args[0])
// 			ft_putstr_fd(args[0], 2);
// 		write(2, ": command not found\n", 20);
// 		return (127);
// 	}
// 	return (0);
// }

int	enter_process_op(t_data *data, int iter)//env deve estar atualizado
{
	t_cmd	*node;
	// int		code;

	node = data->cmds;
	while(iter)
	{
		node = node->next;
		iter--;
	}
	// code = verify_cmd_access(node->args, &node->exec_cmd);
	// if (!code)
	// {
		execve(node->exec_cmd, node->args, data->envp);
		perror("Execve fail");
	// }
	// exit(code);
	return (1);
}

void	wait_all_child_finish(int id[], t_data *data)
{
	int	child_qtd;
	int	status;
	int	i;
	
	i = 0;
	child_qtd = data->pipex.n_args;
	status = data->pipex.status;
	while (i <= child_qtd)
	{
		waitpid(id[i], &status, 0);
		i++;
	}
}

//[TODO] melhorar fluxo, verificar acesso antes de fork
//[TODO] waitpid com falg para matar processos de forma assincrona