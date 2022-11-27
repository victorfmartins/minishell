/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 21:35:51 by asoler            #+#    #+#             */
/*   Updated: 2022/11/27 14:32:30 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_hash_table(t_data *data)
{
	int		i;

	i = 0;
	while (i < TABLE_SIZE)
	{
		if (data->hash_table[i])
			ft_envclear(&data->hash_table[i], free);
		i++;
	}
	free(data->hash_table);
}

int	free_and_count_array(char **array, void (*f)(void *))
{
	int	n;

	n = 0;
	while (array[n])
	{
		if (f)
			f(array[n]);
		n++;
	}
	if (f)
		f(array);
	return (n);
}
