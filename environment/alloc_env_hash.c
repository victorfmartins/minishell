/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_env_hash.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 08:00:54 by vfranco-          #+#    #+#             */
/*   Updated: 2022/12/04 03:10:48 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

unsigned int	hash(char *name)
{
	unsigned int	hash;
	int				c;

	hash = 5381;
	while (*name)
	{
		c = *name;
		hash = (((hash << 5) + hash) + c) % TABLE_SIZE;
		name++;
	}
	return (hash);
}

int	hash_table_delete(t_data *data, char *key)
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

int	hash_table_insert(t_data *data, char *env)
{
	unsigned int	index;
	t_env			*node;
	char			**split_line;

	split_line = ft_split(env, '=');
	index = hash(split_line[0]);
	node = ft_envnew(split_line[0], split_line[1]);
	free_and_count_array(split_line, free);
	ft_env_addback(&data->hash_table[index], node);
	return (1);
}

void	alloc_env_hash(char **envp, t_data *data)
{
	int		i;

	i = 0;
	data->hash_table = ft_calloc(sizeof(t_env *), TABLE_SIZE);
	while (envp[i])
	{
		hash_table_insert(data, envp[i]);
		i++;
	}
}
