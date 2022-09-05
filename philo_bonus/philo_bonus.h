/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:11:57 by hrings            #+#    #+#             */
/*   Updated: 2022/07/28 09:22:42 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

# define INT_MAX 2147483647
# define INPUTERROR 1
# define MUTEXERROR 2
# define THREADERROR 3
# define FORKERROR 4
# define SEMAERROR 5
# define FORKTAKEN "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define CHECKTIME 100
# define SLEEPTIMER 100
# define STARTDELAY 10000

typedef struct s_philo	t_philo;

typedef struct s_philosopher
{
	int		num;
	long	last_meal;
	int		meals_needed;
	pid_t	id;
	sem_t	*meal_check;
	t_philo	*info;
}	t_philosopher;

typedef struct s_philo
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_must_eat;
	int				error;
	long			start_time;
	t_philosopher	*philosophers;
	sem_t			*death_check;
	sem_t			*forks;
	sem_t			*writing;
	sem_t			*finished;
	sem_t			*num_meal_check;
}	t_philo;

int		ft_atoi_phil(const char *str, t_philo *philo);
void	error_handler(t_philo *philo, int errrornum);
void	run_dinner(t_philo *philo);
void	active_phil(t_philosopher *philosophers);
void	print_action(t_philosopher *philosophers, char *msg);
long	timestamp(void);
void	clean_up_phil(t_philosopher *philosophers);
void	clean_up(t_philo *philo);
void	*check_philo_status(void *arg);
void	*finished(void *arg);
long	time_dif(t_philosopher *philosophers);
void	print_dead(t_philosopher *philosophers);
void	*philo_eaten(void *arg);
void	start_threads(t_philo *philo);
void	*finished_eaten(void *arg);
void	ft_usleep(long time);

#endif