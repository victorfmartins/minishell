/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_one_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:08:29 by asoler            #+#    #+#             */
/*   Updated: 2022/09/28 01:16:13 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	del_one_var(t_env *lst, void (*del)(void*))
{
	del(lst->key);
	del(lst->value);
	free(lst);
}
