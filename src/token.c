/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:39:21 by vpelc             #+#    #+#             */
/*   Updated: 2024/10/11 15:53:04 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_handle_words(t_program_data *data, int index)
{
	int	i;

	i = index;
	while (data->input[i] != ' ' && data->input[i])
		i++;
	return (i - index);
}

int	ft_handle_quotes(char type, t_program_data *data, int index)
{
	int	i;

	i = index;
	while (data->input[i] != type && data->input[i])
		i++;
	if (i >= (int)ft_strlen(data->input))
		return (printf("ERROR"));
	return (i - index);
}
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

int	process_quotes(t_program_data *data, int *i, char quote)
{
	int		len;
	char	*substr;

	len = ft_handle_quotes(quote, data, *i + 1);
	if (len < 0 || *i + len + 2 > (int)ft_strlen(data->input))
		return (-1);
	(*i)++;
	substr = ft_substr(data->input, *i, (size_t)len);
	if (!substr)
		return (-1);
	ft_new_token(substr, data, (quote == '\"') ? DOUBLE_QUOTE : SINGLE_QUOTE);
	free(substr);
	*i += len;
	return (0);
}

int	process_word(t_program_data *data, int *i)
{
	int		len;
	char	*substr;

	len = ft_handle_words(data, *i);
	if (len < 0 || *i + len > (int)ft_strlen(data->input))
		return (-1);
	substr = ft_substr(data->input, *i, (size_t)len);
	if (!substr)
		return (-1);
	ft_new_token(substr, data, WORD);
	free(substr);
	*i += len;
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
			continue ;
		if (data->input[i] == '\"' || data->input[i] == '\'')
		{
			if (process_quotes(data, &i, data->input[i]) < 0)
				return (-1);
			continue ;
		}
		if (data->input[i] != ' ' && process_word(data, &i) < 0)
			return (-1);
		i++;
	}
	return (0);
}
