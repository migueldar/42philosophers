/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore_create_destroy.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 01:43:06 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/09/25 09:02:02 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	close_semaphores(sem_t **sems, int n)
{
	while (n--)
		sem_close(sems[n]);
}

int	create_semaphores(int n_forks)
{
	sem_t	*sems[7];

	sems[0] = sem_open(SEM_WRITE, O_CREAT | O_EXCL, 0700, 1);
	if (!sems[0])
		return (0);
	sems[1] = sem_open(SEM_FORK, O_CREAT | O_EXCL, 0700, n_forks);
	if (!sems[1])
		return (close_semaphores(sems, 1), 0);
	sems[2] = sem_open(SEM_SYNC, O_CREAT | O_EXCL, 0700, 1);
	if (!sems[2])
		return (close_semaphores(sems, 2), 0);
	sems[3] = sem_open(SEM_END, O_CREAT | O_EXCL, 0700, 0);
	if (!sems[3])
		return (close_semaphores(sems, 3), 0);
	sems[4] = sem_open(SEM_EXIT_D, O_CREAT | O_EXCL, 0700, 0);
	if (!sems[4])
		return (close_semaphores(sems, 4), 0);
	sems[5] = sem_open(SEM_EXIT_N, O_CREAT | O_EXCL, 0700, 0);
	if (!sems[5])
		return (close_semaphores(sems, 5), 0);
	sems[6] = sem_open(MUTEX_END, O_CREAT | O_EXCL, 0700, 1);
	if (!sems[6])
		return (close_semaphores(sems, 6), 0);
	close_semaphores(sems, 7);
	return (1);
}

void	unlink_semaphores(void)
{
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_SYNC);
	sem_unlink(SEM_END);
	sem_unlink(SEM_EXIT_D);
	sem_unlink(SEM_EXIT_N);
	sem_unlink(MUTEX_END);
}
