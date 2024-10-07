/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:39:21 by vpelc             #+#    #+#             */
/*   Updated: 2024/10/03 18:56:40 by vpelc            ###   ########.fr       */
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
		return (printf("ERROR"));		// ---> no error but skip the command
	return (i - index);
}

int	ft_tokens_fill_list(t_program_data *data)
{
	int	i;
	int	len;

	if (!data || !data->input)
		return (-1);

	i = 0;
	while (data->input[i])
	{
		len = 0;
		if (data->input[i] == '>')
		{
			if (data->input[i + 1] && data->input[i + 1] == '>')
			{
				ft_new_token(">>", data, REDIRECT_APPEND);
				i++;
			}
			else
				ft_new_token(">", data, REDIRECT_OUT);
		}
		else if (data->input[i] == '<')
		{
			if (data->input[i + 1] && data->input[i + 1] == '<')
			{
				ft_new_token("<<", data, REDIRECT_HEREDOC);
				i++;
			}
			else
				ft_new_token("<", data, REDIRECT_IN);
		}
		else if (data->input[i] == '|')
		{
			ft_new_token("|", data, PIPE);
		}
		else if (data->input[i] == '\"')
		{
			len = ft_handle_quotes('\"', data, i + 1);
			if (len < 0)
				return (-1);
			i++;
			if (i - 1 + len + 2 <= (int)ft_strlen(data->input))
				ft_new_token(ft_substr(data->input, i, (size_t)len), data, DOUBLE_QUOTE);
			else
				return (-1);
			i += len;
		}
		else if (data->input[i] == '\'')
		{
			len = ft_handle_quotes('\'', data, i + 1);
			if (len < 0)
				return (-1);
			i++;
			if (i - 1 + len + 2 <= (int)ft_strlen(data->input))
				ft_new_token(ft_substr(data->input, i, (size_t)len), data, SINGLE_QUOTE);
			else
				return (-1);
			i += len;
		}
		else if (data->input[i] != ' ')
		{
			len = ft_handle_words(data, i);
			if (len < 0 || i + len > (int)ft_strlen(data->input))
				return (-1);
			ft_new_token(ft_substr(data->input, i, (size_t)len), data, WORD);
			i += len;
		}
		if (i + 1 > (int)ft_strlen(data->input))
			break;
		i++;
	}
	return (0);
}

