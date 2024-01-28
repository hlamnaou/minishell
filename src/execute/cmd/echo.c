/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamnaou <hlamnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 23:18:48 by gbazart           #+#    #+#             */
/*   Updated: 2024/01/27 15:36:35 by hlamnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * itereate on the args to check if there is a -n.
 *
 * @param args (char **) args
 * @param i (int *) index
 * @return (int) 1 if it works, 0 if don't.
 */
static int	check_args_echo(char **args, int *i)
{
	int	n;
	int	j;

	n = 0;
	while (args[*i])
	{
		if (args[*i][0] == '-')
		{
			j = 1;
			while (args[*i][j] && args[*i][j] == 'n')
				j++;
			if (args[*i][j])
				return (n);
			n = 1;
			(*i)++;
		}
		else
			return (n);
	}
	return (n);
}

/**
 * print the args given.
 *
 * @param args (char **) args
 * @param fd (int)
 * @return (int) 1 if it works, 0 if don't.
 */
int	echo(char **args)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	if (!args[1])
		return (1);
	n = check_args_echo(args, &i);
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!n)
		ft_putstr_fd("\n", 1);
	g_exit_code = 0;
	return (1);
}
