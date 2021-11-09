/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalgruu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 12:19:58 by ebalgruu          #+#    #+#             */
/*   Updated: 2021/10/22 12:20:02 by ebalgruu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define ERROR_MEMORY 101
# define INVALID_ARGUMENTS 102

typedef pthread_mutex_t	t_mutex;

typedef struct s_params
{
	size_t				somebody_died;
	size_t				num_of_philos;
	long long			time_to_sleep;
	long long			time_to_die;
	long long			time_to_eat;
	size_t				num_meals;
	t_mutex				print;
	t_mutex				died;
	t_mutex				*forks;
	struct s_philo		*philo;
	long long			start;
	long long			routine_time;
}						t_params;

typedef struct s_philo
{
	size_t				id;
	size_t				full;
	size_t				died;
	size_t				left;
	size_t				right;
	pthread_t			thread;
	size_t				eat_time;
	size_t				num_meals;
	struct s_params		*data;
	long long			last_meal;
	long long			time_to_die;
	long long			current_time;
}				t_philo;

void			ft_usleep(long long time);
void			ft_error(int error);
long long		get_time(void);
void			ft_eat(t_philo *philo);
int				ft_atoi(const char *str);
void			ft_sleep(t_philo *philo);
void			put_forks(t_philo *philo);
void			get_forks(t_philo *philo);
void			ft_init_philo(t_params *data);
void			ft_init(t_params *data, size_t count);
void			ft_get_data(t_params *data, char **argv);
void			*routine(void *philos);

#endif
