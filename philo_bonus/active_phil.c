/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   active_phil.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 09:52:15 by hrings            #+#    #+#             */
/*   Updated: 2022/06/09 10:15:13 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

static void	eat(t_philosopher *philosophers);
static void	eat_with_num(t_philosopher *philosophers);
static void	sleeping(t_philosopher *philosophers);
static void	think(t_philosopher *philosophers);

void	active_phil(t_philosopher *philosophers)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, check_philo_status, philosophers);
	pthread_detach(thread);
	if (philosophers->num % 2 == 1)
		usleep(STARTDELAY);
	if (philosophers->info->num_must_eat == -1)
	{
		while (1)
		{
			eat(philosophers);
			sleeping(philosophers);
			think(philosophers);
		}
	}
	else
	{
		while (1)
		{
			eat_with_num(philosophers);
			sleeping(philosophers);
			think(philosophers);
		}
	}
}

static void	eat(t_philosopher *philosophers)
{
	sem_wait(philosophers->info->forks);
	print_action(philosophers, FORKTAKEN);
	sem_wait(philosophers->info->forks);
	sem_wait(philosophers->meal_check);
	print_action(philosophers, FORKTAKEN);
	print_action(philosophers, EATING);
	philosophers->last_meal = timestamp();
	sem_post(philosophers->meal_check);
	ft_usleep(philosophers->info->time_to_eat);
	sem_post(philosophers->info->forks);
	sem_post(philosophers->info->forks);
}

static void	eat_with_num(t_philosopher *philosophers)
{
	sem_wait(philosophers->info->forks);
	print_action(philosophers, FORKTAKEN);
	sem_wait(philosophers->info->forks);
	sem_wait(philosophers->meal_check);
	print_action(philosophers, FORKTAKEN);
	print_action(philosophers, EATING);
	philosophers->last_meal = timestamp();
	philosophers->meals_needed -= 1;
	if (philosophers->meals_needed == 0)
		sem_post(philosophers->info->num_meal_check);
	sem_post(philosophers->meal_check);
	ft_usleep(philosophers->info->time_to_eat);
	sem_post(philosophers->info->forks);
	sem_post(philosophers->info->forks);
}

static void	sleeping(t_philosopher *philosophers)
{
	print_action(philosophers, SLEEPING);
	ft_usleep(philosophers->info->time_to_sleep);
}

static void	think(t_philosopher *philosophers)
{
	print_action(philosophers, THINKING);
}
