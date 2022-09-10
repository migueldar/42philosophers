/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:48:37 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/09/10 05:08:13 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>

// COLORS
#define red		"\033[31m"
#define green	"\033[32m"
#define yellow	"\033[33m"
#define blue	"\033[34m"
#define magenta	"\033[35m"
#define cyan	"\033[36m"
#define white	"\033[37m"
#define fn		"\033[0m"

typedef struct s_philo_list
{
	pthread_mutex_t		*mutex_left;
	int					fork_l;
	pthread_mutex_t		*mutex_right;
	int					fork_r;
	pthread_mutex_t		*mutex_write;
	int					*end;
	int					id;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					number_eat;
	struct s_philo_list	*next;
}	t_philo_list;

typedef struct s_thread_list
{
	pthread_t				*thread;
	struct s_thread_list	*next;
}	t_thread_list;

int		ft_atoi(const char *str, int *status);
void	*philo_exec(void *philo_void);
void	printf_wrapper(int type, pthread_mutex_t *write_mutex, int philo_id);

#endif