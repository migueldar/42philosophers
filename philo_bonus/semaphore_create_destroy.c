/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore_create_destroy.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 01:43:06 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/09/26 00:19:33 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_semaphores(int n_forks, t_philo *philo)
{
	philo->sem_write = sem_open(SEM_WRITE, O_CREAT | O_EXCL, 0700, 1);
	if (!philo->sem_write)
		return (0);
	philo->sem_fork = sem_open(SEM_FORK, O_CREAT | O_EXCL, 0700, n_forks);
	if (!philo->sem_fork)
		return (0);
	philo->sem_sync = sem_open(SEM_SYNC, O_CREAT | O_EXCL, 0700, 1);
	if (!philo->sem_sync)
		return (0);
	philo->mutex_time = sem_open(MUTEX_TIME, O_CREAT | O_EXCL, 0700, 1);
	if (!philo->mutex_time)
		return (0);
	return (1);
}

void	close_semaphores(t_philo *philo)
{
	sem_close(philo->sem_write);
	sem_close(philo->sem_fork);
	sem_close(philo->sem_sync);
	sem_close(philo->mutex_time);
}

void	unlink_semaphores(void)
{
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_SYNC);
	sem_unlink(MUTEX_TIME);
}
