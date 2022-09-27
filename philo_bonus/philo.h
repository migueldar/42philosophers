/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:48:37 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/09/25 23:12:55 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>

// COLORS
# define RED	"\033[31m"
# define GREEN	"\033[32m"
# define YELLOW	"\033[33m"
# define BLUE	"\033[34m"
# define PINK	"\033[35m"
# define CYAN	"\033[36m"
# define WHITE	"\033[37m"
# define FN		"\033[0m"

// SEMAPHORE NAMES
# define SEM_FORK	"semaphore_fork"
# define SEM_WRITE	"semaphore_write"
# define SEM_SYNC	"semaphore_sync"
# define MUTEX_TIME	"semaphore_mutex_time"

typedef struct s_philo
{
	int				id;
	int				number_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				time_think;
	int				number_eat;
	struct timeval	time_init;
	struct timeval	time_last_ate;
	sem_t			*sem_fork;
	sem_t			*sem_write;
	sem_t			*sem_sync;
	sem_t			*mutex_time;
}	t_philo;

typedef struct s_pid_list
{
	int					pid;
	struct s_pid_list	*next;
}	t_pid_list;

int				ft_atoi(const char *str, int *status);
int				ft_strlen(const char *str);
void			ft_usleep(long long seconds);
void			printf_wrapper(int type, t_philo *philo);
t_philo			create_philo(int *args);
t_pid_list		*create_processes(int number_philos, t_philo *philo);
void			processes_kill(t_pid_list *pid_list);
void			free_pid_list(t_pid_list *pid_list);
void			philo_exec(int num, t_philo *philo);
int				create_semaphores(int n_forks, t_philo *philo);
void			close_semaphores(t_philo *philo);
void			unlink_semaphores(void);
void			philo_loop(t_philo *philo);
void			*malloc(size_t n);

#endif