/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:18:21 by vpelc             #+#    #+#             */
/*   Updated: 2024/10/21 16:29:52 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_type(t_token **tmp, t_redirection **redir)
{
	while ((*tmp) && (((*tmp)->type == REDIRECT_IN
				|| (*tmp)->type == REDIRECT_APPEND
				|| (*tmp)->type == REDIRECT_HEREDOC
				|| (*tmp)->type == REDIRECT_OUT) && ((*tmp)->next->type == WORD
				|| (*tmp)->next->type == DOUBLE_QUOTE
				|| (*tmp)->next->type == SINGLE_QUOTE)))
	{
		*redir = ft_new_redirection((*tmp)->next->content, *redir,
				(*tmp)->type);
		*tmp = (*tmp)->next->next;
	}
	return (0);
}
int	ft_check_2(t_token **tmp, t_redirection **redir)
{
	while ((*tmp && (*tmp)->next) && (*tmp)->type != PIPE)
	{
		if (((*tmp)->type == REDIRECT_IN || (*tmp)->type == REDIRECT_OUT
				|| (*tmp)->type == REDIRECT_HEREDOC
				|| (*tmp)->type == REDIRECT_APPEND)
			&& ((*tmp)->next->type == WORD || (*tmp)->next->type == SINGLE_QUOTE
				|| (*tmp)->next->type == DOUBLE_QUOTE))
			*redir = ft_new_redirection((*tmp)->next->content, *redir,
					(*tmp)->type);
		else
			return (0);
		(*tmp) = (*tmp)->next->next;
	}
	return (0);
}
int	ft_check_3(t_token **tmp, t_redirection **redir)
{
	while ((*tmp && (*tmp)->next) && (*tmp)->type != PIPE)
	{
		if (((*tmp)->type == REDIRECT_IN || (*tmp)->type == REDIRECT_OUT
				|| (*tmp)->type == REDIRECT_HEREDOC
				|| (*tmp)->type == REDIRECT_APPEND)
			&& ((*tmp)->next->type == WORD || (*tmp)->next->type == SINGLE_QUOTE
				|| (*tmp)->next->type == DOUBLE_QUOTE))
			*redir = ft_new_redirection((*tmp)->next->content, *redir,
					(*tmp)->type);
		else
			return (0);
		(*tmp) = (*tmp)->next->next;
	}
	return (0);
}

t_token	*ft_commands_fill_list_r(t_program_data *data, t_token *tmp,
		char **args, char **opt)
{
	t_command		*cmd;
	t_redirection	*redir;
	char			*cmd_n;
	char			*free_tmp;

	redir = NULL;
	ft_check_type(&tmp, &redir);
	if (!tmp || tmp->type == PIPE)
		cmd_n = NULL;
	else
	{
		if (tmp->type == WORD)
			cmd_n = tmp->content;
		tmp = tmp->next;
		while (tmp && (tmp->content[0] == '-' && (tmp->type == WORD
					|| tmp->type == SINGLE_QUOTE || tmp->type == DOUBLE_QUOTE)))
		{
			free_tmp = *opt;
			*opt = ft_strjoin(free_tmp, tmp->content);
			free(free_tmp);
			tmp = tmp->next;
			free_tmp = *opt;
			*opt = ft_strjoin(free_tmp, " ");
			free(free_tmp);
		}
		while (tmp && (tmp->type == WORD || tmp->type == SINGLE_QUOTE
				|| tmp->type == DOUBLE_QUOTE))
		{
			free_tmp = *args;
			*args = ft_strjoin(free_tmp, tmp->content);
			free(free_tmp);
			tmp = tmp->next;
			free_tmp = *args;
			*args = ft_strjoin(free_tmp, " ");
			free(free_tmp);
		}
	}
	cmd = ft_new_command(cmd_n, data, *args, *opt);
	ft_check_2(&tmp, &redir);
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