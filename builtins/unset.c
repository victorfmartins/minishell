/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 21:21:51 by asoler            #+#    #+#             */
/*   Updated: 2022/12/05 21:27:32 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_unset(t_data *data, char *key)
{
	unsigned int	index;
	t_env			*node;
	t_env			*prev;

	index = hash(key);
	node = data->hash_table[index];
	prev = NULL;
	while (node)
	{
		if (ft_strncmp(key, node->key, ft_strlen(key)))
		{
			if (prev && node->next)
				prev->next = node->next;
			if (!node->next)
				prev->next = NULL;
			node->next = NULL;
			ft_envclear(&node, free);
			break ;
		}
		prev = node;
		node = node->next;
	}
	return (0);
}
