/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 02:51:56 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/09/11 05:39:06 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo_dead(t_philo_list *philo)
{
	struct timeval	time_curr;
	long long		time_since_ate;

	gettimeofday(&time_curr, NULL);
	time_since_ate = (time_curr.tv_sec - philo->time_last_ate->tv_sec) * 1000;
	time_since_ate += (time_curr.tv_usec
			- philo->time_last_ate->tv_usec) / 1000;
	if (time_since_ate > (long long) philo->time_die)
	{
		printf_wrapper(4, philo->mutex_write, philo->id, philo->time_init);
		end_to_true(philo);
		return (1);
	}
	return (0);
}

void	philo_sleep(t_philo_list *philo)
{
	printf_wrapper(2, philo->mutex_write, philo->id, philo->time_init);
	usleep(philo->time_sleep * 1000);
}

void	philo_think(t_philo_list *philo)
{
	printf_wrapper(3, philo->mutex_write, philo->id, philo->time_init);
}

void	philo_eat(t_philo_list *philo)
{
	pthread_mutex_lock(philo->mutex_right);
	pthread_mutex_unlock(philo->mutex_right);
	usleep(100);
	pthread_mutex_lock(philo->mutex_left);
	pthread_mutex_unlock(philo->mutex_left);
	usleep(100);
	pthread_mutex_lock(philo->mutex_right);
	pthread_mutex_lock(philo->mutex_left);
	if (end_value(philo) || check_philo_dead(philo))
	{
		pthread_mutex_unlock(philo->mutex_right);
		pthread_mutex_unlock(philo->mutex_left);
		return ;
	}
	printf_wrapper(0, philo->mutex_write, philo->id, philo->time_init);
	printf_wrapper(0, philo->mutex_write, philo->id, philo->time_init);
	printf_wrapper(1, philo->mutex_write, philo->id, philo->time_init);
	usleep(philo->time_eat * 1000);
	pthread_mutex_unlock(philo->mutex_right);
	pthread_mutex_unlock(philo->mutex_left);
	gettimeofday(philo->time_last_ate, NULL);
}

void	*philo_exec(void *philo_void)
{
	t_philo_list	*philo;

	//printf("Hello from %d\n", philo->id);
	philo = (t_philo_list *) philo_void;
	while (philo->number_eat == -1 || (philo->number_eat)-- > 0)
	{
		if (end_value(philo) || check_philo_dead(philo))
			break ;
		philo_eat(philo);
		if (end_value(philo) || check_philo_dead(philo))
			break ;
		philo_sleep(philo);
		if (end_value(philo) || check_philo_dead(philo))
			break ;
		philo_think(philo);
	}
	pthread_mutex_destroy(philo->mutex_right);
	free(philo->mutex_right);
	free(philo->time_init);
	free(philo->time_last_ate);
	free(philo);
	return (NULL);
}
