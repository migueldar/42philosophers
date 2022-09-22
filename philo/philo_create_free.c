/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 01:58:26 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/09/22 05:49:45 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	gbj_c_philo(t_philo_list *list, struct timeval *time1, struct timeval *time2, int *fork)
{
	if (time1)
		free(time1);
	if (time2)
		free(time2);
	if (fork)
		free(fork);
	if (list)
		free(list);
}

t_philo_list	*malloc_philo()
{
	t_philo_list	*new;

	new = malloc(sizeof(t_philo_list));
	if (!new)
		return (NULL);
	new->time_init = malloc(sizeof(struct timeval));
	if (!(new->time_init))
		return (gbj_c_philo(new, NULL, NULL, NULL), NULL);
	new->time_last_ate = malloc(sizeof(struct timeval));
	if (!(new->time_last_ate))
		return (gbj_c_philo(new, new->time_init, NULL, NULL), NULL);
	new->fork_right = malloc(4);
	if (!(new->fork_right))
		return (gbj_c_philo(new, new->time_init, new->time_last_ate, NULL), NULL);
	new->mutex_right = malloc(sizeof(pthread_mutex_t));
	if (!(new->mutex_right))
		return (gbj_c_philo(new, new->time_init, new->time_last_ate, new->fork_right), NULL);
	if (pthread_mutex_init(new->mutex_right, NULL))
		return (gbj_c_philo(new, new->time_init, new->time_last_ate, new->fork_right), free(new->mutex_right), NULL);
	return (new);
}

t_philo_list	*new_philo(int *args, int counter, pthread_mutex_t *mutex_write, pthread_mutex_t *mutex_end)
{
	t_philo_list	*new;

	new = malloc_philo();
	if (!new)
		return (NULL);
	*(new->fork_right) = 0;
	new->mutex_write = mutex_write;
	new->mutex_end = mutex_end;
	new->id = counter;
	new->time_die = args[1];
	new->time_eat = args[2];
	new->time_sleep = args[3];
	new->time_think = new->time_eat - new->time_sleep + 2;
	if (new->time_think < 0)
		new->time_think = 0;
	new->number_eat = args[4];
	new->end = &args[5];
	gettimeofday(new->time_init, NULL);
	*(new->time_last_ate) = *(new->time_init);
	return (new);
}

void	add_philo(t_philo_list **philo_list, t_philo_list *new)
{
	t_philo_list	*aux;

	if (!*philo_list)
	{
		new->next = new;
		*philo_list = new;
		return ;
	}
	aux = (*philo_list)->next;
	(*philo_list)->next = new;
	new->next = aux;
}

void	add_left_forks(t_philo_list *list)
{
	pthread_mutex_t	*aux;
	int				*aux_int;

	aux = list->mutex_right;
	aux_int = list->fork_right;
	list = list->next;
	while (list->id != 1)
	{
		list->mutex_left = aux;
		list->fork_left = aux_int;
		aux = list->mutex_right;
		aux_int = list->fork_right;
		list = list->next;
	}
	list->mutex_left = aux;
	list->fork_left = aux_int;
}

void	free_philo_list(t_philo_list *list)
{
	t_philo_list	*aux;
	t_philo_list	*head;

	head = list;
	while (list && 42)
	{
		pthread_mutex_destroy(list->mutex_right);
		free(list->mutex_right);
		free(list->fork_right);
		free(list->time_init);
		free(list->time_last_ate);
		aux = list->next;
		free(list);
		if (aux == head)
			break ;
		list = aux;
	}
}

t_philo_list	*philo_create(int *args,
	pthread_mutex_t *mutex_w, pthread_mutex_t *mutex_e)
{
	int				counter;
	t_philo_list	*philo_l;
	t_philo_list	*philo_aux;

	counter = 0;
	philo_l = NULL;
	while (++counter <= args[0])
	{
		philo_aux = new_philo(args, counter, mutex_w, mutex_e);
		if (!philo_aux)
			return (free_philo_list(philo_l), NULL);
		add_philo(&philo_l, philo_aux);
	}
	add_left_forks(philo_l);
	return (philo_l);
}
