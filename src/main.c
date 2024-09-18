/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/09/17 19:43:12 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_handle_words(char type, t_program_data *data, int index)
{
	int	i;

	i = index;
	while (data->input[i] != type && data->input[i])
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

int	ft_tokens_fill_list(t_program_data *data)
{
	int	i;
	int	len;

	i = 0;
	while (i < (int)ft_strlen(data->input))
	{
		len = 0;
		if (data->input[i] == '>')
		{
			if (data->input[i + 1] == '>')
			{
				ft_new_token(">>", data, REDIRECT_APPEND);
				i++;
			}
			else
				ft_new_token(">", data, REDIRECT_OUT);
		}
		else if (data->input[i] == '<')
		{
			if (data->input[i + 1] == '<')
			{
				ft_new_token("<<", data, REDIRECT_HEREDOC);
				i++;
			}
			else
				ft_new_token("<", data, REDIRECT_IN);
		}
		else if (data->input[i] == '|')
			ft_new_token("|", data, PIPE);
		else if (data->input[i] == '\"')
		{
			len = ft_handle_quotes('\"', data, i + 1);
			i++;
			ft_new_token(ft_substr(data->input, i - 1, (size_t)len + 2),
				data, DOUBLE_QUOTE);
			i += len;
		}
		else if (data->input[i] == '\'')
		{
			len = ft_handle_quotes('\'', data, i + 1);
			i++;
			ft_new_token(ft_substr(data->input, i - 1, (size_t)len + 2),
				data, SINGLE_QUOTE);
			i += len;
		}
		else if (data->input[i] != ' ')
		{
			len = ft_handle_words(' ', data, i);
			ft_new_token(ft_substr(data->input, i, (size_t)len + 1),
				data, WORD);
			i += len;
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	char			*rl;
	t_program_data	data;

	data.token_top = NULL;
	if (argc != 1 || argv[1])
	{
		write(2, "Arg err\n", 8);
		return (0);
	}
	rl = readline("$> ");
	data.input = rl;
	ft_tokens_fill_list(&data);
	ft_print_tokens_list(data);
	return (0);
}
