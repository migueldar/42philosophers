/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_create_free.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 01:57:59 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/09/23 01:47:46 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_to_die()
{
	while (1)
		ft_usleep(500);
}

void	create_append_list(int pid, t_pid_list **list)
{
	t_pid_list	*new;
	
	new = malloc(sizeof(t_pid_list));
	new->pid = pid;
	new->next = *list;
	*list = new;
}

void	free_pid_list(t_pid_list *list)
{
	t_pid_list	*aux;

	while (list)
	{
		aux = list;
		list = list->next;
		free(aux);
	}
}

t_pid_list	*create_processes(int number_philos, t_philo *philo)
{
	int			counter;
	int			pid;
	t_pid_list	*pid_list;
	int			pid_die;

	pid_die = fork();
	if (pid_die == 0)
		wait_to_die();
	philo->pid_die = pid_die;
	pid_list = NULL;
	counter = 0;
	while (++counter <= number_philos)
	{
		pid = fork();
		if (pid == 0)
			philo_exec(counter, philo);
		create_append_list(pid, &pid_list);
	}
	waitpid(pid_die, NULL, 0);
	return (pid_list);
}

void	processes_wait(t_pid_list *pid_list)
{
	while (pid_list)
	{
		waitpid(pid_list->pid, NULL, 0);
		pid_list = pid_list->next;
	}
}
