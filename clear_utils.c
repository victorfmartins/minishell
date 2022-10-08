/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 21:35:51 by asoler            #+#    #+#             */
/*   Updated: 2022/10/08 23:14:45 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	free_lst(t_env *env)
{
	t_env	*tmp;

	while (env != NULL)
	{
		tmp = env;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		env = env->next;
	}
}

void	free_hash_table(t_data *data)
{
	int		i;

	i = 0;
	while (i < TABLE_SIZE)
	{
		if (data->hash_table[i])
			free_lst(data->hash_table[i]);
		i++;
	}
	free(data->hash_table);
}
