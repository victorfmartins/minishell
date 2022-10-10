/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfranco- <vfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 17:14:02 by asoler            #+#    #+#             */
/*   Updated: 2022/10/10 17:14:24 by vfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_cmd_son(t_data *data)
{
	if (execve(data->exec_cmd[0], data->exec_cmd, NULL) < 0) // a ausencia de envp não pode prejudicar a exec. de algum programa?
	{
		data->proc.pid = -1;
		ft_printf("bash: %s: %s\n", data->exec_cmd[0], strerror(errno));
	}
}

void	exec_cmd_parent(t_data *data)
{
	fork_process(data); //faz o fork e chama a execução do process filho
	if (data->proc.pid != -1)
		wait_and_free(data);
}

void	exec_cmd(t_data *data)
{
	if (!verify_cmd(data))
	{
		ft_printf("bash: %s: command not found\n", data->cmd);
		free(data->cmd);
	}
	else
		exec_cmd_parent(data);
}
