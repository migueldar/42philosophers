/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores_create_destroy.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 01:43:06 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/09/23 01:46:14 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int create_semaphores(int n_forks)
{
    sem_t   *sem_w;
    sem_t   *sem_f;
    sem_t   *sem_s;
    sem_t   *sem_e;
    
    sem_w = sem_open(SEM_WRITE, O_CREAT | O_EXCL, 0700, 1);
    if (!sem_w)
        return (0);
    sem_f = sem_open(SEM_FORK, O_CREAT | O_EXCL, 0700, n_forks);
    if (!sem_f)
        return (sem_close(sem_w), sem_unlink(SEM_WRITE), 0);
    sem_s = sem_open(SEM_SYNC, O_CREAT | O_EXCL, 0700, 1);
    sem_e = sem_open(SEM_END, O_CREAT | O_EXCL, 0700, 0);
    sem_close(sem_w);
    sem_close(sem_f);
    sem_close(sem_s);
    sem_close(sem_e);
    return (1);
}

void    unlink_semaphores(void)
{
    sem_unlink(SEM_WRITE);
    sem_unlink(SEM_FORK);
    sem_unlink(SEM_SYNC);
    sem_unlink(SEM_END);
}