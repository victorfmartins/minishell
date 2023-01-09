/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 21:29:01 by asoler            #+#    #+#             */
/*   Updated: 2022/12/10 20:28:09 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtin_env(t_env *hash_table[TABLE_SIZE], int flag_export)
{
	int	i;

	i = 0;
	while (i < TABLE_SIZE)
	{
		if (hash_table[i])
			print_env_lst(hash_table[i], flag_export);
		i++;
	}
}
