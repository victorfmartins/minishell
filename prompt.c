/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 21:09:10 by lufelip2          #+#    #+#             */
/*   Updated: 2022/10/08 21:31:38 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	free_lst(t_env **env)
{
	t_env	*aux;
	t_env	*tmp;

	aux = *env;
	tmp = *env;
	while (aux)
	{
		free(tmp->key);
		free(tmp->value);
		aux = tmp->next;
		free(tmp);
		tmp = aux;
	}
	*env = 0;
}

void	free_hash_table(t_data *data)
{
	int		i;
	t_env *lst;

	i = 0;
	lst = data->hash_table[i];
	while (i < TABLE_SIZE)
	{
		free_lst(&lst);
		i++;
		lst = data->hash_table[i];
	}
	free(lst);
}

void	exit_program(t_data *data)
{
	free_hash_table(data);
	(void)data;
	exit(0);
}

void	analize_line(t_data *data)
{
	exec_cmd(data);
}

void	prompt(t_data *data)
{
	char	*path;

	path = getcwd(0, 0);
	printf("%s\n", path);
	free(path);
	data->line = readline("❯ ");
	if (*data->line)
		add_history(data->line);
	else
		return ;
	if (!ft_strncmp("exit", data->line, 4))
		exit_program(data);
	analize_line(data);
}
