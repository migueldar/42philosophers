/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:48:37 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/09/25 09:01:51 by mde-arpe         ###   ########.fr       */
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
# define SEM_END	"semaphore_end"
# define SEM_EXIT_D	"semaphore_exit_dead"
# define SEM_EXIT_N "semaphore_exit_natural"
# define MUTEX_END	"semaphore_mutex_end"

typedef struct s_philo
{
	int				id;
	int				number_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				time_think;
	int				number_eat;
	int				end;
	struct timeval	*time_init;
	struct timeval	*time_last_ate;
	sem_t			*sem_fork;
	sem_t			*sem_write;
	sem_t			*sem_sync;
	sem_t			*sem_end;
	sem_t			*sem_exit_d;
	sem_t			*sem_exit_n;
	sem_t			*mutex_end;
	int				pid_die;
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
t_philo			*create_philo(int *args);
void			free_philo(t_philo *philo);
t_pid_list		*create_processes(int number_philos, t_philo *philo);
void			processes_wait(t_pid_list *pid_list);
void			free_pid_list(t_pid_list *pid_list);
void			philo_exec(int num, t_philo *philo);
int				create_semaphores(int n_forks);
void			unlink_semaphores(void);
void			end_to_one(t_philo *philo);
int				end_value(t_philo *philo);
void			philo_loop(t_philo *philo);
//void			*malloc(size_t n);

#endif