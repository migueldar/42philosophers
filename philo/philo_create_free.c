/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 01:58:26 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/09/26 00:20:15 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	garbage_coll_philo(t_philo_list *list, struct timeval *time1,
							struct timeval *time2, int *fork)
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

static t_philo_list	*malloc_philo(void)
{
	t_philo_list	*new;

	new = malloc(sizeof(t_philo_list));
	if (!new)
		return (NULL);
	new->time_init = malloc(sizeof(struct timeval));
	if (!(new->time_init))
		return (garbage_coll_philo(new, NULL, NULL, NULL), NULL);
	new->time_last_ate = malloc(sizeof(struct timeval));
	if (!(new->time_last_ate))
		return (garbage_coll_philo(new, new->time_init, NULL, NULL), NULL);
	new->fork_right = malloc(4);
	if (!(new->fork_right))
		return (garbage_coll_philo(new, new->time_init,
				new->time_last_ate, NULL), NULL);
	new->mutex_right = malloc(sizeof(pthread_mutex_t));
	if (!(new->mutex_right))
		return (garbage_coll_philo(new, new->time_init,
				new->time_last_ate, new->fork_right), NULL);
	if (pthread_mutex_init(new->mutex_right, NULL))
		return (free(new->mutex_right), garbage_coll_philo(new, new->time_init,
				new->time_last_ate, new->fork_right), NULL);
	return (new);
}

static t_philo_list	*new_philo(int *args, int counter,
								pthread_mutex_t *mutex_write,
								pthread_mutex_t *mutex_end)
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
