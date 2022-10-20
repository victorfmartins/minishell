/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_verification.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfranco- <vfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 17:20:26 by asoler            #+#    #+#             */
/*   Updated: 2022/10/20 17:51:20 by vfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_absolute_path(t_data *data)
{
	if (*data->line == '.' || *data->line == '/')
		return (1);
	return (0);
}

void	set_exec_paths(t_data *data) // poderia ir para env_var_utils
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

int	verify_cmd(t_data *data) //veirfy_alloc_cmd --> nota: separar o cmd e args
{
	char	*join_cmd;
	int		i;

	i = 0;
	data->exec_cmd = ft_split(data->line, ' ');
	if (is_absolute_path(data))
		return (1);
	data->cmd = ft_strdup(data->exec_cmd[0]);
	while (data->path[i])
	{
		join_cmd = ft_strjoin(data->path[i], data->cmd);
		if (!access(join_cmd, F_OK))
		{
			free(data->exec_cmd[0]);
			data->exec_cmd[0] = ft_strdup(join_cmd);
			free(join_cmd);
			return (1);
		}
		free(join_cmd);
		i++;
	}
	return (0);
}
