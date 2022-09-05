/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:38:01 by hrings            #+#    #+#             */
/*   Updated: 2022/06/09 10:18:04 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

static int	phil_starved(t_philosopher *philosophers);

void	*check_philo_status(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	while (1)
	{
		sem_wait(philosopher->info->death_check);
		sem_wait(philosopher->meal_check);
		if (phil_starved(philosopher))
		{
			print_dead(philosopher);
			sem_post(philosopher->info->finished);
			break ;
		}
		sem_post(philosopher->meal_check);
		sem_post(philosopher->info->death_check);
		usleep(CHECKTIME);
	}
	return (NULL);
}

static int	phil_starved(t_philosopher *philosophers)
{
	if (philosophers->info->time_to_die <= time_dif(philosophers))
		return (1);
	else
		return (0);
}

void	*finished(void *arg)
{
	int		index;
	t_philo	*philo;

	philo = (t_philo *) arg;
	index = 0;
	sem_wait(philo->finished);
	while (index < philo->num_philo)
	{
		kill(philo->philosophers[index].id, SIGTERM);
		index++;
	}
	return (NULL);
}

void	*finished_eaten(void *arg)
{
	int		index;
	t_philo	*philo;

	philo = (t_philo *) arg;
	index = 0;
	sem_wait(philo->finished);
	while (index < philo->num_philo)
		kill(philo->philosophers[index++].id, SIGTERM);
	index = 0;
	while (index < philo->num_philo)
	{
		sem_post(philo->num_meal_check);
		index++;
	}
	return (NULL);
}

void	*philo_eaten(void *arg)
{
	t_philo	*philo;
	int		index;

	philo = (t_philo *) arg;
	index = 0;
	while (index < philo->num_philo)
	{
		sem_wait(philo->num_meal_check);
		index++;
	}
	sem_post(philo->finished);
	return (NULL);
}
