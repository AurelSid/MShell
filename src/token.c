/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:39:21 by vpelc             #+#    #+#             */
/*   Updated: 2024/11/04 17:18:52 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	process_redirects(t_program_data *data, int *i)
{
	if (data->input[*i] == '>')
	{
		if (data->input[*i + 1] == '>')
		{
			ft_new_token(">>", data, REDIRECT_APPEND);
			(*i)++;
		}
		else
			ft_new_token(">", data, REDIRECT_OUT);
	}
	else if (data->input[*i] == '<')
	{
		if (data->input[*i + 1] == '<')
		{
			ft_new_token("<<", data, REDIRECT_HEREDOC);
			(*i)++;
		}
		else
			ft_new_token("<", data, REDIRECT_IN);
	}
	else if (data->input[*i] == '|')
		ft_new_token("|", data, PIPE);
	else
		return (0);
	return (1);
}

int	process_word(t_program_data *data, int *i)
{
	int	j;
	char *tmp_name;
	j = *i;
	while (data->input[j] && (data->input[j] != ' ' && data->input[j] != '>'
			&& data->input[j] != '<'))
	{
		if (data->input[j] == '\'' || data->input[j] == '\"')
			j += ft_handle_quotes(data->input, j);
		else
			j += ft_handle_words(data->input, j);
	}
	tmp_name = ft_substr(data->input, *i, (size_t)(j - *i));
	ft_new_token(tmp_name, data, WORD);
	free(tmp_name);
	*i = j;
	return (0);
}

int	ft_tokens_fill_list(t_program_data *data)
{
	int	i;

	i = 0;
	if (!data || !data->input)
		return (-1);
	while (data->input[i])
	{
		if (process_redirects(data, &i))
		{
			i++;
			continue ;
		}
		else if (data->input[i] != ' ')
			process_word(data, &i);
		if (i + 1 > (int)ft_strlen(data->input))
			break ;
		i++;
	}
	return (0);
}
