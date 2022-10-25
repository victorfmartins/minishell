/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:01:50 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/24 13:14:09 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

int	verify_cmd_access(char **args, char **cmd)
{
	if (access(*cmd, F_OK) < 0 || !args[0])
	{
		write(2, "bash: ", 6);
		if (args[0])
			ft_putstr_fd(args[0], 2);
		write(2, ": command not found\n", 20);
		return (127);
	}
	return (0);
}

int	enter_process_op(t_main *data, int iter) // receber stuct com out e in fds cmd e envp (deve estar atualizado) ta no data
{
	char	**args;
	char	*cmd;
	int		code;

	manage_fds(data, iter);
	args = ft_split_pass(data->argv[iter + 2], ' ', '\''); //apagar
	cmd = ft_strjoin("/usr/bin/", args[0]); //reemplazar por verify_cmd
	code = verify_cmd_access(args, &cmd);
	if (!code)
	{
		execve(cmd, args, data->envp);
		perror("Execve fail");
	}
	free_args(&args, &cmd, data);
	exit(code);
	return (1);
}

void	wait_all_child_finish(int id[], int child_qtd, int *status)
{
	int	i;

	i = 0;
	while (i < child_qtd)
	{
		waitpid(id[i], status, 0);
		i++;
	}
}

//[TODO] melhorar fluxo, verificar acesso antes de fork, mater dups depois de fork