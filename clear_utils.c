/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfranco- <vfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 21:35:51 by asoler            #+#    #+#             */
/*   Updated: 2022/10/20 08:48:49 by vfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
