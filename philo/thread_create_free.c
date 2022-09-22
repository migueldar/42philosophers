/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_create_free.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 01:57:59 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/09/22 05:36:15 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_thread_list	*new_thread(t_philo_list *philo)
{
	t_thread_list	*ret;

	ret = malloc(sizeof(t_thread_list));
	if (!ret)
		return (NULL);
	ret->thread = malloc(sizeof(pthread_t));
	if (!(ret->thread))
		return (free(ret), NULL);
	if (pthread_create(ret->thread, NULL, philo_exec, philo))
		return (free(ret->thread), free(ret), NULL);
	ft_usleep(100);
	ret->next = NULL;
	return (ret);
}

void	add_thread(t_thread_list **thread_list, t_thread_list *new)
{
	if (*thread_list)
		new->next = *thread_list;
	*thread_list = new;
}

void	free_thread_list(t_thread_list *thread_list)
{
	t_thread_list	*aux;

	while (thread_list)
	{
		free(thread_list->thread);
		aux = thread_list->next;
		free(thread_list);
		thread_list = aux;
	}
}

t_thread_list	*thread_create(int *args, t_philo_list *philo_l)
{
	int				counter;
	t_thread_list	*thread_l;
	t_thread_list	*thread_aux;

	counter = 0;
	thread_l = NULL;
	while (++counter <= args[0])
	{
		thread_aux = new_thread(philo_l);
		if (!thread_aux)
		{
			end_to_true(philo_l);
			thread_wait(thread_l);
			free_thread_list(thread_l);
		}
		add_thread(&thread_l, thread_aux);
		philo_l = philo_l->next;
	}
	return (thread_l);
}

void	thread_wait(t_thread_list *thread_l)
{
	while (thread_l)
	{
		pthread_join(*(thread_l->thread), NULL);
		thread_l = thread_l->next;
	}
}
