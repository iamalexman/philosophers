/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalgruu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 23:25:29 by ebalgruu          #+#    #+#             */
/*   Updated: 2021/10/21 23:25:31 by ebalgruu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_philo.h"

int	ft_atoi(char *str)
{
	long	result;
	int		sign;
	int		i;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 8 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = ((result * 10) + (str[i] - '0'));
		if (result > 2147483647 && sign == 1)
			return (-1);
		if (result > 2147483648 && sign == -1)
			return (0);
		i++;
	}
	return ((int)result * sign);
}

void	ft_error_bonus(int error)
{
	if (error == 102)
		printf("Error arguments\n");
	else if (error == 101)
		printf("Error memory\n");
	else
		printf("Common error\n");
	exit(0);
}

long long	get_time(void)
{
	struct timeval	 time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep_bonus(long long time)
{
	while (get_time() < time)
		usleep(100);
}

void	clear_and_free(t_params *data)
{
	sem_close(data->sem_print);
	sem_close(data->died);
	sem_close(data->forks);
	sem_close(data->waiter);
	sem_close(data->full);
	free(data->philo);
	exit(0);
}
