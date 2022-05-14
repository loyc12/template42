/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:53:48 by llord             #+#    #+#             */
/*   Updated: 2022/05/03 10:58:54 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

//printf but wonkier

int		allowsprint(char c);
void	printptr(void *param);
void	printparam(char c, void *param);

int	ft_printf(const char *input, ...)
{
	va_list	args;
	char	*string;
	int		i;

	va_start(args, input);
	i = 0;
	string = va_arg(args, char *);
	while (string[i])
	{
		if (string[i] != '%')
			write(1, string, 1);
		else
		{
			if (allowsprint(string[i]))
				printparam(string[i], va_arg(args, void *));
			else if (string[i + 1] == '%')
				write(1, "%", 1);
			i++;
		}
		i++;
	}
	va_end(args);

	return (0);		//temp
}

int	allowsprint(char c)
{
	if (c == 'c' || c == 's' || c == 'p' \
		|| c == 'd' || c == 'i' || c == 'u' \
		|| c == 'x' || c == 'X')
		return (1);
	return (0);
}

void	printparam(char c, void *param)
{
	if (c == 'c')
		write(1, (char *)param, 1);
	if (c == 's')
		ft_putstr((char *)param);
	if (c == 'p')
		printptr(param);
	if (c == 'd')
		ft_putnbr((int)param);
	if (c == 'i')
		ft_putnbr((int)param);
	if (c == 'u')
		ft_putbase((unsigned long)param, 10, "0123456789");
	if (c == 'x')
		ft_putbase((unsigned long)param, 16, "0123456789abcdef");
	if (c == 'X')
		ft_putbase((unsigned long)param, 16, "0123456789ABCDEF")
}

void	printptr(void *param)
{
	write(1, "0x", 2);
	ft_putbase((unsigned long)param, 16, "0123456789ABCDEF");
}
