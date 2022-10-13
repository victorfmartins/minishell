#include "../includes/minishell.h"

// macros
// # define'<'  1
// # define'<<' 2
// # define'>'  3
// # define'>>' 4
// # define'|'  5

// typedef enum //um para opp e otro para words

typedef struct s_cmd {
	char	*exec_cmd;
	char	*args;
	int		type; //builtin or not ou se é um comando absoluto (que começa com /)
	void	*next;
	void	*previews;
} t_cmd;

typedef struct s_file {
	char *file;
	void *next;
	void *previwes;
} t_file;

typedef struct s_opperators {
	int type;
	void *next;
	void *previwes;
} t_opperators;

t_list	*tokenization(t_data *data)
{
	t_list	*token_lst;
	int		i;

	token_lst = NULL;
	i = 0;
	while (data->line[i])
	{
		// ft_printf("%d\t", i);
		// ft_printf("%c\t", data->line[i]);
		// ft_printf("%p\n", data->line + i);
		if (data->line[i] == '|')
			ft_lstadd_back(&token_lst, ft_lstnew("|"));
		else if (data->line[i] == '&')
			ft_lstadd_back(&token_lst, ft_lstnew("&"));
		else if (ft_strncmp(data->line + i, "<<", 2) == 0 && i++)
			ft_lstadd_back(&token_lst, ft_lstnew("<<"));
		else if (data->line[i] == '<')
			ft_lstadd_back(&token_lst, ft_lstnew("<"));
		else if (ft_strncmp(data->line + i, ">>", 2) == 0 && i++)
			ft_lstadd_back(&token_lst, ft_lstnew(">>"));
		else if (data->line[i] == '>')
			ft_lstadd_back(&token_lst, ft_lstnew(">"));
		else if (data->line[i] == '\'')
			ft_lstadd_back(&token_lst, ft_lstnew("\'"));
		else if (data->line[i] == '\"')
			ft_lstadd_back(&token_lst, ft_lstnew("\""));
		else if (data->line[i] == '-')
			ft_lstadd_back(&token_lst, ft_lstnew("-"));
		else if (ft_isalnum(data->line[i]))
			ft_lstadd_back(&token_lst, ft_lstnew(ft_worddup(data->line + i)));
		i++;
	}
	return (token_lst);
}
		// else if (data->line[i] == '-' && data->line[i + 1] && ft_isalnum(data->line[i + 1]) && i++)

void	print_lst(t_list *lst)
{
	while (lst)
	{
		printf("%s\n", (char *)lst->content);
		lst = lst->next;
	}
}
