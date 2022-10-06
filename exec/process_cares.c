/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cares.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 17:24:11 by asoler            #+#    #+#             */
/*   Updated: 2022/09/28 01:16:32 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	wait_and_free(t_data *data)
{
	if (waitpid(data->proc.pid, &data->proc.status, 0) < 0)
	{
		ft_printf("Wait fail %s\n", strerror(errno));
		return (0);
	}
	free_table(data->exec_cmd);
	if (WIFEXITED(data->proc.status))
		data->proc.ret = WEXITSTATUS(data->proc.status);
	return (1);
}

void	fork_process(t_data *data)
{
	data->proc.pid = fork();
	if (data->proc.pid < 0)
		exit (1);
	if (!data->proc.pid)
		exec_cmd_son(data);
}
