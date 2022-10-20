/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_structure_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfranco- <vfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 22:06:52 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/20 17:09:14 by vfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*ft_split_to_cmd_lst(char *line, char delimiter)
{
	char	**frases;
	t_cmd	*lst;
	int		i;

	frases = ft_split(line, delimiter);
	lst = NULL;
	i = 0;
	while (frases[i])
	{
		ft_cmd_addback(&lst, ft_cmdnew(ft_strdup(frases[i])));
		i++;
	}
	ft_clear_array(frases);
	return (lst);
}

static void	pass_through_quotes(char *str, size_t *i, size_t *size)
{
	if (str[*i] == '\'' && ft_strchr(str + *i + 1, '\''))
	{
		if (size)
			*size += ft_strchr(str + *i + 1, '\'') - str - *i;
		*i = ft_strchr(str + *i + 1, '\'') - str;
	}
	if (str[*i] == '\"' && ft_strchr(str + *i + 1, '\"'))
	{
		if (size)
			*size += ft_strchr(str + *i + 1, '\"') - str - *i;
		*i = ft_strchr(str + *i + 1, '\"') - str;
	}
}

size_t	ft_new_line_size(char *str, int mode)
{
	size_t	size;
	size_t	i;

	i = 0;
	size = 0;
	while (str[i])
	{
		pass_through_quotes(str, &i, &size);
		if (str[i] == '>' * (mode == REDIR) + '<' * (mode == DIR))
		{
			i++;
			if (str[i] == '>' * (mode == REDIR) + '<' * (mode == DIR))
				i++;
			while (str[i] && !ft_isspace(str[i]) && !ft_isredirect(str[i]))
			{
				pass_through_quotes(str, &i, NULL);
				i++;
			}
			if (str[i] == '>' * (mode == REDIR) + '<' * (mode == DIR))
				continue ;
		}
		i++;
		size++;
	}
	return (size);
}

// [ERROR]
// in ft_split_to_cmd_lst: frases = ft_split(line, delimiter);
// can return frase that is empty