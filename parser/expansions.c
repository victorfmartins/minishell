
#include "../includes/minishell.h"

// Tilde Expansion

//tilde-prefix is a tilde followed by a slash or end of string or a non-alphanumeric character
//in assignments a tild-prefix is a word starting with a tilde and ending with a slash or a column
// a tild-prefix can be in the beginning of a word or after a column or after a slash or after an equal sign

//Exemples:
// vfranco-@doliveira:~/42sp$ echo $LOGNAME
// vfranco-

// vfranco-@doliveira:~/42sp$ CAMINHO=~
// vfranco-@doliveira:~/42sp$ echo $CAMINHO
// /home/vfranco-

// vfranco-@doliveira:~/42sp$ CAMINHO=~:
// vfranco-@doliveira:~/42sp$ echo $CAMINHO
// /home/vfranco-:

// vfranco-@doliveira:~/42sp$ CAMINHO=~/
// vfranco-@doliveira:~/42sp$ echo $CAMINHO
// /home/vfranco-/

// vfranco-@doliveira:~/42sp$ CAMINHO=~/oi
// vfranco-@doliveira:~/42sp$ echo $CAMINHO
// /home/vfranco-/oi

// vfranco-@doliveira:~/42sp$ CAMINHO=~:oi
// vfranco-@doliveira:~/42sp$ echo $CAMINHO
// /home/vfranco-:oi

// vfranco-@doliveira:~/42sp$ CAMINHO=~ddoliv
// vfranco-@doliveira:~/42sp$ echo $CAMINHO
// ~ddoliv

// vfranco-@doliveira:~/42sp$ CAMINHO=~vfranco-
// vfranco-@doliveira:~/42sp$ echo $CAMINHO
// /home/vfranco-

// vfranco-@doliveira:~/42sp$ CAMINHO=~vfranco-:
// vfranco-@doliveira:~/42sp$ echo $CAMINHO
// /home/vfranco-:

// vfranco-@doliveira:~/42sp$ CAMINHO=~vfranco-/
// vfranco-@doliveira:~/42sp$ echo $CAMINHO
// /home/vfranco-/

// vfranco-@doliveira:~/42sp$ CAMINHO=~oi:
// vfranco-@doliveira:~/42sp$ echo $CAMINHO
// ~oi:

// vfranco-@doliveira:~/42sp$ CAMINHO=~:oi
// vfranco-@doliveira:~/42sp$ echo $CAMINHO
// /home/vfranco-:oi

char	*ft_strsubstitute(char *str, char *del, char *insert, int pos)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(insert) + 1));
	if (!new_str)
	{
		ft_printf("Error: malloc failed in ft_strsubstitute");
		exit(1);
	}
	while (str[i] && i < pos)
	{
		new_str[i] = str[i];
		i++;
	}
	while (insert[j])
		new_str[i++] = insert[j++];
	while (str[i - ft_strlen(insert) + ft_strlen(del)])
	{
		new_str[i] = str[i - ft_strlen(insert) + ft_strlen(del)];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*ft_strcpy_until(char *str, char *delimiter)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new_str)
	{
		ft_printf("Error: malloc failed in ft_struntil");
		exit(1);
	}
	while (str[i] && !ft_strchr(delimiter, str[i]))
		new_str[j++] = str[i++];
	new_str[j] = '\0';
	return (new_str);
}

// check if input is a login name
int	ft_islogin(t_data data, char *str)
{
	int		i;
	char	*login;

	i = 0;
	while (data.envp[i])
	{
		if (ft_strncmp(data.envp[i], "LOGNAME=", 8) == 0)
		{
			login = ft_strchr(data.envp[i], '=') + 1;
			if (ft_strncmp(login, str, ft_strlen(str)) == 0)
				return (1);
		}
		i++;
	}
	return (0);
}

// get the home directory of the login name
char	*get_login_path(t_data data, char *str)
{
	int		i;
	char	*login;
	char	*path;

	i = 0;
	while (data.envp[i])
	{
		if (ft_strncmp(data.envp[i], "LOGNAME=", 8) == 0)
		{
			login = ft_strchr(data.envp[i], '=') + 1;
			if (ft_strncmp(login, str, ft_strlen(str)) == 0)
			{
				path = ft_strchr(data.envp[i], '=') + 1;
				return (path);
			}
		}
		i++;
	}
	return (NULL);
}

void	tilde_expansion(t_data data, char **s)
{
	size_t	i;
	char	*word;

	i = 0;
	ft_printf("Before tilde expansion: %s\n", *s);
	while ((*s)[i])
	{
		pass_through_quotes(*s, &i, NULL);
		if ((i == 0 && (*s)[i] == '~') ||
			(i > 0 && ft_strchr(" =", (*s)[i - 1]) && (*s)[i] == '~'))
		{
			if ((*s)[i + 1] == '/' || (*s)[i + 1] == '\0' || (*s)[i + 1] == ':')
			{
				word = ft_strsubstitute(*s, "~", get_env_var(&data, "HOME"), i);
				free(*s);
				*s = word;
				i = i + ft_strlen(get_env_var(&data, "HOME"));
			}
			else
			{
				word = ft_strcpy_until(*s + i + 1, " /:");
				if (ft_islogin(data, word))
				{
					free(*s);
					*s = ft_strsubstitute(*s, word, get_login_path(data, word), i);
					i = i + ft_strlen(get_login_path(data, word));
				}
			}
		}
		i++;
	}
	ft_printf("After tilde expansion: %s\n", *s);
}

// environment variable expansion function
void	env_var_expansion(t_data data, char **s)
{
	size_t	i;
	char	*word;

	i = 0;
	ft_printf("Before env var expansion: %s\n", *s);
	while ((*s)[i])
	{
		pass_through_quotes(*s, &i, NULL);
		if ((*s)[i] == '$')
		{
			word = ft_strcpy_until(*s + i + 1, " /:");
			if (get_env_var(&data, word))
			{
				free(*s);
				*s = ft_strsubstitute(*s, word, get_env_var(&data, word), i);
				i = i + ft_strlen(get_env_var(&data, word));
			}
		}
		i++;
	}
	ft_printf("After env var expansion: %s\n", *s);
}

void	expansions(t_data data, t_cmd **cmds)
{
	t_file	*lst;
	char	**args;
	int		i;

	lst = (*cmds)->outfiles;
	ft_printf("outfiles\n");
	while (lst)
	{
		tilde_expansion(data, &lst->name);
		env_var_expansion(data, &lst->name);
		lst = lst->next;
	}
	lst = (*cmds)->infiles;
	ft_printf("infiles\n");
	while (lst)
	{
		tilde_expansion(data, &lst->name);
		env_var_expansion(data, &lst->name);
		lst = lst->next;
	}
	args = (*cmds)->args;
	i = 0;
	ft_printf("args\n");
	while (args[i])
	{
		tilde_expansion(data, &args[i]);
		env_var_expansion(data, &args[i]);
		i++;
	}
}

// it is missing the expansion of the login name
// it is missing the expansion of the exec_cmd