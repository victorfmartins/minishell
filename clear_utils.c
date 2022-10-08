/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 21:35:51 by asoler            #+#    #+#             */
/*   Updated: 2022/10/08 22:19:33 by asoler           ###   ########.fr       */
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
	t_env	*lst;

	i = 0;
	lst = data->hash_table[i];
	while (i < TABLE_SIZE)
	{
		while (!lst && i < TABLE_SIZE)
			i++;
		lst = data->hash_table[i];
		free_lst(&lst);
	}
	free(data->hash_table);
}
