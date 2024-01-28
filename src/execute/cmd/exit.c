/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamnaou <hlamnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 18:17:26 by gbazart           #+#    #+#             */
/*   Updated: 2024/01/27 15:41:11 by hlamnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief check if the number is inferior to LLONG_MIN.
 *
 * @param num (char *) number
 * @return true if inferior, false if not
 */
static bool	inf_to_llmin(char *num)
{
	int	i;

	i = 1;
	if (num[0] != '-')
		return (false);
	if (ft_strlen(num) < 20)
		return (false);
	if (ft_strlen(num) > 20)
		return (true);
	while (num[i])
	{
		if ((num[i] - 48) > (MIN_LL[i] - 48))
			return (true);
		if ((num[i] - 48) < (MIN_LL[i] - 48))
			return (false);
		i++;
	}
	return (false);
}

/**
 * @brief check if the number is superior to LLONG_MAX.
 *
 * @param num (char *) number
 * @return true if superior, false if not
 */
static bool	sup_to_llmax(char *num)
{
	int	i;

	i = 0;
	if (num[0] == '-')
		return (false);
	if (ft_strlen(num) < 19)
		return (false);
	if (ft_strlen(num) > 19)
		return (true);
	while (num[i] && MAX_LL[i])
	{
		if ((num[i] - 48) > (MAX_LL[i] - 48))
			return (true);
		if ((num[i] - 48) < (MAX_LL[i] - 48))
			return (false);
		i++;
	}
	if (num[i])
		return (true);
	return (false);
}

/**
 * @brief print exit. (norme !!!!)
 *
 * @param print (int) 1 if it works, 0 if don't.
 */
void	print_exit(int print, int code)
{
	if (print)
		ft_putendl_fd("exit", 2);
	g_exit_code = code;
}

/**
 * @brief exit the program
 *
 * @param args (char **)
 * @param data (t_data *)
 * @return (int) 1 if it works, 0 if don't.
 */
void	exit_builtin(char **args, t_data *data, int print)
{
	if (args[1] == NULL)
	{
		print_exit(print, 0);
		data->exit = true;
	}
	else if (!ft_isnumeric(args[1]) || sup_to_llmax(args[1]) == true
		|| inf_to_llmin(args[1]) == true)
	{
		print_exit(print, 2);
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		data->exit = true;
	}
	else if (args[2])
	{
		g_exit_code = 1;
		ft_putstr_fd("exit: too many arguments\n", 2);
	}
	else
	{
		print_exit(print, ft_atoll(args[1]) % 256);
		data->exit = true;
	}
}
