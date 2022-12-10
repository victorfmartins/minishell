/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 21:29:01 by asoler            #+#    #+#             */
/*   Updated: 2022/12/10 20:04:52 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtin_env(t_env *hash_table[TABLE_SIZE], int flag)
{
	int	i;

	i = 0;
	while (i < TABLE_SIZE)
	{
		if (flag)
			ft_printf("declare -x ");
		if (hash_table[i])
			print_env_lst(hash_table[i]);
		i++;
	}
}
