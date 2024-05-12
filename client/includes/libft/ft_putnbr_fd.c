/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:51:48 by triedel           #+#    #+#             */
/*   Updated: 2023/11/22 16:45:07 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putlong_fd(long n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n / 10 > 0)
		ft_putlong_fd(n / 10, fd);
	ft_putchar_fd('0' + n % 10, fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	ft_putlong_fd(n, fd);
}

// int	main()
// {
// 	ft_putnbr_fd(2147483647, 1);
// 	ft_putchar_fd('\n', 1);

// 	ft_putnbr_fd(-2147483648, 1);
// 	ft_putchar_fd('\n', 1);

// 	ft_putnbr_fd(0, 1);
// 	ft_putchar_fd('\n', 1);

// 	ft_putnbr_fd(42, 1);
// 	ft_putchar_fd('\n', 1);

// 	ft_putnbr_fd(-42, 1);
// 	ft_putchar_fd('\n', 1);
// }
