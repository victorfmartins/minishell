/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 21:50:00 by asoler            #+#    #+#             */
/*   Updated: 2022/09/28 01:16:06 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	alloc_env(char **envp, t_env **env)
{
	char	**split_line;
	int		i;

	i = 0;
	while (envp[i])
	{
		split_line = ft_split(envp[i], '=');
		add_back(env, create_var(split_line[0], split_line[1]));
		free_table(split_line);
		i++;
	}
}
