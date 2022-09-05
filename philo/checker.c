/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:38:01 by hrings            #+#    #+#             */
/*   Updated: 2022/05/20 11:42:55 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	set_all_done(t_philo *philo);
static int	check_all_eaten(t_philo *philo);

int	not_done(t_philo *philo)
{
	int	result;

	pthread_mutex_lock(philo->death_check);
	result = philo->all_done;
	pthread_mutex_unlock(philo->death_check);
	return (result);
}

void	*check_philo_status(void *argv)
{
	t_philosopher	*philosophers;

	philosophers = (t_philosopher *)argv;
	while (not_done(philosophers->info))
	{
		pthread_mutex_lock(philosophers->meal_check);
		if (philosophers->info->time_to_die <= time_dif(philosophers))
		{
			set_all_done(philosophers->info);
			print_dead(philosophers);
		}
		pthread_mutex_unlock(philosophers->meal_check);
		usleep(CHECKTIME);
	}
	return (NULL);
}

void	*check_philo_status_eaten(void *argv)
{
	t_philo	*philo;

	philo = (t_philo *)argv;
	while (not_done(philo))
	{
		if (check_all_eaten(philo))
			set_all_done(philo);
		usleep(CHECKTIME);
	}
	return (NULL);
}

static void	set_all_done(t_philo *philo)
{
	pthread_mutex_lock(philo->death_check);
	philo->all_done = 0;
	pthread_mutex_unlock(philo->death_check);
}

static int	check_all_eaten(t_philo *philo)
{
	int	result;

	pthread_mutex_lock(philo->meal_check);
	if (philo->philo_eaten >= philo->num_philo)
		result = 1;
	else
		result = 0;
	pthread_mutex_unlock(philo->meal_check);
	return (result);
}
