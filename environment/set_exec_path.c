/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exec_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:43:42 by vfranco-          #+#    #+#             */
/*   Updated: 2022/11/27 14:32:25 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_exec_paths(t_data *data)
{
	char	*value;
	char	**paths;
	int		lines;
	int		i;

	value = get_env_var(data, "PATH");
	// [TODO]
	// if (value) -> nao tem path em envp
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
