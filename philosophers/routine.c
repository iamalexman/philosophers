/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalgruu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 20:16:06 by ebalgruu          #+#    #+#             */
/*   Updated: 2021/10/13 20:16:08 by ebalgruu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long long time)
{
	while (get_time() < time)
		usleep(100);
}

void	get_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left]);
	pthread_mutex_lock(&philo->data->print);
	printf("%llu %zu has taken a left fork\n",
		   get_time() - philo->data->start, philo->id);
	pthread_mutex_unlock(&philo->data->print);
	pthread_mutex_lock(&philo->data->forks[philo->right]);
	pthread_mutex_lock(&philo->data->print);
	printf("%llu %zu has taken a right fork\n",
		   get_time() - philo->data->start, philo->id);
	pthread_mutex_unlock(&philo->data->print);
}

void	ft_eat(t_philo *philo)
{
	philo->last_meal = get_time();
	pthread_mutex_lock(&philo->data->print);
	printf("%llu %zu is eating\n", get_time() - philo->data->start, philo->id);
	philo->num_meals++;
	pthread_mutex_unlock(&philo->data->print);
	ft_usleep(philo->data->time_to_eat + philo->data->routine_time);
	philo->data->routine_time = get_time();
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->right]);
	pthread_mutex_unlock(&philo->data->forks[philo->left]);
	pthread_mutex_lock(&philo->data->print);
	printf("%llu %zu is sleeping\n",
		   get_time() - philo->data->start, philo->id);
	pthread_mutex_unlock(&philo->data->print);
	usleep((useconds_t)philo->data->time_to_sleep * 1000);
	pthread_mutex_lock(&philo->data->print);
	printf("%llu %zu is thinking\n",
		   get_time() - philo->data->start, philo->id);
	pthread_mutex_unlock(&philo->data->print);
}

void	*routine(void *philos)
{
	t_philo		*philo;

	philo = (t_philo *)philos;
	while (1)
	{
		philo->data->routine_time = get_time();
		if (philo->data->num_meals == philo->num_meals
			&& philo->data->num_meals > 0)
		{
			philo->full = 1;
			break ;
		}
		else if (philo->data->somebody_died == 1)
			break ;
		get_forks(philo);
		ft_eat(philo);
		put_forks(philo);
	}
	return ((void *)0);
}
