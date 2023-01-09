#include "../includes/minishell.h"

// vfranco-@doliveira:~/42sp/minishell_space$ ls ~ 
// 42sp  Study  docker  docker-compose.yml  mongodb  nmacn  packages.microsoft

// vfranco-@doliveira:~/42sp/minishell_space$ ls ~/ >| wc -c
// vfranco-@doliveira:~/42sp/minishell_space$ ls ~/ |  
// > wc -l
// 10

void	print_systax_error(char *s)
{
	ft_putstr_fd("bash: syntax error near unexpected token `", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("'\n", 2);
}

// vfranco-@doliveira:~/42sp/minishell_space$ | ls ~/
// bash: syntax error near unexpected token `|'
void	start_with_pipe(char *s)
{
	if (s[0] == '|')
		print_systax_error("|");
}

// vfranco-@doliveira:~/42sp/minishell_space$ ls ~/ ||  wc -c
// 42sp  Study  docker  docker-compose.yml  mongodb  nmacn  packages.microsoft
void	find_double_pipes(char *s)
{
	int		i;
	char	*new_s;

	new_s = malloc(sizeof(char) * (ft_strlen(s) + 1));
	i = 0;
	while (s[i])
	{
		if (s[i] == '|' && s[i + 1] && s[i + 1] == '|')
			break ;
		new_s[i] = s[i];
		i++;
	}
	free(s);
	s = new_s;
}

// vfranco-@doliveira:~/42sp/minishell_space$ ls ~/ |   | wc -c
// bash: syntax error near unexpected token `|'
void	find_spaced_double_pipes(char *s)
{
	int		i;
	int		boo;

	i = 0;
	boo = 0;
	while (s[i])
	{
		if (s[i] == '|' && !boo)
			boo = 1;
		else if (s[i] == '|' && boo)
		{
			print_systax_error("|");
			break ;
		}
		else if (ft_isalnum(s[i]))
			boo = 0;
		i++;
	}
}

// vfranco-@doliveira:~/42sp/minishell_space$ ls ~/ > | wc -c
// bash: syntax error near unexpected token `|'
// vfranco-@doliveira:~/42sp/minishell_space$ ls ~/ >> | wc -l
// bash: syntax error near unexpected token `|'
// vfranco-@doliveira:~/42sp/minishell_space$ < | cat
// bash: syntax error near unexpected token `|'
// vfranco-@doliveira:~/42sp/minishell_space$ << | cat
// bash: syntax error near unexpected token `|'
void	find_pipe_redir_conflict(char *s, int m)
{
	int		i;
	int		boo;

	i = 0;
	boo = 0;
	while (s[i])
	{
		if (s[i] == '>' * (m == O_REDIR) + '<' * (m == I_REDIR) &&
			s[i + 1] && !boo &&
			s[i + 1] != '>' * (m == O_REDIR) + '<' * (m == I_REDIR))
			boo = 1;
		else if (s[i] == '|' && boo)
		{
			print_systax_error("|");
			break ;
		}
		else if (ft_isalnum(s[i]))
			boo = 0;
		i++;
	}
}

// vfranco-@doliveira:~/42sp/minishell_space$ ls ~/ > >f2
// bash: syntax error near unexpected token `>'
// vfranco-@doliveira:~/42sp/minishell_space$ < <wc cat
// bash: syntax error near unexpected token `<'
void	find_spaced_double_redirs(char *s, int m)
{
	int		i;
	int		boo;
	char	*str;

	i = 0;
	boo = 0;
	while (s[i])
	{
		if (s[i] == '>' * (m == O_REDIR) + '<' * (m == I_REDIR) &&
			s[i + 1] && !boo &&
			s[i + 1] != '>' * (m == O_REDIR) + '<' * (m == I_REDIR))
			boo = 1;
		else if (s[i] == '>' * (m == O_REDIR) + '<' * (m == I_REDIR) && boo)
		{
			str = malloc(sizeof(char) * (1 + 1));
			str[0] = '>' * (m == O_REDIR) + '<' * (m == I_REDIR);
			str[1] = '\0';
			print_systax_error(str);
			free(str);
			break ;
		}
		else if (ft_isalnum(s[i]))
			boo = 0;
		i++;
	}
}

// vfranco-@doliveira:~/42sp/minishell_space$ ls ~/ >|
// bash: syntax error near unexpected token `newline'
// vfranco-@doliveira:~/42sp/minishell_space$ ls ~/ >   
// bash: syntax error near unexpected token `newline'
void	unexpecte_newline(char *s)
{
	int		i;
	int		boo;

	i = 0;
	boo = 0;
	while (s[i])
	{
		if (s[i] == '>' && s[i + 1] && s[i] != '>' && !boo)
			boo = 1;
		else if (s[i] == '|' && boo)
		{
			print_systax_error("newline");
			break ;
		}
		else if (ft_isalnum(s[i]))
			boo = 0;
		i++;
	}
}

void	lexical_analysis(t_data *data)
{
	start_with_pipe(data->line);
	find_double_pipes(data->line);
	find_spaced_double_pipes(data->line);
	find_pipe_redir_conflict(data->line, O_REDIR);
	find_pipe_redir_conflict(data->line, I_REDIR);
	find_spaced_double_redirs(data->line, O_REDIR);
	find_spaced_double_redirs(data->line, I_REDIR);
	unexpecte_newline(data->line);
}