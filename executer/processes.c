/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:01:50 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/30 23:55:55 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	enter_process_op(t_data *data, t_cmd *node)//env deve estar atualizado
{
	dup_fds(data, node);
	close_fds_until(data);
	execve(node->exec_cmd, node->args, data->envp);
	perror("Execve fail");
	return (1);
}

int	wait_and_free(t_data *data)
{
	int	status;
	int	ret;
	int	n_cmds;

	n_cmds = data->pipex.n_args;
	ret = 0;
	if (waitpid(0, &status, 0) < 0)
		ft_printf("Wait fail %s\n", strerror(errno));
	free(data->pipex.inter.id);
	while (n_cmds > 0)
	{
		n_cmds--;
		free(data->pipex.inter.fd[n_cmds]);
	}
	free(data->pipex.inter.fd);
	if (WIFEXITED(status))
		ret = WEXITSTATUS(status);
	return (ret);
}
