/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:01:50 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/30 17:47:01 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	enter_process_op(t_data *data, t_cmd *node)//env deve estar atualizado
{
	dup_fds(data, node);
	close_fds_until(data);
	execve(node->exec_cmd, node->args, data->envp);
	perror("Execve fail");
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

//[TODO] waitpid com flag para matar processos de forma assincrona