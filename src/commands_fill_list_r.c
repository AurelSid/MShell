/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_fill_list_r.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:18:21 by vpelc             #+#    #+#             */
/*   Updated: 2024/11/14 13:27:19 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_redir(t_token **tmp, t_redirection **redir)
{
	if ((*tmp) && (((*tmp)->type == REDIRECT_IN
				|| (*tmp)->type == REDIRECT_APPEND
				|| (*tmp)->type == REDIRECT_HEREDOC
				|| (*tmp)->type == REDIRECT_OUT)) && (!(*tmp)->next
			|| (*tmp)->next->type != WORD))
	{
		*tmp = (*tmp)->next;
		write(2, "syntax error near unexpected token `newline'\n", 46);
		ft_return_data()->exit_status = 2;
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

void	support_1(t_redirection **redir, t_token **tmp)
{
	if (ft_return_data()->token_top->type == PIPE)
	{
		write(2, " syntax error near unexpected token `|'\n", 41);
		ft_return_data()->exit_status = 2;
	}
	ft_check_redir(tmp, redir);
}

void	support_2(t_redirection **redir, t_token **tmp, char *cmd_n,
		char **args)
{
	while (*tmp && ((*tmp)->type != PIPE))
	{
		if ((*tmp)->type == REDIRECT_IN || (*tmp)->type == REDIRECT_APPEND
			|| (*tmp)->type == REDIRECT_HEREDOC || (*tmp)->type == REDIRECT_OUT)
			ft_check_redir(tmp, redir);
		else if ((*tmp)->type == WORD)
			ft_check_args(tmp, cmd_n, args);
	}
}

t_token	*ft_commands_fill_list_r(t_token *tmp, char **args, char **opt)
{
	t_command		*cmd;
	t_redirection	*redir;
	char			*cmd_n;

	redir = NULL;
	support_1(&redir, &tmp);
	if (!tmp || tmp->type == PIPE)
		cmd_n = NULL;
	else
	{
		if (tmp->type == WORD)
		{
			ft_checkspchar(&tmp->content);
			cmd_n = ft_strtrim_args(tmp->content, 0, 0);
		}
		else
			return (0);
		tmp = tmp->next;
		if (ft_strcmp(cmd_n, "exit") && ft_strcmp(cmd_n, "cd"))
			ft_check_opt(&tmp, cmd_n, opt);
		support_2(&redir, &tmp, cmd_n, args);
	}
	cmd = ft_new_command(cmd_n, *args, *opt);
	cmd->redirection_list = redir;
	return (free(cmd_n), tmp);
}
