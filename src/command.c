/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:18:21 by vpelc             #+#    #+#             */
/*   Updated: 2024/10/22 14:08:53 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_redir(t_token **tmp, t_redirection **redir)
{
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

int	ft_check_opt(t_program_data *data, t_token **tmp, char *cmd_n, char **opt)
{
	char	*tmp_str;
	char	*free_tmp;

	while ((*tmp) && ((*tmp)->content[0] == '-' && (*tmp)->type == WORD))
	{
		if (ft_strcmp(cmd_n, "export"))
		{
			ft_checkspchar(&(*tmp)->content, data);
			tmp_str = (*tmp)->content;
		}
		free_tmp = *opt;
		*opt = ft_strjoin(free_tmp, (*tmp)->content);
		free(free_tmp);
		(*tmp) = (*tmp)->next;
		free_tmp = *opt;
		*opt = ft_strjoin(free_tmp, " ");
		free(free_tmp);
	}
	return (0);
}

int	ft_check_args(t_program_data *data, t_token **tmp, char *cmd_n, char **args)
{
	char	*tmp_str;
	char	*free_tmp;

	while ((*tmp) && (*tmp)->type == WORD)
	{
		if (ft_strcmp(cmd_n, "export"))
		{
			ft_checkspchar(&(*tmp)->content, data);
			tmp_str = (*tmp)->content;
		}
		free_tmp = *args;
		*args = ft_strjoin(free_tmp, (*tmp)->content);
		free(free_tmp);
		(*tmp) = (*tmp)->next;
		free_tmp = *args;
		*args = ft_strjoin(free_tmp, " ");
		free(free_tmp);
	}
	return (0);
}

t_token	*ft_commands_fill_list_r(t_program_data *data, t_token *tmp,
		char **args, char **opt)
{
	t_command		*cmd;
	t_redirection	*redir;
	char			*cmd_n;

	redir = NULL;
	ft_check_redir(&tmp, &redir);
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
		ft_check_opt(data, &tmp, cmd_n, opt);
		while (tmp && (tmp->type != PIPE))
		{
			if (tmp->type == REDIRECT_IN || tmp->type == REDIRECT_APPEND
				|| tmp->type == REDIRECT_HEREDOC || tmp->type == REDIRECT_OUT)
				ft_check_redir(&tmp, &redir);
			else if (tmp->type == WORD)
				ft_check_args(data, &tmp, cmd_n, args);
		}
	}
	cmd = ft_new_command(cmd_n, data, *args, *opt);
	cmd->redirection_list = redir;
	return (tmp);
}

void	ft_commands_fill_list(t_program_data *data)
{
	t_token	*tmp;
	char	*opt;
	char	*args;

	opt = ft_calloc(1, 1);
	if (!opt)
		return ;
	args = ft_calloc(1, 1);
	if (!args)
		return ;
	tmp = data->token_top;
	tmp = ft_commands_fill_list_r(data, tmp, &args, &opt);
	if ((tmp && tmp->next) && tmp->type == PIPE)
	{
		tmp = tmp->next;
		data->token_top = tmp;
		ft_commands_fill_list(data);
	}
	if (opt)
		free(opt);
	if (args)
		free(args);
}