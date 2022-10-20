/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_structures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfranco- <vfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 22:02:17 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/20 07:03:03 by vfranco-         ###   ########.fr       */
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

void	ft_file_addback(t_file **lst, t_file *new)
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

// int	main(void)
// {
// 	t_cmd	*cmd;
// 	t_cmd	*p;
// 	t_cmd	*p_next;
// 	t_file	*file;

// 	cmd = NULL;
// 	ft_cmd_addback(&cmd, ft_cmdnew(ft_strdup("victor franco martins")));
// 	ft_cmd_addback(&cmd, ft_cmdnew(ft_strdup("debora de oliveira")));
// 	ft_cmd_addback(&cmd, ft_cmdnew(ft_strdup("angela soler")));
// 	p = cmd;
// 	while (p)
// 	{
// 		p_next = p->next;
// 		get_cmd_attributes(&p);
// 		file = NULL;
// 		ft_file_addback(&file, ft_filenew(ft_strdup("(in1) "), DIR));
// 		ft_file_addback(&file, ft_filenew(ft_strdup("(in2) "), DIR));
// 		ft_file_addback(&file, ft_filenew(ft_strdup("(in3)"), DIR));
// 		p->infiles = file;
// 		file = NULL;
// 		ft_file_addback(&file, ft_filenew(ft_strdup("(out1) "), REDIR));
// 		ft_file_addback(&file, ft_filenew(ft_strdup("(out2) "), REDIR));
// 		ft_file_addback(&file, ft_filenew(ft_strdup("(out3)"), REDIR));
// 		p->outfiles = file;
// 		p = p_next;
// 	}
// 	print_cmd_lst(cmd);
// 	ft_cmdclear(&cmd, free);
// }
