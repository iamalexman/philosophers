/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalgruu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 23:25:16 by ebalgruu          #+#    #+#             */
/*   Updated: 2021/10/21 23:25:19 by ebalgruu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_philo.h"

void	get_forks_bonus(t_philo *philo)
{
	sem_wait(philo->data->waiter);
	sem_wait(philo->data->forks);
	sem_wait(philo->data->sem_print);
	printf("%llu %zu has taken a fork\n",
		   get_time() - philo->data->start, philo->id);
	sem_post(philo->data->sem_print);
	sem_wait(philo->data->forks);
	sem_wait(philo->data->sem_print);
	printf("%llu %zu has taken a fork\n",
		   get_time() - philo->data->start, philo->id);
	sem_post(philo->data->sem_print);
}

void	ft_eat_bonus(t_philo *philo)
{
	sem_wait(philo->data->sem_print);
	printf("%llu %zu is eating\n", get_time() - philo->data->start, philo->id);
	philo->num_meals++;
	sem_post(philo->data->sem_print);
	philo->data->routine_time = get_time();
	philo->last_meal = get_time();
	ft_usleep_bonus(philo->data->time_to_eat + philo->data->routine_time);
}

void	put_forks_bonus(t_philo *philo)
{
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	sem_post(philo->data->waiter);
	if (philo->num_meals == philo->data->num_meals
		&& philo->data->num_meals != 0)
		philo->full = 1;
	sem_wait(philo->data->sem_print);
	printf("%llu %zu is sleeping\n", get_time() - philo->data->start,
		   philo->id);
	sem_post(philo->data->sem_print);
	usleep((useconds_t)philo->data->time_to_sleep * 1000);
	sem_wait(philo->data->sem_print);
	printf("%llu %zu is thinking\n",
		   get_time() - philo->data->start, philo->id);
	sem_post(philo->data->sem_print);
}

void	routine_bonus(t_params *data, size_t i)
{
	data->start = get_time();
	while (1)
	{
		data->routine_time = get_time();
		get_forks_bonus(&data->philo[i]);
		ft_eat_bonus(&data->philo[i]);
		put_forks_bonus(&data->philo[i]);
		if (data->philo[i].full > 0)
			exit(2);
	}
}
