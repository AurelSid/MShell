/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:18:21 by vpelc             #+#    #+#             */
/*   Updated: 2024/10/07 16:31:56 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
		/!\ LEAKS ON STRJOIN /!\
*/

/* t_token	*ft_commands_fill_list_c(t_program_data *data, t_token *tmp,
		char **args, char **opt)
{
	t_command	*cmd;

	tmp = tmp->next;
	while (tmp && (tmp->content[0] == '-' && (tmp->type == WORD
				|| tmp->type == SINGLE_QUOTE || tmp->type == DOUBLE_QUOTE)))
	{
		*opt = ft_strjoin(*opt, tmp->content);
		tmp = tmp->next;
		*opt = ft_strjoin(*opt, " ");
	}
	while (tmp && (tmp->type == WORD || tmp->type == SINGLE_QUOTE
			|| tmp->type == DOUBLE_QUOTE))
	{
		*args = ft_strjoin(*args, tmp->content);
		tmp = tmp->next;
		*args = ft_strjoin(*args, " ");
	}
	cmd = ft_new_command(data->token_top->content, data, *args, *opt);
	while ((tmp && tmp->next) && tmp->type != PIPE)
	{
		if ((tmp->type == REDIRECT_IN || tmp->type == REDIRECT_OUT
				|| tmp->type == REDIRECT_HEREDOC
				|| tmp->type == REDIRECT_APPEND) && tmp->next->type == WORD)
			ft_new_redirection(tmp->next->content, cmd, tmp->type);
		else
			printf("ERROR\n");
		tmp = tmp->next->next;
	}
	return (tmp);
} */

t_token	*ft_commands_fill_list_r(t_program_data *data, t_token *tmp,
		char **args, char **opt)
{
	t_command		*cmd;
	t_redirection	*redir;
	char			*cmd_n;
	char			*tmp_str;

	redir = NULL;
	while (tmp && ((tmp->type == REDIRECT_IN || tmp->type == REDIRECT_APPEND
				|| tmp->type == REDIRECT_HEREDOC || tmp->type == REDIRECT_OUT)
			&& (tmp->next->type == WORD || tmp->next->type == DOUBLE_QUOTE
				|| tmp->next->type == SINGLE_QUOTE)))
	{
		redir = ft_new_redirection(tmp->next->content, redir, tmp->type);
		tmp = tmp->next->next;
	}
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
			if (tmp->type == DOUBLE_QUOTE)
				tmp_str = ft_db_quotes(tmp->content, *data);
			else if (tmp->type == WORD)
				tmp_str = ft_word(tmp->content, *data);
			else
				tmp_str = tmp->content;
			*opt = ft_strjoin(*opt, tmp_str);
			tmp = tmp->next;
			*opt = ft_strjoin(*opt, " ");
		}
		while (tmp && (tmp->type == WORD || tmp->type == SINGLE_QUOTE
				|| tmp->type == DOUBLE_QUOTE))
		{
			if (tmp->type == DOUBLE_QUOTE)
				tmp_str = ft_db_quotes(tmp->content, *data);
			else if (tmp->type == WORD)
				tmp_str = ft_word(tmp->content, *data);
			else
				tmp_str = tmp->content;
			*args = ft_strjoin(*args, tmp_str);
			tmp = tmp->next;
			*args = ft_strjoin(*args, " ");
		}
	}
	cmd = ft_new_command(cmd_n, data, *args, *opt);
	while ((tmp && tmp->next) && tmp->type != PIPE)
	{
		if ((tmp->type == REDIRECT_IN || tmp->type == REDIRECT_OUT
				|| tmp->type == REDIRECT_HEREDOC
				|| tmp->type == REDIRECT_APPEND)
			&& (tmp->next->type == WORD || tmp->next->type == SINGLE_QUOTE
				|| tmp->next->type == DOUBLE_QUOTE))
			redir = ft_new_redirection(tmp->next->content, redir, tmp->type);
		else
			printf("ERROR\n");
		tmp = tmp->next->next;
	}
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
//	if (tmp->type >= REDIRECT_IN && tmp->type <= REDIRECT_APPEND)
		tmp = ft_commands_fill_list_r(data, tmp, &args, &opt);
//	else if (tmp->type == WORD)
//		tmp = ft_commands_fill_list_c(data, tmp, &args, &opt);
//	else
//		printf("ERROR\n");
	if ((tmp && tmp->next) && tmp->type == PIPE)
	{
		tmp = tmp->next;
		data->token_top = tmp;
		ft_commands_fill_list(data);
	}
}
