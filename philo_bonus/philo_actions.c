/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 08:45:14 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/09/26 00:08:49 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_sleep(t_philo *philo)
{
	printf_wrapper(2, philo);
	ft_usleep(philo->time_sleep * 1000);
}

static void	philo_think(t_philo *philo)
{
	printf_wrapper(3, philo);
	ft_usleep(philo->time_think * 1000);
}

static void	philo_eat(t_philo *philo)
{
	sem_wait(philo->sem_sync);
	sem_wait(philo->sem_fork);
	sem_wait(philo->sem_fork);
	sem_post(philo->sem_sync);
	sem_wait(philo->mutex_time);
	gettimeofday(&(philo->time_last_ate), NULL);
	sem_post(philo->mutex_time);
	printf_wrapper(0, philo);
	printf_wrapper(0, philo);
	printf_wrapper(1, philo);
	ft_usleep(philo->time_eat * 1000);
	sem_post(philo->sem_fork);
	sem_post(philo->sem_fork);
}

void	philo_loop(t_philo *philo)
{
	while (philo->number_eat == -1 || (philo->number_eat)-- > 0)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
}
