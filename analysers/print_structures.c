/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_structures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfranco- <vfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 22:05:10 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/18 22:05:21 by vfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_file_lst(t_file *lst)
{
	while (lst)
	{
		ft_printf("file: %s\ttype: %i\n", (char *)lst->name, lst->type);
		lst = lst->next;
	}
}

void	print_cmd_lst(t_cmd *lst)
{
	while (lst)
	{
		ft_printf("%s\n", (char *)lst->line);
		print_file_lst(lst->outfiles);
		print_file_lst(lst->infiles);
		lst = lst->next;
	}
}
