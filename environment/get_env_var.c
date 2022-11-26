/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfranco- <vfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:54:26 by asoler            #+#    #+#             */
/*   Updated: 2022/11/23 10:10:35 by vfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env_var(t_data *data, char *key)
{
	unsigned int	i;
	int				len;
	t_env			*aux;

	i = hash(key);
	len = ft_strlen(key);
	aux = data->hash_table[i];
	if (!aux)
		return (NULL);
	while (ft_strncmp(key, aux->key, len))
	{
		if (!aux->next)
			return (0);
		aux = aux->next;
	}
	return (aux->value);
}
