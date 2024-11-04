/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_fill_list_r.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:18:21 by vpelc             #+#    #+#             */
/*   Updated: 2024/11/04 15:50:18 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_redir(t_token **tmp, t_redirection **redir, t_program_data *data)
{
	if ((*tmp) && (((*tmp)->type == REDIRECT_IN
				|| (*tmp)->type == REDIRECT_APPEND
				|| (*tmp)->type == REDIRECT_HEREDOC
				|| (*tmp)->type == REDIRECT_OUT)) && (!(*tmp)->next
			|| (*tmp)->next->type != WORD))
	{
		*tmp = (*tmp)->next;
		write(2, "syntax error near unexpected token `newline'\n", 46);
		data->exit_status = 2;
	}
	while ((*tmp) && (((*tmp)->type == REDIRECT_IN
				|| (*tmp)->type == REDIRECT_APPEND
				|| (*tmp)->type == REDIRECT_HEREDOC
				|| (*tmp)->type == REDIRECT_OUT) && (*tmp)->next->type == WORD))
	{
		*redir = ft_new_redirection((*tmp)->next->content, *redir,
				(*tmp)->type);
		*tmp = (*tmp)->next->next;
	}
	return (0);
}

void	support_1(t_program_data *data, t_redirection **redir, t_token **tmp)
{
	if (data->token_top->type == PIPE)
	{
		write(2, " syntax error near unexpected token `|'\n", 41);
		data->exit_status = 2;
	}
	ft_check_redir(tmp, redir, data);
}

void	support_2(t_program_data *data, t_redirection **redir, t_token **tmp,
		char *cmd_n, char **args)
{
	while (*tmp && ((*tmp)->type != PIPE))
	{
		if ((*tmp)->type == REDIRECT_IN || (*tmp)->type == REDIRECT_APPEND
			|| (*tmp)->type == REDIRECT_HEREDOC || (*tmp)->type == REDIRECT_OUT)
			ft_check_redir(tmp, redir, data);
		else if ((*tmp)->type == WORD)
			ft_check_args(data, tmp, cmd_n, args);
	}
}

t_token	*ft_commands_fill_list_r(t_program_data *data, t_token *tmp,
		char **args, char **opt)
{
	t_command		*cmd;
	t_redirection	*redir;
	char			*cmd_n;

	redir = NULL;
	support_1(data, &redir, &tmp);
	if (!tmp || tmp->type == PIPE)
		cmd_n = NULL;
	else
	{
		if (tmp->type == WORD)
		{
			ft_checkspchar(&tmp->content, data);
			cmd_n = tmp->content;
		}
		else
			return (0);
		tmp = tmp->next;
		if (ft_strcmp(cmd_n, "exit") && ft_strcmp(cmd_n, "cd"))
			ft_check_opt(data, &tmp, cmd_n, opt);
		support_2(data, &redir, &tmp, cmd_n, args);
	}
	cmd = ft_new_command(cmd_n, data, *args, *opt);
	cmd->redirection_list = redir;
	return (tmp);
}
