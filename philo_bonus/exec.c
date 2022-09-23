/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 02:51:56 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/09/23 02:20:00 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo_dead(t_philo *philo)
{
	struct timeval	time_curr;
	long long		time_since_ate;

	gettimeofday(&time_curr, NULL);
	time_since_ate = (time_curr.tv_sec - philo->time_last_ate->tv_sec) * 1000;
	time_since_ate += (time_curr.tv_usec
			- philo->time_last_ate->tv_usec) / 1000;
	if (time_since_ate > (long long) philo->time_die)
	{
		printf_wrapper(4, philo);
		philo->end = 1;
		return (1);
	}
	return (0);
}

void	philo_sleep(t_philo *philo)
{
	printf_wrapper(2, philo);
	ft_usleep(philo->time_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	printf_wrapper(3, philo);
	ft_usleep(philo->time_think * 1000);
}

void	philo_eat(t_philo *philo)
{
	sem_wait(philo->sem_sync);
	sem_wait(philo->sem_fork);
	sem_wait(philo->sem_fork);
	sem_post(philo->sem_sync);
	if (philo->end || check_philo_dead(philo))
		return (sem_post(philo->sem_fork), sem_post(philo->sem_fork), (void) 42);
	gettimeofday(philo->time_last_ate, NULL);
	printf_wrapper(0, philo);
	printf_wrapper(0, philo);
	printf_wrapper(1, philo);
	ft_usleep(philo->time_eat * 1000);
	sem_post(philo->sem_fork);
	sem_post(philo->sem_fork);
}

void	*checker_routine(void *end)
{
	sem_t	*sem_end;

	sem_end = sem_open(SEM_END, 0);
	sem_wait(sem_end);
	*(int *)end = 1;
	sem_post(sem_end);
	sem_close(sem_end);
	return (NULL);
}

void	philo_exec(int num, t_philo *philo)
{
	pthread_t	checker;

	philo->id = num;
	philo->sem_fork = sem_open(SEM_FORK, 0);
	philo->sem_write = sem_open(SEM_WRITE, 0);
	philo->sem_sync = sem_open(SEM_SYNC, 0);
	pthread_create(&checker, NULL, checker_routine, &(philo->end));
	pthread_detach(checker);
	while (philo->number_eat == -1 || (philo->number_eat)-- > 0)
	{
		if (philo->end || check_philo_dead(philo))
			break ;
		philo_eat(philo);
		if (philo->end || check_philo_dead(philo))
			break ;
		philo_sleep(philo);
		if (philo->end || check_philo_dead(philo))
			break ;
		philo_think(philo);
	}
	exit(0);
}
