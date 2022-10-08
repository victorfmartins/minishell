/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 20:42:25 by asoler            #+#    #+#             */
/*   Updated: 2022/10/08 20:24:52 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*create_var(char	*key, char *value)
{
	t_env	*result;

	result = malloc(sizeof(t_env));
	if (!result)
		return (0);
	result->key = ft_strdup(key);
	result->value = ft_strdup(value);
	result->next = NULL;
	return (result);
}
