/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atol.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:15:24 by vpelc             #+#    #+#             */
/*   Updated: 2024/10/25 16:26:35 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_exit_atol(int e)
{
	write(2, " numeric argument required\n", 27);
	exit(e);
}

static int	ft_isspace(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\v' || str[i] == '\t'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	return (i);
}

static int	ft_isnegative(char str)
{
	if (str == '+')
		return (1);
	if (str == '-')
		return (-1);
	return (0);
}

long	ft_atol(const char *str)
{
	int		i;
	long	r;
	int		n;

	n = 1;
	r = 0;
	i = ft_isspace(str);
	if (ft_isnegative(str[i]) != 0)
	{
		n *= ft_isnegative(str[i]);
		i++;
	}
	if (!ft_isdigit(str[i]))
		ft_exit_atol(255);
	while (ft_isdigit(str[i]))
	{
		r = r * 10;
		r = r + (str[i] - '0');
		i++;
	}
	if (!ft_isdigit(str[i]) && str[i] != '\0')
		ft_exit_atol(255);
	return (r * n);
}
