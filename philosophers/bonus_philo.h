/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_philo.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalgruu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 12:20:12 by ebalgruu          #+#    #+#             */
/*   Updated: 2021/10/22 12:20:16 by ebalgruu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_PHILO_H
# define BONUS_PHILO_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>

# define ERROR_MEMORY 101
# define INVALID_ARGUMENTS 102

typedef struct s_params
{
	pthread_t			philo_waiter;
	size_t				somebody_died;
	int					full_philos;
	int					num_of_philos;
	long long			time_to_sleep;
	long long			time_to_die;
	long long			time_to_eat;
	size_t				num_meals;
	sem_t				*sem_print;
	sem_t				*died;
	sem_t				*waiter;
	sem_t				*forks;
	sem_t				*full;
	long long			start;
	long long			routine_time;
	struct s_philo		*philo;
}						t_params;

typedef struct s_philo
{
	size_t				id;
	pid_t				pid;
	int					full;
	size_t				eat_time;
	size_t				num_meals;
	long long			last_meal;
	long long			time_to_die;
	long long			current_time;
	struct s_params		*data;
}						t_philo;

long long			get_time(void);
int					ft_atoi(char *str);
void				ft_error_bonus(int error);
void				ft_init_sems(t_params *data);
void				ft_eat_bonus(t_philo *philo);
void				ft_init_bonus(t_params *data);
void				ft_sleep_bonus(t_philo *philo);
void				ft_usleep_bonus(long long time);
void				put_forks_bonus(t_philo *philo);
void				get_forks_bonus(t_philo *philo);
void				clear_and_free(t_params *data);
void				ft_init_philo_bonus(t_params *data);
void				routine_bonus(t_params *data, size_t i);
void				ft_get_data_bonus(t_params *data, char **argv);

#endif
