/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfranco- <vfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 22:02:17 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/18 22:02:50 by vfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_file	*ft_filenew(char *name, int type)
{
	t_file	*lst;

	lst = malloc(sizeof(t_file));
	if (!lst)
		return (NULL);
	lst->name = name;
	lst->type = type;
	lst->next = NULL;
	return (lst);
}

void	ft_fileadd_back(t_file **lst, t_file *new)
{
	t_file	*p;

	if (!lst || !new)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		p = *lst;
		while (p->next)
			p = p->next;
		p->next = new;
	}
}

t_cmd	*ft_cmdnew(char *frase)
{
	t_cmd	*lst;

	lst = malloc(sizeof(t_cmd));
	if (!lst)
		return (NULL);
	lst->line = frase;
	lst->next = NULL;
	return (lst);
}

void	ft_cmd_addback(t_cmd **lst, t_cmd *new)
{
	t_cmd	*p;

	if (!lst || !new)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		p = *lst;
		while (p->next)
			p = p->next;
		p->next = new;
	}
}
