/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 02:51:56 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/09/25 09:40:49 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_philo_dead(void *philo_void)
{
	struct timeval	time_curr;
	long long		time_since_ate;
	t_philo			*philo;

	philo = (t_philo *)philo_void;
	while (!end_value(philo))
	{
		gettimeofday(&time_curr, NULL);
		time_since_ate = (time_curr.tv_sec - philo->time_last_ate->tv_sec)
			* 1000;
		time_since_ate += (time_curr.tv_usec
				- philo->time_last_ate->tv_usec) / 1000;
		if (time_since_ate > (long long) philo->time_die)
		{
			printf_wrapper(4, philo);
			kill(philo->pid_die, 9);
			break ;
		}
		ft_usleep(500);
	}
	return (NULL);
}

void	*checker_routine(void *philo_void)
{
	t_philo	*philo;

	philo = (t_philo *) philo_void;
	sem_wait(philo->sem_end);
	end_to_one(philo);
	sem_post(philo->sem_end);
	
	return (NULL);
}

void	single_philo(t_philo *philo)
{
	pthread_t	check_death;

	pthread_create(&check_death, NULL, check_philo_dead, philo);
	pthread_join(check_death, NULL);
	exit(0);
}

void	init_exec(int num, t_philo *philo)
{
	philo->id = num;
	if (philo->number_philos == 1)
		single_philo(philo);
	philo->sem_fork = sem_open(SEM_FORK, 0);
	philo->sem_write = sem_open(SEM_WRITE, 0);
	philo->sem_sync = sem_open(SEM_SYNC, 0);
	philo->sem_end = sem_open(SEM_END, 0);
	philo->sem_exit_d = sem_open(SEM_EXIT_D, 0);
	philo->sem_exit_n = sem_open(SEM_EXIT_N, 0);
	philo->mutex_end = sem_open(MUTEX_END, 0);
}

void	end_exec(t_philo *philo)
{
	sem_close(philo->sem_fork);
	sem_close(philo->sem_write);
	sem_close(philo->sem_sync);
	sem_close(philo->sem_end);
	sem_close(philo->sem_exit_d);
	sem_close(philo->sem_exit_n);
	sem_close(philo->mutex_end);
	free_philo(philo);
	printf("End %d\n", philo->id);
	exit(0);
}

void	philo_exec(int num, t_philo *philo)
{
	pthread_t	checker;
	pthread_t	check_death;
	int			counter;

	init_exec(num, philo);
	pthread_create(&checker, NULL, checker_routine, philo);
	pthread_create(&check_death, NULL, check_philo_dead, philo);
	philo_loop(philo);
	end_to_one(philo);
	counter = 0;
	pthread_join(check_death, NULL);
	printf("Begin %d\n", philo->id);
	if (philo->id == 1)
	{
		printf("Help please %d \n", counter);
		while (++counter < philo->number_philos)
		{
			sem_wait(philo->sem_exit_n);
		}
		kill(philo->pid_die, 9);
	}
	else
		sem_post(philo->sem_exit_n);
	printf("Middle %d\n", philo->id);
	pthread_join(checker, NULL);
	counter = 0;
	if (philo->id == 1)
	{
		while (++counter < philo->number_philos)
			sem_wait(philo->sem_exit_d);
		sem_post(philo->sem_write);
	}
	else
		sem_post(philo->sem_exit_d);
	end_exec(philo);
}
