/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfranco- <vfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:08:18 by vfranco-          #+#    #+#             */
/*   Updated: 2022/11/22 16:12:29 by vfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	tilde_expansion(t_data data, char **s)
{
	size_t	i;
	char	*word;

	i = 0;
	while ((*s)[i])
	{
		pass_through_quotes(*s, &i, NULL);
		if ((i == 0 && (*s)[i] == '~') ||
			(i > 0 && ft_strchr(" =", (*s)[i - 1]) && (*s)[i] == '~'))
		{
			if ((*s)[i + 1] == '/' || (*s)[i + 1] == '\0' || (*s)[i + 1] == ':')
			{
				word = ft_strsubstitute(*s, "~", get_env_var(&data, "HOME"), i);
				if (!word)
					return ;
				free(*s);
				*s = word;
				i = i + ft_strlen(get_env_var(&data, "HOME"));
			}
		}
		i++;
	}
}

void	env_var_expansion(t_data data, char **s)
{
	size_t	i;
	char	*word;
	char	*s_new;

	i = 0;
	while ((*s)[i])
	{
		pass_through_quotes(*s, &i, NULL);
		if ((*s)[i] == '$')
		{
			word = ft_strcpy_until(*s + i + 1, " /:");
			if (!word)
				return ;
			if (get_env_var(&data, word))
			{
				s_new = ft_strsubstitute(*s, word, get_env_var(&data, word), i);
				if (!s_new)
					return ;
				free(*s);
				*s = s_new;
				i = i + ft_strlen(get_env_var(&data, word));
			}
		}
		i++;
	}
}

void	expand_file(t_data data, t_cmd ***cmds, int mode)
{
	t_file	*lst;

	if (mode == O_REDIR)
		lst = (*(*cmds))->outfiles;
	else
		lst = (*(*cmds))->infiles;
	while (lst)
	{
		tilde_expansion(data, &lst->name);
		env_var_expansion(data, &lst->name);
		lst = lst->next;
	}
}

void	expand_args(t_data data, t_cmd ***cmds)
{
	char	**args;
	int		i;

	args = (*(*cmds))->args;
	i = 0;
	while (args[i])
	{
		tilde_expansion(data, &args[i]);
		env_var_expansion(data, &args[i]);
		i++;
	}
}

void	expansions(t_data data, t_cmd **cmds)
{
	expand_file(data, &cmds, O_REDIR);
	expand_file(data, &cmds, I_REDIR);
	expand_args(data, &cmds);
}

// it is missing the expansion of the exec_cmd