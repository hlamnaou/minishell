/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbazart <gabriel.bazart@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:30:15 by gbazart           #+#    #+#             */
/*   Updated: 2024/01/11 16:52:46 by gbazart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief convert a string to int.
 *
 * @param nptr (const char *) string to convert
 * @return (int) string converted
 */
int	ft_atoi(const char *nptr)
{
	int		n;
	int		sign;
	size_t	i;

	n = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		n = n * 10 + nptr[i] - '0';
		i++;
	}
	return (n * sign);
}
