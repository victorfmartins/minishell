/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_env_hash.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfranco- <vfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 08:00:54 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/20 08:49:40 by vfranco-         ###   ########.fr       */
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

void	alloc_env_hash(char **envp, t_data *data) // [TODO] if (!envp) ??
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

void	print_table(t_env *hash_table[TABLE_SIZE])
{
	int	i;

	i = 0;
	while (i < TABLE_SIZE)
	{
		if (hash_table[i] == NULL)
			ft_printf("\t%i\t---\n", i);
		else
		{
			ft_printf("\t%i\t", i);
			print_env_lst(hash_table[i]);
		}
		i++;
	}
}
