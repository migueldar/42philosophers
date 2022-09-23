/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:48:37 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/09/23 02:24:59 by mde-arpe         ###   ########.fr       */
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
# define RED	"\033[31m"
# define GREEN	"\033[32m"
# define YELLOW	"\033[33m"
# define BLUE	"\033[34m"
# define PINK	"\033[35m"
# define CYAN	"\033[36m"
# define WHITE	"\033[37m"
# define FN		"\033[0m"

typedef struct s_philo_list
{
	pthread_mutex_t		*mutex_left;
	int					*fork_left;
	pthread_mutex_t		*mutex_right;
	int					*fork_right;
	pthread_mutex_t		*mutex_write;
	pthread_mutex_t		*mutex_end;
	int					id;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					time_think;
	int					number_eat;
	int					*end;
	struct timeval		*time_init;
	struct timeval		*time_last_ate;
	struct s_philo_list	*next;
}	t_philo_list;

typedef struct s_thread_list
{
	pthread_t				*thread;
	struct s_thread_list	*next;
}	t_thread_list;

int				ft_atoi(const char *str, int *status);
void			*philo_exec(void *philo_void);
void			printf_wrapper(int type, t_philo_list *philo);
void			add_philo(t_philo_list **philo_list, t_philo_list *new);
void			add_left_forks(t_philo_list *list);
void			end_to_true(t_philo_list *philo);
int				end_value(t_philo_list *philo);
void			free_thread_list(t_thread_list *thread_list);
void			free_philo_list(t_philo_list *list);
void			ft_usleep(long long seconds);
void			set_to_zero(int *fork, pthread_mutex_t *mutex);
char			try_to_set_one(int *fork, pthread_mutex_t *mutex);
t_philo_list	*philo_create(int *args, pthread_mutex_t *mutex_w,
					pthread_mutex_t *mutex_e);
t_thread_list	*thread_create(int *args, t_philo_list *philo_l);
void			thread_wait(t_thread_list *thread_l);
int				ft_strlen(const char *str);
//void			*malloc(size_t n);

#endif