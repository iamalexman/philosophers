/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalgruu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 20:16:20 by ebalgruu          #+#    #+#             */
/*   Updated: 2021/10/13 20:16:23 by ebalgruu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_waiter(t_params *data)
{
	size_t		full_philos;
	size_t		i;

	i = 0;
	full_philos = 0;
	while (i < data->num_of_philos)
	{
		if (data->philo->num_meals == data->num_meals && data->num_meals != 0)
		{
			usleep(1000000);
			break ;
		}
		else if (get_time() - data->philo[i].last_meal >= data->time_to_die)
		{
			data->somebody_died = 1;
			pthread_mutex_lock(&data->print);
			exit(printf("%llu %zu died\n", get_time() - data->start, \
				   data->philo[i].id));
		}
		i++;
		if (i == data->num_of_philos)
			i = 0;
	}
}

void	odd_philos(t_params *data)
{
	size_t	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (i % 2 == 1)
		{
			data->philo[i].last_meal = get_time();
			pthread_create(&((data->philo[i]).thread), NULL, routine, \
						   (void *)&(data->philo[i]));
			pthread_detach(data->philo[i].thread);
			usleep(100);
		}
		i++;
	}
}

void	even_philos(t_params *data)
{
	size_t		i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (i % 2 == 0)
		{
			data->philo[i].last_meal = get_time();
			pthread_create(&((data->philo[i]).thread), NULL, routine, \
						   (void *)&(data->philo[i]));
			pthread_detach(data->philo[i].thread);
			usleep(100);
		}
		i++;
	}
}

void	ft_food_porn(t_params *data)
{
	data->start = get_time();
	even_philos(data);
	usleep(100);
	odd_philos(data);
	ft_waiter(data);
}

int	main(int argc, char **argv)
{
	pthread_t		*thread;
	void			*philos;
	size_t			count;
	t_params		data;

	if (argc < 5 || argc > 6)
		ft_error(INVALID_ARGUMENTS);
	count = ft_atoi(argv[1]);
	philos = (t_philo *)malloc(sizeof(t_philo) * count);
	thread = (pthread_t *)malloc(sizeof(pthread_t) * count);
	data.philo = (t_philo *)malloc(sizeof(t_philo) * count);
	data.forks = (t_mutex *)malloc(sizeof(t_mutex) * count);
	if (!philos || !thread || !data.philo || !data.forks)
		ft_error(ERROR_MEMORY);
	ft_init(&data, count);
	ft_get_data(&data, argv);
	ft_init_philo(&data);
	ft_food_porn(&data);
	exit(0);
}
