/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalgruu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 23:24:45 by ebalgruu          #+#    #+#             */
/*   Updated: 2021/10/21 23:24:54 by ebalgruu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_philo.h"

void	*check_status(void *philos)
{
	t_philo		*philo;

	philo = (t_philo *)philos;
	while (1)
	{
		usleep((useconds_t)philo->data->time_to_eat);
		if (get_time() - philo->last_meal >= philo->data->time_to_die)
		{
			philo->data->somebody_died = 1;
			sem_wait(philo->data->sem_print);
			printf("%llu %zu died\n", get_time() - philo->data->start, \
						philo->id);
			sem_post(philo->data->died);
			break ;
		}
	}
	return ((void *)0);
}

void	*ft_food_porn_bonus(t_philo *philo, size_t i)
{
	pthread_t		waiter;

	philo->data->start = get_time();
	philo->data->philo[i].last_meal = get_time();
	pthread_create(&waiter, NULL, check_status, philo);
	if (!waiter)
		ft_error_bonus(ERROR_MEMORY);
	pthread_detach(waiter);
	pthread_join(waiter, NULL);
	if (philo->id % 2 == 1)
		usleep(100);
	routine_bonus(philo->data, i);
	exit(2);
	return ((void *)0);
}

void	*wait_philo(void *datas)
{
	int			status;
	t_params	*data;
	pid_t		child;

	data = (t_params *)datas;
	child = waitpid(0, &status, 0);
	status = WEXITSTATUS(status);
	if (status > 1 && data->num_of_philos)
	{
		data->num_of_philos -= 1;
		wait_philo(data);
	}
	else
		sem_post(data->died);
	return ((void *) 0);
}

void	create_company(t_params *data)
{
	pthread_t		thread;
	int				count;

	count = 0;
	while (count < data->num_of_philos)
	{
		data->philo[count].pid = fork();
		if (data->philo[count].pid == 0)
		{
			ft_food_porn_bonus(&data->philo[count], count);
			if (data->philo[count].pid == -1)
				ft_error_bonus(ERROR_MEMORY);
		}
		else
			count++;
	}
	pthread_create(&thread, NULL, wait_philo, data);
	if (!thread)
		ft_error_bonus(ERROR_MEMORY);
	pthread_detach(thread);
}

int	main(int argc, char **argv)
{
	int				philos;
	int				count;
	t_params		data;

	count = 0;
	philos = ft_atoi(argv[1]);
	if (argc < 5 || argc > 6)
		ft_error_bonus(INVALID_ARGUMENTS);
	ft_init_bonus(&data);
	ft_get_data_bonus(&data, argv);
	ft_init_philo_bonus(&data);
	ft_init_sems(&data);
	create_company(&data);
	sem_wait(data.died);
	while (count < philos && data.num_of_philos)
		kill(data.philo[count++].pid, SIGTERM);
	clear_and_free(&data);
}
