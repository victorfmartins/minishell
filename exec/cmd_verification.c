/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_verification.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 17:20:26 by asoler            #+#    #+#             */
/*   Updated: 2022/10/11 15:04:44 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_absolute_path(t_data *data)
{
	if (*data->line == '.' || *data->line == '/') //apenas executa arquivos executavel e absolutos
		return (1);
	return (0);
}

void	set_exec_paths(t_data *data) // poderia ir para os arquivos de env_var_utils
{
	char	*value;
	char	**paths;
	int		lines;
	int		i;

	value = get_env_var(data, "PATH");
	paths = ft_split(value, ':');
	lines = free_and_count_array(paths, 0) + 1;
	data->path = malloc(lines * sizeof(char *));
	i = 0;
	while (paths[i])
	{
		data->path[i] = ft_strjoin(paths[i], "/");
		i++;
	}
	data->path[i] = 0;
	free_and_count_array(paths, free);
}

int	verify_cmd(t_data *data) //veirfy_alloc_cmd --> nota: vamos separar o comando e args
{
	char	*join_cmd;
	int		i;

	i = 0;
	data->exec_cmd = ft_split(data->line, ' ');
	if (is_absolute_path(data))
		return (1);
	data->cmd = ft_strdup(data->exec_cmd[0]); //só manda um comando
	while (data->path[i])
	{
		join_cmd = ft_strjoin(data->path[i], data->cmd);
		if (!access(join_cmd, F_OK))
		{
			free(data->exec_cmd[0]);
			data->exec_cmd[0] = ft_strdup(join_cmd); //guarda o comando antes de parsear -> um comando nao absoluto
			free(join_cmd);
			return (1);
		}
		free(join_cmd);
		i++;
	}
	return (0);
}
