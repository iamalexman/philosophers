/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalgruu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 23:25:51 by ebalgruu          #+#    #+#             */
/*   Updated: 2021/10/21 23:25:54 by ebalgruu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_philo.h"

void	ft_init_sems(t_params *data)
{
	sem_unlink("wa12");
	sem_unlink("pri1");
	sem_unlink("di1");
	sem_unlink("fo1");
	data->sem_print = sem_open("pri1", O_CREAT | O_EXCL, 0777, 1);
	data->died = sem_open("di1", O_CREAT | O_EXCL, 0777, 0);
	data->forks = sem_open("fo1", O_CREAT | O_EXCL, 0777, data->num_of_philos);
	data->waiter = sem_open("wa12", O_CREAT | O_EXCL, 0777,
			data->num_of_philos / 2);
}

void	ft_init_bonus(t_params *data)
{
	size_t	i;

	i = 0;
	data->start = 0;
	data->full_philos = 0;
	data->somebody_died = 0;
	data->num_meals = 0;
	data->time_to_die = 0;
	data->time_to_eat = 0;
	data->time_to_sleep = 0;
	data->num_of_philos = 0;
	data->routine_time = 0;
}

void	ft_init_philo_bonus(t_params *data)
{
	int			i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->num_of_philos);
	if (!data->philo)
		ft_error_bonus(ERROR_MEMORY);
	while (i < data->num_of_philos)
	{
		data->philo[i].id = i + 1;
		data->philo[i].full = 0;
		data->philo[i].eat_time = 0;
		data->philo[i].num_meals = 0;
		data->philo[i].last_meal = 0;
		data->philo[i].time_to_die = 0;
		data->philo[i].current_time = 0;
		data->philo[i].data = data;
		i++;
	}
}

void	ft_get_data_bonus(t_params *data, char **argv)
{
	data->num_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->num_meals = ft_atoi(argv[5]);
}
