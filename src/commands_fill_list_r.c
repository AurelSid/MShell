/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_fill_list_r.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:18:21 by vpelc             #+#    #+#             */
/*   Updated: 2024/11/02 12:42:55 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*ft_commands_fill_list_r(t_program_data *data, t_token *tmp,
		char **args, char **opt)
{
	t_command		*cmd;
	t_redirection	*redir;
	char			*cmd_n;

	redir = NULL;
	if (data->token_top->type == PIPE)
	{
		write(2, " syntax error near unexpected token `|'\n", 41);
		data->exit_status = 2;
	}
	ft_check_redir(&tmp, &redir, data);
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
		while (tmp && (tmp->type != PIPE))
		{
			if (tmp->type == REDIRECT_IN || tmp->type == REDIRECT_APPEND
				|| tmp->type == REDIRECT_HEREDOC || tmp->type == REDIRECT_OUT)
				ft_check_redir(&tmp, &redir, data);
			else if (tmp->type == WORD)
				ft_check_args(data, &tmp, cmd_n, args);
		}
	}
	cmd = ft_new_command(cmd_n, data, *args, *opt);
	cmd->redirection_list = redir;
	return (tmp);
}
