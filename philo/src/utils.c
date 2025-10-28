/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 19:45:04 by abita             #+#    #+#             */
/*   Updated: 2025/10/27 11:36:50 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/philo.h"

long long	ft_atol(const char *nptr)
{
	long	num;
	int		minus;
	int		i;

	minus = 1;
	num = 0;
	i = 0;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			minus = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num *= 10;
		num += nptr[i] - '0';
		i++;
	}
	return (num * minus);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count && size && count > SIZE_MAX / size)
		return (NULL);
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}

int	ft_valid_number(char *str)
{
	int	i;

	if (!str)
		return (EXIT_FAILURE);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (EXIT_FAILURE);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

size_t ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return(i);
}
void print_error(const char *msg)
{
	write(STDERR_FILENO, "\033[31m", 5);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\033[31m", 5);
}