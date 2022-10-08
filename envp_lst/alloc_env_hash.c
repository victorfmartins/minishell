/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_env_hash.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfranco- <vfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 08:00:54 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/08 11:54:12 by vfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

unsigned int	hash(char *name)
{
	int				length;
	int				i;
	unsigned int	hash_value;
	
	length = ft_strlen(name);
	hash_value = 0;
	i = 0;
	while (i < length)
	{
		hash_value += name[i];
		hash_value = (hash_value * name[i]) % TABLE_SIZE;
		i++;
	}
	return (hash_value);
}

void	init_hash_table(t_env *hash_table[TABLE_SIZE])
{
	int	i;
	
	i = 0;
	while (i < TABLE_SIZE)
	{
		hash_table[i] = NULL;
		i++;
	}
	//table is empty
}

int	hash_table_insert(t_env *hash_table[TABLE_SIZE], t_env *env)
{
	int	index;
	
	if (env == NULL)
		return (0);
	index = hash(env->key);
	//if (hash_table[inde] != NULL)
		// add_to_list
	add_back(&hash_table[index], env);
	return (1);
}

void	alloc_env_hash(char **envp, t_env **env)
{
	char	**split_line;
	int		i;
	t_env	*hash_table[TABLE_SIZE];

	init_hash_table(hash_table);
	i = 0;
	while (envp[i])
	{
		split_line = ft_split(envp[i], '=');
		hash_table_insert(hash_table, create_var(split_line[0], split_line[1]));
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
			//ft_printf("\t%i\t%s\t%s\n", i, hash_table[i]->key, hash_table[i]->value);
		}
		i++;
	}
}

int	main()
{
	t_env	*hash_table[TABLE_SIZE];
	
	init_hash_table(hash_table);
	hash_table_insert(hash_table, create_var(ft_strdup("dirpath"), ft_strdup("basename")));
	print_table(hash_table);
}
// int	main(int argc, char **argv, char **envp)
// {
// 	t_data	data;

// 	data.env = NULL;
// 	alloc_env_hash(envp, &data.env);
// }