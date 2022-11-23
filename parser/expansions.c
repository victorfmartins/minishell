/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfranco- <vfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:08:18 by vfranco-          #+#    #+#             */
/*   Updated: 2022/11/23 10:52:39 by vfranco-         ###   ########.fr       */
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
				i = i + ft_strlen(get_env_var(&data, "HOME")) - 1;
			}
		}
		i++;
	}
}

void	env_var_substitution(t_data data, char ***s, size_t *i)
{
	char	*word;
	char	*s_new;
	char	*env_var;

	word = ft_strcpy_until((*(*s)) + (*i), " /:");
	if (!word)
		return ;
	if (word[1])
	{
		env_var = get_env_var(&data, word + 1);
		if (!env_var)
			return (free(word));
		s_new = ft_strsubstitute((*(*s)), word, env_var, *i);
		free((*(*s)));
		(*(*s)) = s_new;
		if (!s_new)
			return (free(word));
		*i = *i + ft_strlen(env_var) - 1;
	}
	free(word);
}

void	env_var_expansion(t_data data, char **s)
{
	size_t	i;

	i = 0;
	while ((*s)[i])
	{
		pass_through_quotes(*s, &i, NULL);
		if ((*s)[i] == '$')
			env_var_substitution(data, &s, &i);
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