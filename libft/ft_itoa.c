/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbazart <gabriel.bazart@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:42:39 by gbazart           #+#    #+#             */
/*   Updated: 2024/01/23 03:00:03 by gbazart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_number(long int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_putina(char *dest, long int number, int len)
{
	while (number > 0)
	{
		dest[len--] = (number % 10) + 48;
		number /= 10;
	}
	return (dest);
}

/**
 * @brief convert a int to string.
 *
 * @param n (int) int to convert
 * @return (char *) string converted don't forget to free it.
 */
char	*ft_itoa(int n)
{
	char		*dst;
	long int	num;
	int			len;

	len = count_number(n);
	dst = malloc((len + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	dst[len--] = '\0';
	num = n;
	if (num < 0)
	{
		num *= -1;
		dst[0] = '-';
	}
	else if (n == 0)
		dst[0] = '0';
	return (ft_putina(dst, num, len));
}
