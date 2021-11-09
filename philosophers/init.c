/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalgruu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 20:16:30 by ebalgruu          #+#    #+#             */
/*   Updated: 2021/10/13 20:16:32 by ebalgruu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init(t_params *data, size_t count)
{
	size_t	i;

	i = 0;
	data->start = 0;
	data->num_meals = 0;
	data->time_to_die = 0;
	data->time_to_eat = 0;
	data->routine_time = 0;
	data->somebody_died = 0;
	data->time_to_sleep = 0;
	data->num_of_philos = 0;
	pthread_mutex_init(&data->died, NULL);
	pthread_mutex_init(&data->print, NULL);
	while (i < count)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

void	ft_init_philo(t_params *data)
{
	size_t	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		(data->philo)[i].id = i + 1;
		(data->philo)[i].full = 0;
		(data->philo)[i].data = data;
		(data->philo)[i].eat_time = 0;
		(data->philo)[i].num_meals = 0;
		(data->philo)[i].last_meal = 0;
		(data->philo)[i].time_to_die = 0;
		(data->philo)[i].current_time = 0;
		if (data->num_of_philos % 2 == 0)
		{
			(data->philo)[i].left = i;
			(data->philo)[i].right = (i + 1) % data->num_of_philos;
		}
		else
		{
			(data->philo)[i].right = i;
			(data->philo)[i].left = (i + 1) % data->num_of_philos;
		}
		i++;
	}
}

void	ft_get_data(t_params *data, char **argv)
{
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->num_of_philos = ft_atoi(argv[1]);
	if (argv[5])
		data->num_meals = ft_atoi(argv[5]);
}
