/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:54:26 by asoler            #+#    #+#             */
/*   Updated: 2022/12/05 22:43:28 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*get_env_var(t_data *data, char *key)
{
	unsigned int	i;
	int				len;
	t_env			*aux;

	i = hash(key);
	len = ft_strlen(key);
	aux = data->hash_table[i];
	if (!aux)
		return (0);
	while (ft_strncmp(key, aux->key, len))
	{
		if (!aux->next)
			return (0);
		aux = aux->next;
	}
	return (aux);
}
