/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 08:45:14 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/09/25 09:19:33 by mde-arpe         ###   ########.fr       */
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
	if (end_value(philo))
		return ;
	gettimeofday(philo->time_last_ate, NULL);
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
		if (end_value(philo))
			break ;
		philo_eat(philo);
		if (end_value(philo))
			break ;
		philo_sleep(philo);
		if (end_value(philo))
			break ;
		philo_think(philo);
	}
	printf("Exit loop %d\n", philo->id);
}
