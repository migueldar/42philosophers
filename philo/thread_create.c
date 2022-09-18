/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 01:57:59 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/09/12 00:19:24 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//create fail manage
t_thread_list	*new_thread(t_philo_list *philo)
{
	t_thread_list	*ret;

	ret = malloc(sizeof(t_thread_list));
	ret->thread = malloc(sizeof(pthread_t));
	pthread_create(ret->thread, NULL, philo_exec, philo);
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
