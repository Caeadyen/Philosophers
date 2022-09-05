/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 09:07:57 by hrings            #+#    #+#             */
/*   Updated: 2022/08/01 07:55:47 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

# define INT_MAX 2147483647
# define INPUTERROR 1
# define MUTEXERROR 2
# define THREADERROR 3
# define FORKTAKEN "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define CHECKTIME 500
# define SLEEPTIMER 100
# define STARTDELAY 10000

typedef struct s_philo	t_philo;

typedef struct s_philosopher
{
	int				num;
	long			last_meal;
	int				meals_needed;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*meal_check;
	pthread_t		id;
	t_philo			*info;
}	t_philosopher;

typedef struct s_philo
{
	int					num_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					num_must_eat;
	int					philo_eaten;
	int					error;
	int					all_done;
	long				start_time;
	t_philosopher		*philosophers;
	pthread_mutex_t		*meal_check;
	pthread_mutex_t		*death_check;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*writing;
}	t_philo;

int		ft_atoi_phil(const char *str, t_philo *philo);
void	error_handler(t_philo *philo, int errrornum);
void	run_dinner(t_philo *philo);
void	*active_phil(void *argv);
void	print_action(t_philosopher *philosophers, char *msg);
long	timestamp(void);
void	clean_up_phil(t_philosopher *philosophers);
void	clean_up(t_philo *philo);
void	clean_up_one(t_philo *philo);
void	*check_philo_status(void *argv);
int		not_done(t_philo *philo);
long	time_dif(t_philosopher *philosophers);
void	print_dead(t_philosopher *philosophers);
void	*check_philo_status_eaten(void *argv);
void	set_phil_meal(t_philosopher *philosophers);
void	eat(t_philosopher *philosophers);
void	eat_num_meal(t_philosopher *philosophers);
void	sleeping(t_philosopher *philosophers);
void	think(t_philosopher *philosophers);
void	run_eat_checker(t_philo *philo);
void	init_philo(t_philo *philo, t_philosopher *philosophers);
void	ft_usleep(long time);

#endif