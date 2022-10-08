/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_env_hash.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 08:00:54 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/08 16:33:24 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

unsigned int	hash(char *name)
{
	unsigned int	hash;
	int	c;

	hash = 5381;
	while (*name)
	{
		c = *name;
		hash = (((hash << 5) + hash) + c) % TABLE_SIZE;
		name++;
	}
	return (hash);
}

void	init_hash_table(t_env **hash_table[TABLE_SIZE])
{
	int	i;
	
	i = 0;
	while (i < TABLE_SIZE)
	{
		*hash_table[i] = NULL;
		i++;
	}
}

int	hash_table_insert(t_env **hash_table, t_env *env)
{
	int	index;
	
	if (env == NULL)
		return (0);
	index = hash(env->key);
	add_back(&hash_table[index], env);
	return (1);
}

void	alloc_env_hash(char **envp, t_env ***hash_table)
{
	char	**split_line;
	int		i;

	i = 0;
	while (envp[i])
	{
		split_line = ft_split(envp[i], '=');
		hash_table_insert(*hash_table, create_var(split_line[0], split_line[1]));
		free_table(split_line);
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
			print_env(hash_table[i]);
		}
		i++;
	}
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_data	data;

// 	data.hash_table = ft_calloc(sizeof(t_env), TABLE_SIZE);
// 	alloc_env_hash(envp, &data.hash_table);
// 	print_table(data.hash_table);
// }
